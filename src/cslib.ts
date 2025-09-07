/*
  Provides basic utilities
*/
import * as fs from "node:fs"
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



export function find_self_in_arr<T>(_array: Array<T>, _lookFor: T): T | undefined {
  return _array.find(item => item === _lookFor)
}
export function find_key_in_map<K, V>(_map: Map<K, V[]>, _key: K): V[] | undefined {
  return _map.has(_key) ? _map.get(_key) : undefined
}
export function find_val_in_map<K, V>(_map: Map<K, V[]>, _value: V): K | undefined {
  for (const [key, values] of _map.entries())
    if (values.includes(_value))
      return key
  return undefined
}


export function add_val_to_map<K, V>(_map: Map<K, V[]>, _key: K, _value: V): void {
  if (_map.has(_key))
    _map.get(_key)!.push(_value)
  else
    _map.set(_key, [_value])
}
export function add_key_to_map<K, V>(_map: Map<K, V[]>, _key: K): void {
  if (!_map.has(_key))
    _map.set(_key, [])
}



export function sort_arr<T>(_array: Array<T>, _compareFn: (a: T, b: T) => number): Array<T> {
  return _array.slice().sort(_compareFn)
}


export function or_err<T>(_x: T | undefined, msg: string): T {
  if (_x === undefined) throw new AnyError(msg)
  return _x
}



export const TRIM_WITH = "..."
export function shorten_begin(_str: string, _maxLen: number): string {
  /*
    Shorten string from the beginning if it
    exceeds `_maxLen`
  */
  if (_maxLen <= TRIM_WITH.length) {}
  return ""
}



export function element_by_id(_id: string): HTMLElement {
  const element = document.getElementById(_id);
  if (!element)
    throw new AnyError(`No element with id '${_id}' found.`);
  return element;
}



export function input_element_by_id(_id: string): HTMLInputElement {
  const element = document.getElementById(_id) as HTMLInputElement;
  if (!element)
    throw new AnyError(`No input field with id '${_id}' found.`);
  return element;
}



export function elements_by_class(_class: string): HTMLElement[] {
  const elements = document.getElementsByClassName(_class);
  if (!elements)
    throw new AnyError(`No elements with class '${_class}' found.`);
  return Array.from(elements) as HTMLElement[];
}



export function to_str(_x: unknown): string {
  if (typeof _x === "string")
    return _x
  if (_x === null || _x === undefined)
    return String(_x)
  try {
    return typeof (_x as any).toString === "function" ? (_x as any).toString() : JSON.stringify(_x)
  } catch {
    try { return JSON.stringify(_x) }
    catch { return String(_x) }
  }
}



export async function sleep(_ms: number): Promise<void> {
  return new Promise(resolve => setTimeout(resolve, _ms));
}



export function time_to_str() {
  // Returns HH:MM:SS-DD:MM:YYYY
  const n = new Date()
  const p = (n: number) => n.toString().padStart(2, "0")
  return `${p(n.getHours())}:${p(n.getMinutes())}:${p(n.getSeconds())}-${p(n.getDate())}:${p(n.getMonth() + 1)}:${n.getFullYear()}`
}



export function separate(_str: string, _sep: string): string[] {
  const result: string[] = []
  let current = ""
  for (const c of _str) {
    if (c === _sep) {
      result.push(current)
      current = ""
    } else {
      current += c
    }
  }
  result.push(current)
  return result
}



export class AnyError extends Error {
  constructor(...msgs: unknown[]) {
    const where = process.cwd()
    const reason = msgs.map(to_str).join("")
    super(`cslib::AnyError at ${where} because: ${reason}`)
  }
}



export const enum ANSII_ESCAPE {
  BOLD = "\u001b[1m",
  ITALIC = "\u001b[3m",
  UNDERLINE = "\u001b[4m",
  STRIKETHROUGH = "\u001b[9m",
  RESET = "\u001b[0m",
  BLACK = "\u001b[30m",
  RED = "\u001b[31m",
  GREEN = "\u001b[32m",
  YELLOW = "\u001b[33m",
  BLUE = "\u001b[34m",
  MAGENTA = "\u001b[35m",
  CYAN = "\u001b[36m",
  WHITE = "\u001b[37m"
}
export class Out {
  silence: boolean = false
  suffix: string = ""
  prefix: string
  constructor(_prefix: string, _color?: ANSII_ESCAPE) {
    this.prefix = _prefix
    if (_color)
      this.prefix = _color + this.prefix + ANSII_ESCAPE.RESET
  }

  print(..._args: any[]) {
    if (!this.silence)
      console.log(`[${time_to_str()}]${this.prefix}${this.suffix}`, ..._args)
  }
}



export const enum RoadStatus {
  FILE = "FILE",
  FOLDER = "FOLDER",
  BLOCK_DEVICE = "BLOCK_DEVICE",
  CHAR_DEVICE = "CHAR_DEVICE",
  SYMLINK = "SYMLINK",
  FIFO = "FIFO",
  SOCKET = "SOCKET"
}
type road_t = Road | Folder | BizarreRoad
export const pathSep = is_windows() ? "\\" : "/"
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


  constructor(_lookFor: string, _shouldBeOfType?: RoadStatus) {
    /*
      Find and resolve the absolute path of _lookFor
      with optional check to _shouldBeOfType
    */
    this.isAt = path.resolve(_lookFor)
    if (_shouldBeOfType)
      if (this.self_type() !== _shouldBeOfType)
        throw new AnyError(`Expected type "${_shouldBeOfType}" from "${this.isAt}" but got "${this.self_type()}"`)
  }


  abstract cpy(): Road
  del(): void {} // Skipped because nothing to destruct


  self_type(): RoadStatus {
    switch (fs.lstatSync(this.isAt).mode & fs.constants.S_IFMT) {
      case fs.constants.S_IFREG: return RoadStatus.FILE
      case fs.constants.S_IFDIR: return RoadStatus.FOLDER
      case fs.constants.S_IFBLK: return RoadStatus.BLOCK_DEVICE
      case fs.constants.S_IFCHR: return RoadStatus.CHAR_DEVICE
      case fs.constants.S_IFLNK: return RoadStatus.SYMLINK
      case fs.constants.S_IFIFO: return RoadStatus.FIFO
      case fs.constants.S_IFSOCK: return RoadStatus.SOCKET
      default: throw new AnyError(`Unknown road type ${fs.lstatSync(this.isAt).mode} for path: ${this.isAt}`)
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
    super(_lookFor)
    if (this.self_type() === RoadStatus.FILE || this.self_type() === RoadStatus.FOLDER)
      throw new AnyError(`"${_lookFor}" is a regular file or directory`)
  }


  override cpy(): BizarreRoad { return new BizarreRoad(this.isAt) }


  override copy_self_into(_copyInto: Folder): BizarreRoad {
    /*
      Attempt to copy the special file using system utilities
    */
    const destPath = path.join(_copyInto.isAt, this.name())
    if (fs.existsSync(destPath))
      throw new AnyError(`Copying to "${destPath}" would overwrite an existing entry`)
    if (this.self_type() === RoadStatus.SYMLINK) {
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
    super(_lookFor, RoadStatus.FOLDER)
  }


  override cpy(): Folder { return new Folder(this.isAt) }


  list(): Array<road_t> {
    return fs.readdirSync(this.isAt).map(name => {
      const fullPath = path.join(this.isAt, name)
      switch (fs.lstatSync(fullPath).mode & fs.constants.S_IFMT) {
        case fs.constants.S_IFDIR: return new Folder(fullPath)
        case fs.constants.S_IFREG: return new File(fullPath)
        case fs.constants.S_IFLNK: return new BizarreRoad(fullPath)
        case fs.constants.S_IFBLK: return new BizarreRoad(fullPath)
        case fs.constants.S_IFCHR: return new BizarreRoad(fullPath)
        case fs.constants.S_IFIFO: return new BizarreRoad(fullPath)
        case fs.constants.S_IFSOCK: return new BizarreRoad(fullPath)
        default: throw new AnyError(`Unknown file type for path: ${fullPath}`)
      }
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

    if (!fs.existsSync(path.join(this.isAt, _lookFor)))
      return undefined

    switch (fs.lstatSync(path.join(this.isAt, _lookFor)).mode & fs.constants.S_IFMT) {
      case fs.constants.S_IFDIR: return new Folder(path.join(this.isAt, _lookFor))
      case fs.constants.S_IFREG: return new File(path.join(this.isAt, _lookFor))
      case fs.constants.S_IFLNK: return new BizarreRoad(path.join(this.isAt, _lookFor))
      case fs.constants.S_IFBLK: return new BizarreRoad(path.join(this.isAt, _lookFor))
      case fs.constants.S_IFCHR: return new BizarreRoad(path.join(this.isAt, _lookFor))
      case fs.constants.S_IFIFO: return new BizarreRoad(path.join(this.isAt, _lookFor))
      case fs.constants.S_IFSOCK: return new BizarreRoad(path.join(this.isAt, _lookFor))
      default: throw new AnyError(`Unknown file type for path: ${_lookFor}`)
    }
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
    super(_lookFor, RoadStatus.FILE)
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