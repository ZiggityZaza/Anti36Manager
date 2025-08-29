// Logic comes here
import * as fs from "node:fs"
import * as os from "node:os"
import * as cs from "./cslib.js"



const A36M_CONFIGS: {
  galleryFolder: string // Path to gallery folder
  unsortedFolder: string // Path to unsorted folder
  tagsLookup: Record<tag_t, string>
  [extra: string]: any
} = JSON.parse(new cs.File(os.homedir() + "/Anti36Manager.json", true).read_text())
const GALLERY_FOLDER = new cs.Folder(A36M_CONFIGS.galleryFolder)
const UNSORTED_FOLDER = new cs.Folder(A36M_CONFIGS.unsortedFolder)
const TAGS_LOOKUP: Map<tag_t, string> = new Map([ // would be in A36M_CONFIGS but debugging rn
  ['A', "_A"],
  // ...
  ['Z', "_Z"],
  ['a', "_a"],
  // ...
  ['z', "_z"],
  ['0', "_0"],
  // ...
  ['9', "_9"]
])


const enum MediaType {
  IMAGE = "IMAGE",
  VIDEO = "VIDEO"
}
type tag_t = string // Key to represent tags



// Lookups
const EXTENSION_TO_MEDIA: Record<string, MediaType> = {
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
let folders: cs.Folder[] = []
let files: cs.File[] = []
let unsortedPortrayalsPaths: cs.Road[] = []


// Containers for easy access
let personasByOrigin: Map<Origin, Persona[]> = new Map();
let portrayalsByPersona: Map<Persona, Portrayal[]> = new Map();
let portrayalsByTag: Map<tag_t, Portrayal[]> = new Map();
let portrayalsByType: Map<MediaType, Portrayal[]> = new Map();




class Origin {
  readonly name: string
  constructor(_name: string) {
    this.name = _name
    new cs.Folder(GALLERY_FOLDER.isAt + "/" + _name) // Run constructor for checks
    if (personasByOrigin.has(this))
      throw new cs.AnyError(`Origin "${this.name}" already exists in personasByOrigin`)
    personasByOrigin.set(this, [])
  }
}
class Persona {
  readonly origin: Origin
  readonly name: string
  constructor(_origin: Origin, _name: string) {
    this.origin = _origin
    this.name = _name
    new cs.Folder(GALLERY_FOLDER.isAt + "/" + _origin.name + "/" + _name) // Run constructor for checks
    cs.add_self_to_map(personasByOrigin, this.origin, this)
  }
}
class Portrayal {
  readonly index: number
  readonly persona: Persona
  readonly tags: tag_t[]
  constructor(_index: number, _persona: Persona, _tags?: tag_t[]) {
    this.index = _index
    this.persona = _persona

    // Find self in filesystem
    let imAt: cs.File | undefined = undefined
    for (const entry of new cs.Folder(GALLERY_FOLDER.isAt + "/" + this.persona.origin.name + "/" + this.persona.name).list())
      if (entry instanceof cs.File && entry.isAt.startsWith(cs.to_str(this.index)))
        if (imAt === undefined)
          imAt = entry
        else
          throw new cs.AnyError(`This portrayal (${imAt.isAt}) and ${entry.isAt} have the same index`)
    if (imAt === undefined)
      throw new cs.AnyError(`No file found for portrayal with index ${this.index} in persona ${this.persona.name}`)
  
    // Determine own tags
    const tagsRaw = cs.separate(imAt.name(), '_').at(1) // Something like "12aB"
    this.tags = []
    if (!_tags) {
      if (tagsRaw === undefined)
        throw new cs.AnyError(`No tags found for portrayal ${imAt.isAt}`)
      for (const char of tagsRaw) {
        if (!(char in TAGS_LOOKUP))
          throw new cs.AnyError(`Invalid tag character "${char}" found for portrayal ${imAt.isAt}`)
        if (this.tags.includes(char))
          throw new cs.AnyError(`Duplicate tag "${char}" found for portrayal ${imAt.isAt}`)
        this.tags.push(char)
      }
    } else {
      this.tags = _tags
    }

    // Register portrayal
    const ownType: MediaType = EXTENSION_TO_MEDIA[imAt.extension()] || (() => { throw new cs.AnyError(`Unsupported file extension "${imAt.extension()}" in portrayal ${imAt.isAt}`) })()
    cs.add_self_to_map(portrayalsByPersona, this.persona, this)
    cs.add_self_to_map(portrayalsByType, ownType, this)
    for (const tag of this.tags)
      cs.add_self_to_map(portrayalsByTag, tag, this)
  }
}