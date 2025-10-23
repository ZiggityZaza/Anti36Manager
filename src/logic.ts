/*
  Contains the logic for managing media files
*/
import * as os from "node:os"
import * as path from "node:path"
import * as cs from "./cslib.js"


export const enum MediaT {
  IMAGE = "IMAGE",
  VIDEO = "VIDEO"
}
export type TagChar = string // Key to represent 


export const DEFAULT_A36_CONFIG_PATH = path.join(os.homedir(), "Anti36Manager.json")
export const A36M_CONFIGS: {
  galleryFolder: string // Path to gallery folder
  unsortedFolder: string // Path to unsorted folder
  tagsLookup: Record<TagChar, string>
  [extra: string]: any
} = JSON.parse(new cs.File(DEFAULT_A36_CONFIG_PATH).read_text())
export const GALLERY_FOLDER = new cs.Folder(A36M_CONFIGS.galleryFolder)
export const UNSORTED_FOLDER = new cs.Folder(A36M_CONFIGS.unsortedFolder)
export const TAGS_LOOKUP: Record<TagChar, string> = A36M_CONFIGS.tagsLookup
export const out: cs.Out = new cs.Out("[Anti36Manager]", cs.ANSII_ESCAPE.CYAN)


export function toggle_out(): void {
  out.silence = !out.silence
}


// Lookups
export const EXTENSION_TO_MEDIA: Record<string, MediaT> = {
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
}


// Access
export let personasByOrigin: Map<Origin, Persona[]> = new Map(); // Owns origins and personas
export let portrayalsByPersona: Map<Persona, Portrayal[]> = new Map(); // Owns portrayals


// Containers for easy access
export let portrayalsByTag: Map<TagChar, Portrayal[]> = new Map();
export let portrayalsByType: Map<MediaT, Portrayal[]> = new Map();



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


export class Origin {
  readonly name: string


  constructor(_name: string) {
    this.name = _name
    cs.add_key_to_map(personasByOrigin, this)
  }


  where(): cs.Folder {
    return new cs.Folder(path.join(GALLERY_FOLDER.isAt, this.name))
  }


  find_persona(_byName: string): Persona | undefined {
    if (!personasByOrigin.has(this) || personasByOrigin.get(this)!.length === 0)
      throw new MediaErr(this, `No personas found for this origin`)
    for (const persona of personasByOrigin.get(this)!)
      if (persona.name === _byName)
        return persona
    return undefined
  }


  list_personas(): Persona[] {
    if (!personasByOrigin.has(this))
      throw new MediaErr(this, `No personas found for this origin`)
    return Array.from(personasByOrigin.get(this)!)
  }
}


export class Persona {
  readonly origin: Origin
  readonly name: string


  constructor(_origin: Origin, _name: string) {
    this.origin = _origin
    this.name = _name
    cs.add_val_to_map(personasByOrigin, this.origin, this)
    cs.add_key_to_map(portrayalsByPersona, this)
  }

  where(): cs.Folder {
    return new cs.Folder(path.join(GALLERY_FOLDER.isAt, this.origin.name, this.name))
  }


  find_portrayal(_byIndex: number): Portrayal | undefined {
    if (!portrayalsByPersona.has(this) || portrayalsByPersona.get(this)!.length === 0)
      throw new MediaErr(this, `No portrayals found for this persona`)
    for (const portrayal of portrayalsByPersona.get(this)!)
      if (portrayal.index === _byIndex)
        return portrayal
    return undefined
  }


  list_portrayals(): Portrayal[] {
    if (!portrayalsByPersona.has(this))
      throw new MediaErr(this, `No portrayals found for this persona`)
    return Array.from(portrayalsByPersona.get(this)!)
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
    for (const entry of this.persona.where().list())
      if (entry instanceof cs.File && cs.separate(entry.name(), '_').at(0) === cs.to_str(this.index))
        return entry
    throw new MediaErr(this, `Couldn't find self in persona folder`)
  }


  type(): MediaT {
    if (!EXTENSION_TO_MEDIA[this.where().extension()])
      throw new MediaErr(this, `Unsupported file extension '${this.where().extension()}'`)
    return EXTENSION_TO_MEDIA[this.where().extension()]!
  }


  tags(): TagChar[] {
    // Determine own tags
    const tagsRaw = cs.separate(this.where().name(), '_').at(1) // Something like "1a2B"
    if (tagsRaw === undefined)
      throw new MediaErr(this, `Invalid filename format, no tags found`)

    let existingTags: TagChar[] = []
    for (const char of tagsRaw) {
      if (!(char in TAGS_LOOKUP))
        throw new MediaErr(this, `Invalid tag character '${char}' found`)
      if (existingTags.includes(char))
        throw new MediaErr(this, `Duplicate tag '${char}' found`)
      existingTags.push(char)
    }
    return existingTags
  }
}



export function find_origin(_byName: string): Origin | undefined {
  for (const origin of personasByOrigin.keys())
    if (origin.name === _byName)
      return origin
  return undefined
}



export function list_origins(): Origin[] {
  return Array.from(personasByOrigin.keys())
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
  /*
    Find `_char` as key in TAGS_LOOKUP
  */
  return Object.keys(TAGS_LOOKUP).find(key => key === _char)
}

export function tag_meaning_exists(_meaning: string): TagChar | undefined {
  /*
    Find `_meaning` as value in TAGS_LOOKUP
  */
  return Object.values(TAGS_LOOKUP).find(value => value === _meaning)
}



export function create_portrayal(_persona: Persona, _tagCharAsRow: string, _fromUnsorted: cs.File): Portrayal {
  const nextOpenIndex = portrayalsByPersona.get(_persona)?.length ?? 0
  _fromUnsorted.rename_self_to(`A36M_TEMP_${Math.random().toString(36)}${_fromUnsorted.extension()}`) // Temporary random name to avoid conflicts
  _fromUnsorted.move_self_into(new cs.Folder(_persona.where().isAt))
  _fromUnsorted.rename_self_to(`${nextOpenIndex}_${_tagCharAsRow}${_fromUnsorted.extension()}`)
  return new Portrayal(nextOpenIndex, _persona)
}



// Initialize
export function read_A36() { // TODO: More robust error handling
  out.suffix = "[read_A36]"
  out.print(`Reading content of '${GALLERY_FOLDER.isAt}'...`)
  const entries = GALLERY_FOLDER.list()
  for (const originLayer of entries) {
    if (!(originLayer instanceof cs.Folder))
      throw new A36Err(`Unexpected entry found: '${originLayer.isAt}' (expected first-layer origin folders)`)
    out.print(`Found origin folder: ${originLayer.isAt}`)
    const origin = new Origin(originLayer.name())
    for (const personaLayer of originLayer.list()) {
      if (!(personaLayer instanceof cs.Folder))
        throw new A36Err(`Unexpected entry found: '${personaLayer.isAt}' (expected second-layer persona folders)`)
      out.print(`Found persona folder: ${personaLayer.isAt}`)
      const persona = new Persona(origin, personaLayer.name())
      let expectedIndex = 0
      for (const portrayalLayer of personaLayer.list()) {
        if (!(portrayalLayer instanceof cs.File))
          throw new A36Err(`Unexpected entry found: '${portrayalLayer.isAt}' (expected third/final-layer portrayal files)`)
        out.print(`Found portrayal file: ${portrayalLayer.isAt}`)
        new Portrayal(expectedIndex++, persona)
      }
    }
  }
  out.print(`Finished reading. Found ${list_origins().length} origins, ${Array.from(personasByOrigin.values()).reduce((acc, val) => acc + val.length, 0)} personas, and ${Array.from(portrayalsByPersona.values()).reduce((acc, val) => acc + val.length, 0)} portrayals.`)
}





export function lets_go() {
  console.log("Thank you so much for using the infamous and powerful Anti36Manager!")
  console.log("This software is still in early development, so please report any issues you find.")
  console.log("You can find the project at https://github.com/ZiggityZaza/Anti36Manager")
  console.log("Have fun! <3")
  console.log("Initializing...")
  read_A36()
}