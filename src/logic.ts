/*
  Contains the logic for managing media files
  Note:
    For consistency, don't use Web/DOM-related code here
*/
import * as isb from "ts-instrumentality/node"
import * as fp from "node:fs/promises"
import * as fs from "node:fs"
import { join } from "node:path"

export const enum MediaT {
  IMAGE = "IMAGE",
  VIDEO = "VIDEO"
}


// Lookups and Constants
import A36M_CONFIGS from "E:/a36s.json" with { type: "json" } // Placeholder
export const GALLERY_FOLDER = new isb.Folder(A36M_CONFIGS.galleryFolder)
export const UNSORTED_FOLDER = new isb.Folder(A36M_CONFIGS.unsortedFolder)
export const TAGS = A36M_CONFIGS.tags
export type TagT = keyof typeof TAGS

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




export function find_origin(_byName: string): Origin | undefined {
  const folder = GALLERY_FOLDER.find_sync(_byName)
  if (folder && folder instanceof isb.Folder)
    return new Origin(folder.name())
  return undefined
}
export function list_origins(): Origin[] {
  return GALLERY_FOLDER.list_sync().map(folder => new Origin(folder.name()))
}


export class Origin {
  readonly name: string

  constructor(_name: string) {
    this.name = _name
  }

  where(): isb.Folder {
    return new isb.Folder(join(GALLERY_FOLDER.isAt, this.name))
  }

  list_personas(): Persona[] {
    return this.where().list_sync().map(folder => new Persona(this, folder.name()))
  }

  find_persona(_byName: string): Persona | undefined {
    return this.list_personas().find(persona => persona.name === _byName)
  }
}


export class Persona {
  readonly origin: Origin
  readonly name: string

  constructor(_origin: Origin, _name: string) {
    this.origin = _origin
    this.name = _name
  }

  where(): isb.Folder {
    return new isb.Folder(join(GALLERY_FOLDER.isAt, this.origin.name, this.name))
  }

  list_portrayals(): Portrayal[] {
    return this.where().list_sync(isb.File).map((File, _) => new Portrayal(Number(File.name().split('_')[0]), this))
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

  where(): isb.File {
    return Array.from(this.persona.where().list_sync(isb.File)).find(file => file.name().startsWith(`${this.index}_`))!
  }

  type(): MediaT {
    return EXTENSION_TO_MEDIA[this.where().ext()]!
  }

  tags(): TagT[] {
    return this.where().name().split('_')[1]!.split('').map(tag => tag as TagT) // Something like "1a2B"
  }
}



export function list_all_unsorted_portrayals(_lookIn: isb.Folder = UNSORTED_FOLDER, _existing?: isb.File[]): isb.File[] {
  /*
    Recursively list all files in the unsorted folder
    and its subfolders and return them as an array
    sorted by modification date
  */
  let result: isb.File[] = []
  for (const entry of _lookIn.list_sync())
    if (entry instanceof isb.Folder)
      result = result.concat(list_all_unsorted_portrayals(entry, _existing))
    else if (entry instanceof isb.File)
      result.push(entry)
  result.sort((a, b) => a.modified_sync().getTime() - b.modified_sync().getTime())
  return result
}



export async function create_portrayal(_persona: Persona, _tags: TagT[], _fromUnsorted: isb.File): Promise<Portrayal> {
  /*
    Move a file from unsorted to the given persona folder
    and rename it according to the next available index
    and given tags
  */
  await _persona.where().exists()
  const nextOpenIndex = _persona.list_portrayals().length
  await _fromUnsorted.rename(`A36M_TEMP_${Math.random().toString(36)}${_fromUnsorted.ext()}`) // Temporary random name to avoid conflicts
  await _fromUnsorted.move(_persona.where())
  await _fromUnsorted.rename(`${nextOpenIndex}_${_tags.join("")}_${_fromUnsorted.ext()}`)
  return new Portrayal(nextOpenIndex, _persona)
}