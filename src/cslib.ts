/*
  Provides basic utilities
*/
import * as fs from "node:fs"
import * as path from "node:path"
import * as os from "node:os"
import { spawnSync } from "node:child_process"



// Helper just in case
export let LAST_ERROR: Error | null = null // Only works for throws with this lib



// Vanilla functions (regardless of Node or Web)
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



export abstract class AnyError extends Error {
  constructor(_msg: string) {
    super(`cslib.AnyError because: ${_msg}`)
    LAST_ERROR = this
  }
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



export function range(_from: number, _to?: number, _step: number = 1): Array<number> {
  if (_to === undefined)
    [_from, _to] = [0, _from] // If only one way
  let result: Array<number> = []
  if (_from < _to)
    for (let i = _from; i < _to; i += _step)
      result.push(i)
  else if (_from > _to)
    for (let i = _from; i > _to; i -= _step)
      result.push(i)
  return result
}



export function sort_arr<T>(_array: Array<T>, _compareFn: (a: T, b: T) => number): Array<T> {
  return _array.slice().sort(_compareFn)
}



export function or_err<T>(_x: T | undefined | null, _msg: string, ErrCtor: new (msg: string) => Error | Error): T {
  if (_x === undefined || _x === null)
    throw new ErrCtor(_msg)
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



export function time_to_str() {
  // Returns HH:MM:SS-DD:MM:YYYY
  const n = new Date()
  const p = (n: number) => n.toString().padStart(2, "0")
  return `${p(n.getHours())}:${p(n.getMinutes())}:${p(n.getSeconds())}-${p(n.getDate())}:${p(n.getMonth() + 1)}:${n.getFullYear()}`
}



export async function sleep(_ms: number): Promise<void> {
  return new Promise(resolve => setTimeout(resolve, _ms));
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



export function read_json_as<Interface>(_jsonContentAsStr: string): Interface {
  return JSON.parse(_jsonContentAsStr) as Interface
}




// Node specific (comment out if no node access)
export const IS_WINDOWS = os.platform() === "win32"



export const enum RoadT {
  FILE = "FILE",
  FOLDER = "FOLDER",
  BLOCK_DEVICE = "BLOCK_DEVICE",
  CHAR_DEVICE = "CHAR_DEVICE",
  SYMLINK = "SYMLINK",
  FIFO = "FIFO",
  SOCKET = "SOCKET"
}
export function to_RoadT(_pathorMode: string | number): RoadT {
  const mode = typeof _pathorMode === "string" ? fs.lstatSync(_pathorMode).mode : _pathorMode
  switch (mode & fs.constants.S_IFMT) {
    case fs.constants.S_IFREG: return RoadT.FILE
    case fs.constants.S_IFDIR: return RoadT.FOLDER
    case fs.constants.S_IFBLK: return RoadT.BLOCK_DEVICE
    case fs.constants.S_IFCHR: return RoadT.CHAR_DEVICE
    case fs.constants.S_IFLNK: return RoadT.SYMLINK
    case fs.constants.S_IFIFO: return RoadT.FIFO
    case fs.constants.S_IFSOCK: return RoadT.SOCKET
    default: throw new Error(`Unknown mode type ${mode} for path/mode: '${_pathorMode}'`)
  }
}

export class RoadErr extends Error {
  /*
    Custom error class involving problematic attempts
    to handle the underlying Road
  */
  readonly self: Road
  constructor(_self: Road, _because: unknown) {
    super(`cslib.RoadErr (path: '${_self.isAt}', type: ${_self.type()}) because: ${_because}`)
    this.self = _self
    LAST_ERROR = this
  }
}

export function road_factory(_lookFor: string): Road {
  const entryType = to_RoadT(_lookFor)
  if (entryType === RoadT.FOLDER)
    return new Folder(_lookFor)
  else if (entryType === RoadT.FILE)
    return new File(_lookFor)
  else
    return new BizarreRoad(_lookFor)
}


export abstract class Road {
  /*
    Abstract base class for filesystem entries.
    Represents a path in the filesystem and provides
    methods to manage it. Think of it as a pointer
    for stuff on disk.
    Note:
      Copying/Moving/changing the object won't change
      the represented entry on the disk.
    Example:
      0x123 as int* -> 42 those 4 bytes on stack/heap/seg/reg/...
      File("/ex.txt") -> the actual file on disk
  */
  isAt: string


  constructor(_lookFor: string) {
    /*
      Find and resolve the absolute path of _lookFor
      with optional check to _shouldBeOfType
    */
    if (!fs.existsSync(_lookFor))
      throw new RoadErr(this, "Not found")
    this.isAt = path.resolve(_lookFor)
  }


  abstract exists(): boolean


  type(): RoadT {
    return to_RoadT(this.isAt)
  }


  depth(): number {
    return this.isAt.split(path.sep).length - 1
  }


  name(): string {
    return path.basename(this.isAt)
  }


  last_modified(): Date {
    return fs.statSync(this.isAt).mtime
  }
  created_on(): Date {
    return fs.statSync(this.isAt).birthtime
  }


  stats(): fs.Stats {
    return fs.statSync(this.isAt)
  }


  cpy(_prevPath = this.isAt): this {
    return new (this.constructor as any)(_prevPath) as this
  }


  parent(): Folder {
    return new Folder(path.dirname(this.isAt))
  }


  layer(_index: number): Folder {
    /*
      Find parent paths by layer
      Example:
        const f = new Folder("/root/projects/folder")
        const root: Folder = f.layer(0)
        const parent: Folder = f.layer(f.depth() - 1) // 3 - 1
    */
    let parent: Folder = new Folder("./") // Dummy initialization
    if (_index >= this.depth() || _index < 0)
      throw new RoadErr(this, `Invalid index: Tried ${_index}, but max is ${this.depth() - 1}`)
    for (let _ of range(this.depth() - _index))
      parent = parent.parent()
    return parent
  }


  rename_self_to(_newName: string): void {
    if (_newName.includes(path.sep))
      throw new RoadErr(this, `Invalid name: '${_newName}' is path-like`)
    const newPath = path.join(this.parent().isAt, _newName)
    if (fs.existsSync(newPath))
      throw new RoadErr(this, `New name: '${newPath}' already exists`)
    fs.renameSync(this.isAt, newPath)
    this.isAt = newPath
  }


  move_self_into(_moveInto: Folder): void {
    // Default attempt to move
    const destPath = path.join(_moveInto.isAt, this.name())
    if (fs.existsSync(destPath))
      throw new RoadErr(this, `Destination: '${destPath}' already exists`)
    fs.renameSync(this.isAt, destPath)
    this.isAt = destPath
  }


  copy_self_into(_copyInto: Folder): this {
    // Default attempt to copy
    const destPath = path.join(_copyInto.isAt, this.name())
    if (fs.existsSync(destPath))
      throw new RoadErr(this, `Destination: '${destPath}' already exists`)
    if (this.type() === RoadT.SYMLINK) {
      const linkTarget = fs.readlinkSync(this.isAt)
      fs.symlinkSync(linkTarget, destPath)
    } else {
      // Trying to use 'cp' for other special files (pipes, sockets, etc.)
      const result = spawnSync("cp", ["-a", this.isAt, destPath])
      if (result.status !== 0)
        throw new RoadErr(this, `Failed to copy special file: ${result.stderr?.toString() || "unknown error"}`)
    }
    return this.cpy(destPath);
  }
}



export class BizarreRoad extends Road {
  /*
    Specifically for files that don't fit into
    the usual categories such as symbolic links
    or pipes.
  */
  readonly originalType: RoadT // To remember own type


  constructor(_lookFor: string) {
    super(_lookFor)
    this.originalType = this.type()
    if (this.originalType === RoadT.FILE || this.originalType=== RoadT.FOLDER)
      throw new RoadErr(this, `Type missmatch: ${this.originalType} is too normal (?), use File/Folder instead`)
  }


  override exists(): boolean {
    return fs.existsSync(this.isAt) && this.type() === this.originalType
  }
}



export class Folder extends Road {
  /*
    Handles folders in the file system
  */
  constructor(_lookFor: string, createIfNotExists: boolean = false) {
    if (createIfNotExists && !fs.existsSync(_lookFor))
      fs.mkdirSync(_lookFor, { recursive: true })
    super(_lookFor)
    if (this.type() !== RoadT.FOLDER)
      throw new RoadErr(this, "Type missmatch: Should be folder")
  }


  list(): Array<Road> {
    return fs.readdirSync(this.isAt).map(name => road_factory(path.join(this.isAt, name)))
  }


  find(_lookFor: string): Road | undefined {
    /*
      Check if the folder contains a file or folder with
      the given relative path. If it does, return the
      corresponding Road object.
      Note:
        Path MUST be relative
    */
    if (_lookFor.length === 0)
      throw new RoadErr(this, "Invalid path: Empty path given to lookup")
    if (IS_WINDOWS && _lookFor.at(1) === ":" && _lookFor.at(2) === "\\") // X:\
      throw new RoadErr(this, `Invalid path: Not relative: ${_lookFor}`)
    else if (!IS_WINDOWS && _lookFor.startsWith("/"))
      throw new RoadErr(this, `Invalid path: Not relative: ${_lookFor}`)

    if (!fs.existsSync(path.join(this.isAt, _lookFor)))
      return undefined
    else
      return road_factory(path.join(this.isAt, _lookFor))
  }


  override copy_self_into(_copyInto: Folder, _options: fs.CopySyncOptions = { recursive: true }): this {
    const newFolder = new Folder(path.join(_copyInto.isAt, this.name()))
    fs.cpSync(this.isAt, newFolder.isAt, _options) // Merges
    return newFolder as this
  }


  override exists(): boolean {
    return fs.existsSync(this.isAt) && this.type() === RoadT.FOLDER
  }
}



export class File extends Road {
  /*
    Handles files in the file system
  */
  constructor(_lookFor: string, createIfNotExists: boolean = false) {
    if (createIfNotExists && !fs.existsSync(_lookFor))
      fs.writeFileSync(_lookFor, "")
    super(_lookFor)
    if (this.type() !== RoadT.FILE)
      throw new RoadErr(this, "Type missmatch: Should be file")
  }


  override exists(): boolean {
    return fs.existsSync(this.isAt) && this.type() === RoadT.FILE
  }


  read_text(): string {
    return fs.readFileSync(this.isAt, "utf-8")
  }
  edit_text(_newText: string): void {
    fs.writeFileSync(this.isAt, _newText)
  }


  read_binary(): Buffer {
    return fs.readFileSync(this.isAt)
  }
  edit_binary(_newBuffer: Buffer | Uint8Array): void {
    fs.writeFileSync(this.isAt, _newBuffer)
  }


  extension(): string {
    return path.extname(this.isAt)
  }
  size_in_bytes(): number {
    return fs.statSync(this.isAt).size
  }
}




// If DOM exists
export namespace DOM {
  export class DOMErr extends Error {
    constructor(_identifier: string, _msg: string) {
      super(`cslib.DOMErr from class or id '${_identifier}' because: ${_msg}`)
      LAST_ERROR = this
    }
  }



  export function by_id<T extends HTMLElement>(_id: string, _elementType: new() => T): T {
    const element = document.getElementById(_id)
    if (!element)
      throw new DOMErr(_id, "Not found")
    if (!(element instanceof _elementType))
      throw new DOMErr(_id, `Type missmatch: Element is not of type ${_elementType.name}`)
    return element as T
  }



  export function by_class<T extends HTMLElement>(_className: string, _elementType: new() => T): T[] {
    const cleanClass = _className.startsWith('.') ? _className.slice(1) : _className
    const elements = document.querySelectorAll(`.${cleanClass}`)
    const result: T[] = []

    elements.forEach((element, index) => {
      if (!(element instanceof _elementType))
        throw new DOMErr(_className, `Type missmatch at index ${index}: Element is not of type ${_elementType.name}`)
      result.push(element as T)
    })
    
    return result
  }



  // export function by_class_HTMLVidEl_Or_HTMLImgEl(arg0: string, arg1: number): (HTMLVideoElement | HTMLImageElement)[] {
  //   const rawElements = document.getElementsByClassName(arg0)
  //   const result: (HTMLVideoElement | HTMLImageElement)[] = []
  //   for (let i = 0; i < rawElements.length; i++) {
  //     const el = rawElements.item(i)
  //     if (el instanceof HTMLVideoElement || el instanceof HTMLImageElement) {
  //       result.push(el)
  //     } else {
  //       throw new DOMErr(arg0, `Type missmatch at index ${i}: Element is not of type HTMLVideoElement or HTMLImageElement`)
  //     }
  //   }
  //   return result
  // }
}