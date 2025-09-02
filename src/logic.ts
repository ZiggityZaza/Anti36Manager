/*
  Contains the logic for managing media files
*/
import * as os from "node:os"
import * as cs from "./cslib.js"


export const enum MediaType {
  IMAGE = "IMAGE",
  VIDEO = "VIDEO"
}
export type tag_t = string // Key to represent tags

export const A36M_CONFIGS: {
  galleryFolder: string // Path to gallery folder
  unsortedFolder: string // Path to unsorted folder
  tagsLookup: Record<tag_t, string>
  [extra: string]: any
} = JSON.parse(new cs.File(os.homedir() + cs.pathSep + "Anti36Manager.json", true).read_text())
export const GALLERY_FOLDER = new cs.Folder(A36M_CONFIGS.galleryFolder)
export const UNSORTED_FOLDER = new cs.Folder(A36M_CONFIGS.unsortedFolder)
export const TAGS_LOOKUP: Record<tag_t, string> = A36M_CONFIGS.tagsLookup
export const out: cs.Out = new cs.Out("[Anti36Manager]", cs.ANSII_ESCAPE.CYAN)



export function toggle_out(): void {
  out.silence = !out.silence
}


// Lookups
export const EXTENSION_TO_MEDIA: Record<string, MediaType> = {
  ".mp4": MediaType.VIDEO,
  ".webm": MediaType.VIDEO,
  ".mkv": MediaType.VIDEO,
  ".avi": MediaType.VIDEO,
  ".mov": MediaType.VIDEO,
  ".jpg": MediaType.IMAGE,
  ".jpeg": MediaType.IMAGE,
  ".png": MediaType.IMAGE,
  ".gif": MediaType.IMAGE,
  ".bmp": MediaType.IMAGE,
  ".webp": MediaType.IMAGE
}


// Access
export let personasByOrigin: Map<Origin, Persona[]> = new Map(); // Owns origins and personas
export let portrayalsByPersona: Map<Persona, Portrayal[]> = new Map(); // Owns portrayals


// Containers for easy access
export let portrayalsByTag: Map<tag_t, Portrayal[]> = new Map();
export let portrayalsByType: Map<MediaType, Portrayal[]> = new Map();




export class Origin {
  readonly name: string

  constructor(_name: string) {
    this.name = _name
    cs.add_key_to_map(personasByOrigin, this)
  }

  where(): cs.Folder {
    return new cs.Folder(GALLERY_FOLDER.isAt + "/" + this.name)
  }
}


export class Persona {
  readonly origin: Origin
  readonly name: string

  constructor(_origin: Origin, _name: string) {
    this.origin = _origin
    this.name = _name
    cs.add_val_to_map(personasByOrigin, this.origin, this)
  }

  where(): cs.Folder {
    return new cs.Folder(GALLERY_FOLDER.isAt + "/" + this.origin.name + "/" + this.name)
  }
}


export class Portrayal {
  readonly index: number
  readonly persona: Persona
  constructor(_index: number, _persona: Persona) {
    /*
      Does extended initialization and validation
      Naming conversion:
        <index>_<tags>_.<extension>
    */
    this.index = _index // Zero-based
    this.persona = _persona
    // Register portrayal
    cs.add_val_to_map(portrayalsByPersona, this.persona, this)
    cs.add_val_to_map(portrayalsByType, this.type(), this)
    for (const tag of this.tags())
      cs.add_val_to_map(portrayalsByTag, tag, this)
  }

  where(): cs.File {
    // Find self in filesystem
    const parent = new cs.Folder(GALLERY_FOLDER.isAt + "/" + this.persona.origin.name + "/" + this.persona.name)
    let imAt: cs.File | undefined = undefined
    for (const entry of parent.list())
      if (entry instanceof cs.File && cs.separate(entry.name(), '_').at(0) === cs.to_str(this.index))
        if (!imAt)
          imAt = entry
        else
          throw new cs.AnyError(`This portrayal (${imAt.isAt}) and ${entry.isAt} have the same index`)
    return cs.or_err(imAt, `No file found for portrayal with index ${this.index} in persona ${this.persona.name}`)
  }

  type(): MediaType {
    return cs.or_err(EXTENSION_TO_MEDIA[this.where().extension()], `Unsupported file extension '${this.where().extension()}' in portrayal ${this.where().isAt}`)
  }

  tags(): tag_t[] {
    // Determine own tags
    const tagsRaw = cs.separate(this.where().name(), '_').at(1) // Something like "12aB"
    let existingTags: tag_t[] = []
    if (tagsRaw === undefined)
      throw new cs.AnyError(`No tags found for portrayal ${this.where().isAt}`)
    for (const char of tagsRaw) {
      if (!(char in TAGS_LOOKUP))
        throw new cs.AnyError(`Invalid tag character '${char}' found for portrayal ${this.where().isAt}`)
      if (existingTags.includes(char))
        throw new cs.AnyError(`Duplicate tag '${char}' found for portrayal ${this.where().isAt}`)
      existingTags.push(char)
    }
    return existingTags
  }
}



export function find_origin(_byName: string): Origin {
  for (const origin of personasByOrigin.keys())
    if (origin.name === _byName)
      return origin
  throw new cs.AnyError(`Origin '${_byName}' not found`)
}

export function find_persona(_byName: string, _origin: Origin): Persona {
  for (const persona of personasByOrigin.get(_origin)!)
    if (persona.name === _byName)
      return persona
  throw new cs.AnyError(`Persona '${_byName}' not found in origin '${_origin.name}'`)
}

export function find_portrayal(_byIndex: number, _persona: Persona): Portrayal {
  return cs.or_err(portrayalsByPersona.get(_persona)?.find(portrayal => portrayal.index === _byIndex), `Portrayal with index '${_byIndex}' not found in persona '${_persona.name}'`)
}



export function list_origins(): Origin[] {
  return Array.from(personasByOrigin.keys())
}

export function list_all_personas(_fromOrigin?: Origin): Persona[] {
  if (_fromOrigin) {
    return Array.from(personasByOrigin.get(_fromOrigin)!)
  }
  return Array.from(personasByOrigin.values()).flat()
}

export function list_all_portrayals(_fromPersona?: Persona): Portrayal[] {
  if (_fromPersona) {
    return Array.from(portrayalsByPersona.get(_fromPersona)!)
  }
  return Array.from(portrayalsByPersona.values()).flat()
}

export function list_all_unsorted_portrayals(_existing?: (cs.File | cs.Folder)[], _lookIn = UNSORTED_FOLDER): cs.File[] {
  let result: cs.File[] = []
  for (const entry of _lookIn.list()) {
    if (entry instanceof cs.Folder)
      result = result.concat(list_all_unsorted_portrayals(_existing, entry))
    else if (entry instanceof cs.File)
      result.push(entry)
    else
      throw new cs.AnyError(`Unexpected entry found: '${entry.isAt}' (expected either portrayals or subfolders containing portrayals)`)
  }
  result.sort((a, b) => a.last_modified().getTime() - b.last_modified().getTime());
  return result;
}



export function tag_key_exists(_char: string): string | undefined {
  /*
    Find `_char` as key in TAGS_LOOKUP
  */
  return Object.keys(TAGS_LOOKUP).find(key => key === _char)
}

export function tag_meaning_exists(_meaning: string): tag_t | undefined {
  /*
    Find `_meaning` as value in TAGS_LOOKUP
  */
  return Object.values(TAGS_LOOKUP).find(value => value === _meaning)
}



export function create_portrayal(_persona: Persona, tags: string[], _fromUnsorted: cs.File): Portrayal {
  const nextOpenIndex = portrayalsByPersona.get(_persona)?.length ?? 0
  let tagsCharAsRow = ""
  for (const tag of tags)
    tagsCharAsRow += cs.or_err(tag_meaning_exists(tag), `Unknown tag '${tag}'`)
  _fromUnsorted.move_self_into(new cs.Folder(`${_persona.where().isAt}/${nextOpenIndex}_${tagsCharAsRow}_${_fromUnsorted.extension()}`))
  return new Portrayal(nextOpenIndex, _persona)
}



// Initialize
export function read_A36() {
  out.suffix = "[read_A36]"
  out.print(`Reading content of '${GALLERY_FOLDER.isAt}'...`)
  const entries = GALLERY_FOLDER.list()
  for (const originLayer of entries) {
    if (!(originLayer instanceof cs.Folder))
      throw new cs.AnyError(`Unexpected entry found: '${originLayer.isAt}' (expected first-layer origin folders)`)
    out.print(`Found origin folder: ${originLayer.isAt}`)
    const origin = new Origin(originLayer.name())
    for (const personaLayer of originLayer.list()) {
      if (!(personaLayer instanceof cs.Folder))
        throw new cs.AnyError(`Unexpected entry found: '${personaLayer.isAt}' (expected second-layer persona folders)`)
      out.print(`Found persona folder: ${personaLayer.isAt}`)
      const persona = new Persona(origin, personaLayer.name())
      let expectedIndex = 0
      for (const portrayalLayer of personaLayer.list()) {
        if (!(portrayalLayer instanceof cs.File))
          throw new cs.AnyError(`Unexpected entry found: '${portrayalLayer.isAt}' (expected third/final-layer portrayal files)`)
        out.print(`Found portrayal file: ${portrayalLayer.isAt}`)
        new Portrayal(expectedIndex++, persona)
      }
    }
  }
  out.print(`Finished reading. Found ${list_origins().length} origins, ${list_all_personas().length} personas and ${list_all_portrayals().length} portrayals.`)
}





export function lets_go() {
  console.log("Thank you so much for using the infamous and powerful Anti36Manager!")
  console.log("This software is still in early development, so please report any issues you find.")
  console.log("You can find the project at https://github.com/ZiggityZaza/Anti36Manager")
  console.log("Have fun! <3")
  console.log("Initializing...")
  read_A36()
}