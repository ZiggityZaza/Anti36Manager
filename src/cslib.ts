import * as fs from "node:fs"
import * as fsp from "node:fs/promises"
import * as path from "node:path"
import * as os from "node:os"
import { spawnSync } from "node:child_process"


export function is_windows(): boolean {
  return os.platform() === "win32"
}
export function is_unix(): boolean {
  return os.platform() === "linux" || os.platform() === "darwin"
}


export function range(_from: number, _to: number, _step: number = 1): Array<number> {
  let result: Array<number> = []
  if (_from < _to)
    for (let i = _from; i < _to; i += _step)
      result.push(i)
  else if (_from > _to)
    for (let i = _from; i > _to; i -= _step)
      result.push(i)
  else
    return result
  return result
}


export function add_self_to_map<K, V>(_map: Map<K, V[]>, _key: K, _value: V): void {
  if (_map.has(_key))
    _map.get(_key)!.push(_value)
  else
    _map.set(_key, [_value])
}


export function to_str(x: unknown): string {
  if (typeof x === "string")
    return x
  if (x === null || x === undefined)
    return String(x)
  try {
    return typeof (x as any).toString === "function" ? (x as any).toString() : JSON.stringify(x)
  } catch {
    try { return JSON.stringify(x) }
    catch { return String(x) }
  }
}



export function separate(_str: string, _sep: string): string[] {
  return _str.split(_sep)
}



export class AnyError extends Error {
  constructor(...msgs: unknown[]) {
    const where = process.cwd()
    const reason = msgs.map(to_str).join("")
    super(`cslib::AnyError at ${where} because: ${reason}`)
  }
}



type road_t = Road | Folder | BizarreRoad
export abstract class Road {
  /*
    Represents an entry on the disk with
    extra methods to manage it
    Note:
      Not turned into an abstract class so
      it can be instantiated directly for
      other file types such as pipes
  */
  isAt: string


  constructor(_lookFor: string, _shouldBeOfType?: fs.Stats["mode"]) {
    /*
      Find and resolve the absolute path of _lookFor
      with optional check to _shouldBeOfType
    */
    this.isAt = path.resolve(_lookFor)
    if (_shouldBeOfType) {
      const actualType = this.type()
      if (actualType !== _shouldBeOfType)
        throw new AnyError("Expected type ", _shouldBeOfType, " but got ", actualType)
    }
  }


  abstract cpy(): Road
  del(): void {} // Skipped because nothing to destruct


  type(): fs.Stats["mode"] | "none" {
    try {
      const st = fs.lstatSync(this.isAt)
      return st.mode
    } catch {
      return "none"
    }
  }


  last_modified(): Date {
    const st = fs.statSync(this.isAt)
    return st.mtime
  }


  name(): string {
    return path.basename(this.isAt)
  }


  parent(): Folder {
    return new Folder(path.dirname(this.isAt))
  }


  depth(): number {
    return this.isAt.split(path.sep).length - 1
  }


  layer(_index: number): Folder {
    /*
      Find parent paths by layer
      Example:
        const f = new Folder("/root/projects/folder")
        const root: Folder = f.layer(0)
        const parent: Folder = f.layer(f.depth()-1)
    */
    let parent: Folder = new Folder("../") // Placeholder
    if (_index >= this.depth() || _index < 0)
      throw new AnyError(`Trying to reach (${_index}) but depth is ${this.depth()}`)
    for (const _ of range(0, this.depth() - _index))
      parent = parent.parent()
    return parent
  }


  rename_self_to(_newName: string): void {
    if (_newName.includes(path.sep))
      throw new AnyError(`Renaming to a path "${_newName}" is not allowed (_newName includes path.sep)`)
    const newPath = path.join(this.parent().isAt, _newName)
    fs.renameSync(this.isAt, newPath)
    this.isAt = newPath
  }


  abstract copy_self_into(_copyInto: Folder): Road


  abstract move_self_into(_moveInto: Folder): void
}



export class BizarreRoad extends Road {
  /*
    Specifically for files that don't fit into
    the usual categories such as symbolic links
    or pipes.
  */
  constructor(_lookFor: string) {
    const stats = fs.lstatSync(_lookFor)
    if (stats.isDirectory() || stats.isFile())
      throw new AnyError(`"${_lookFor}" is a regular file or directory`)
    super(_lookFor)
  }


  override cpy(): BizarreRoad { return new BizarreRoad(this.isAt) }


  override copy_self_into(_copyInto: Folder): BizarreRoad {
    /*
      Attempt to copy the special file using system utilities
    */
    const destPath = path.join(_copyInto.isAt, this.name())
    const stats = fs.lstatSync(this.isAt)
    if (fs.existsSync(destPath))
      throw new AnyError(`Copying to "${destPath}" would overwrite an existing entry`)
    if (stats.isSymbolicLink()) {
      // Copy symlink target
      const linkTarget = fs.readlinkSync(this.isAt)
      fs.symlinkSync(linkTarget, destPath)
    } else {
      // Trying to use 'cp' for other special files (pipes, sockets, etc.)
      const result = spawnSync("cp", ["-a", this.isAt, destPath])
      if (result.status !== 0)
        throw new AnyError(`Failed to copy special file: ${result.stderr?.toString() || "unknown error"}`)
    }
    return new BizarreRoad(destPath)
  }


  override move_self_into(_moveInto: Folder): void {
    const destPath = path.join(_moveInto.isAt, this.name())
    if (fs.existsSync(destPath))
      throw new AnyError(`Moving to "${destPath}" would overwrite an existing entry`)
    fs.renameSync(this.isAt, destPath)
    this.isAt = destPath
  }
}



export class Folder extends Road {
  /*
    Handles folders in the file system
  */
  constructor(_lookFor: string, createIfNotExists: boolean = false) {
    if (createIfNotExists && !fs.existsSync(_lookFor))
      fs.mkdirSync(_lookFor, { recursive: true })
    super(_lookFor, fs.constants.S_IFDIR)
  }


  override cpy(): Folder { return new Folder(this.isAt) }


  list(): Array<road_t> {
    return fs.readdirSync(this.isAt).map(name => {
      const fullPath = path.join(this.isAt, name)
      const stats = fs.lstatSync(fullPath)
      if (stats.isDirectory())
        return new Folder(fullPath)
      else if (stats.isFile())
        return new File(fullPath)
      else
        return new BizarreRoad(fullPath)
    })
  }


  find(_lookFor: string): road_t | undefined {
    /*
      Check if the folder contains a file or folder with
      the given relative path. If it does, return the
      corresponding Road object.
      Note:
        Path MUST be relative
    */
    if (_lookFor.length == 0)
      throw new AnyError(`Invalid path: ${_lookFor}`)
    if (is_windows() && _lookFor.at(1) === ":" && _lookFor.at(2) === "\\") // Disk:\
      throw new AnyError(`Path must be relative, got "${_lookFor}"`)
    else if (is_unix() && _lookFor.startsWith("/"))
      throw new AnyError(`Path must be relative, got "${_lookFor}"`)

    if (fs.existsSync(path.join(this.isAt, _lookFor))) {
      const stats = fs.lstatSync(path.join(this.isAt, _lookFor))
      if (stats.isDirectory())
        return new Folder(path.join(this.isAt, _lookFor))
      else if (stats.isFile())
        return new File(path.join(this.isAt, _lookFor))
      else
        return new BizarreRoad(path.join(this.isAt, _lookFor))
    }
    return undefined
  }


  override copy_self_into(_copyInto: Folder): Folder {
    // Recursive copy
    const newFolder = new Folder(path.join(_copyInto.isAt, this.name()))
    if (fs.existsSync(newFolder.isAt))
      throw new AnyError(`Copying to "${newFolder.isAt}" would overwrite an existing entry`)
    this.list().forEach(item => {
      item.copy_self_into(newFolder)
    })
    return newFolder
  }


  override move_self_into(_moveInto: Folder): void {
    const newPath = path.join(_moveInto.isAt, this.name())
    if (fs.existsSync(newPath))
      throw new AnyError(`Moving to "${newPath}" would overwrite an existing entry`)
    fs.renameSync(this.isAt, newPath)
    this.isAt = newPath
  }
}



export class File extends Road {
  /*
    Handles files in the file system
  */
  constructor(_lookFor: string, createIfNotExists: boolean = false) {
    if (createIfNotExists && !fs.existsSync(_lookFor))
      fs.writeFileSync(_lookFor, "")
    super(_lookFor, fs.constants.S_IFREG)
  }


  override copy_self_into(_copyInto: Folder): File {
    const newFile = new File(path.join(_copyInto.isAt, this.name()))
    if (fs.existsSync(newFile.isAt))
      throw new AnyError(`Copying to "${newFile.isAt}" would overwrite an existing entry`)
    fs.copyFileSync(this.isAt, newFile.isAt)
    return newFile
  }
  override move_self_into(_moveInto: Folder): void {
    const newPath = path.join(_moveInto.isAt, this.name())
    if (fs.existsSync(newPath))
      throw new AnyError(`Moving to "${newPath}" would overwrite an existing entry`)
    fs.renameSync(this.isAt, newPath)
    this.isAt = newPath
  }


  override cpy(): File { return new File(this.isAt) }


  read_text(): string {
    return fs.readFileSync(this.isAt, "utf-8")
  }
  edit_text(newText: string): void {
    fs.writeFileSync(this.isAt, newText)
  }


  read_binary(): Buffer {
    return fs.readFileSync(this.isAt)
  }
  edit_binary(newBuffer: Buffer | Uint8Array): void {
    fs.writeFileSync(this.isAt, newBuffer)
  }


  extension(): string {
    return path.extname(this.isAt)
  }
  size_in_bytes(): number {
    return fs.statSync(this.isAt).size
  }
}



export function read_json_as<Interface>(_file: File): Interface {
  const content = _file.read_text()
  return JSON.parse(content) as Interface
}