/*
  Contains the logic for managing media files
  Note:
    For consistency, don't use Web/DOM-related code here
*/
import * as os from "node:os"
import * as fs from "node:fs"
import * as path from "node:path"
import * as cs from "./cslib.js"

export const enum MediaT {
  IMAGE = "IMAGE",
  VIDEO = "VIDEO"
}


import A36M_CONFIGS from "E:/a36s.json" with { type: "json" }; // Placeholder
export const GALLERY_FOLDER = new cs.Folder(false, A36M_CONFIGS.galleryFolder)
export const UNSORTED_FOLDER = new cs.Folder(false, A36M_CONFIGS.unsortedFolder)


// Lookups
export const EXTENSION_TO_MEDIA: { [ext: string]: MediaT } = {
  ".mp4": MediaT.VIDEO,
  ".webm": MediaT.VIDEO,
  ".mkv": MediaT.VIDEO,
  ".avi": MediaT.VIDEO,
  ".mov": MediaT.VIDEO,
  ".jpg": MediaT.IMAGE,
  ".jpeg": MediaT.IMAGE,
  ".png": MediaT.IMAGE,
  ".gif": MediaT.IMAGE,
  ".bmp": MediaT.IMAGE,
  ".webp": MediaT.IMAGE
} as const
export const TAGS_LOOKUP = {
  'A': "_A", /*...*/ 'Z': "_Z",
  'a': "_a", /*...*/ 'z': "_z",
  '0': "_0", /*...*/ '9': "_9",
} as const
export type TagT = keyof typeof TAGS_LOOKUP



export class A36Err extends cs.AnyError {
  constructor(_msg: string) {
    super("logic.A36LogicErr: " + _msg)
  }
}



export class MediaErr extends A36Err {
  readonly self: Portrayal | Persona | Origin


  constructor(_self: Portrayal | Persona | Origin, _msg: string) {
    let fullMessage = "logic.MediaErr: ("
    if (_self instanceof Portrayal)
      fullMessage += `portrayal index=${_self.index} in persona='${_self.persona.name}' of origin='${_self.persona.origin.name}'`
    else if (_self instanceof Persona)
      fullMessage += `persona='${_self.name}' of origin='${_self.origin.name}'`
    else if (_self instanceof Origin)
      fullMessage += `origin='${_self.name}'`
    super(fullMessage + ") because " + _msg)
    this.self = _self
  }
}




export function find_origin(_byName: string): Origin | undefined {
  return new Origin(_byName)
}



export function list_origins(): Origin[] {
  return GALLERY_FOLDER.list().map(folder => new Origin(folder.name()))
}


export class Origin {
  readonly name: string

  constructor(_name: string) {
    /*
      Integrate and return new origin into the Anti36
      ecosystem
    */
    this.name = _name
    // personasByOrigin.set(this, personasByOrigin.get(this) || [])
  }

  where(): cs.Folder {
    return new cs.Folder(false, GALLERY_FOLDER.isAt, this.name)
  }

  list_personas(): Persona[] {
    return this.where().list().map(folder => new Persona(this, folder.name()))
  }

  find_persona(_byName: string): Persona | undefined {
    return this.list_personas().find(persona => persona.name === _byName)
  }
}


export class Persona {
  readonly origin: Origin
  readonly name: string

  constructor(_origin: Origin, _name: string) {
    /*
      Integrate and return new persona into the Anti36
      ecosystem
    */
    this.origin = _origin
    this.name = _name
  }

  where(): cs.Folder {
    return new cs.Folder(false, GALLERY_FOLDER.isAt, this.origin.name, this.name)
  }

  list_portrayals(): Portrayal[] {
    return this.where().list().map((_, index) => new Portrayal(index, this));
  }

  find_portrayal(_byIndex: number): Portrayal | undefined {
    return this.list_portrayals().find(portrayal => portrayal.index === _byIndex)
  }
}


export class Portrayal {
  readonly index: number
  readonly persona: Persona

  constructor(_index: number, _persona: Persona) {
    this.index = _index
    this.persona = _persona
  }

  where(): cs.File {
    for (const entry of this.persona.where().list())
      if (entry instanceof cs.File && entry.name().split('_')[0] === String(this.index))
        return entry
    throw new MediaErr(this, `Couldn't find self in persona folder`)
  }

  type(): MediaT {
    return EXTENSION_TO_MEDIA[this.where().extension()]!
  }

  tags(): TagT[] {
    return this.where().name().split('_')[1]!.split('').map(tag => tag as TagT) // Something like "1a2B"
  }
}



export function list_all_unsorted_portrayals(_existing?: cs.File[], _lookIn = UNSORTED_FOLDER): cs.File[] {
  let result: cs.File[] = []
  for (const entry of _lookIn.list()) {
    if (entry instanceof cs.Folder)
      result = result.concat(list_all_unsorted_portrayals(_existing, entry))
    else if (entry instanceof cs.File)
      result.push(entry)
  }
  result.sort((a, b) => a.last_modified().getTime() - b.last_modified().getTime());
  return result;
}



export function tag_key_exists(_char: string): string | undefined {
  return Object.keys(TAGS_LOOKUP).find(key => key === _char)
}

export function tag_meaning_exists(_meaning: string): TagT | undefined {
  return Object.entries(TAGS_LOOKUP).find(([_, value]) => value === _meaning)?.[0] as TagT | undefined
}



export function create_portrayal(_persona: Persona, _tags: TagT[], _fromUnsorted: cs.File): Portrayal {
  const nextOpenIndex = _persona.list_portrayals().length
  _fromUnsorted.rename_self_to(`A36M_TEMP_${Math.random().toString(36)}${_fromUnsorted.extension()}`) // Temporary random name to avoid conflicts
  _fromUnsorted.move_self_into(_persona.where())
  _fromUnsorted.rename_self_to(`${nextOpenIndex}_${_tags.join("")}_${_fromUnsorted.extension()}`)
  return new Portrayal(nextOpenIndex, _persona)
}