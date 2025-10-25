import * as os from "node:os"
// import React from "react" // React on idle
// import * as ReactDOM from "react-dom/client" // React on idle
import * as cs from "./cslib.js"
import * as bn from "./logic.js"
// import type { HTMLElementType } from "react"




// Resources
let isSortingMode = true
let selectedPersonaFilters: bn.Persona[] = [] // Origins and personas to filter by
let selectedTags: bn.TagT[] = []



// Handle UI elements 
const UI = {
  /*
    Contains references to important UI elements and
    functions to manipulate them.
  */
  // Dynamically accessed elements
  originSelect: cs.DOM.by_id("origin-select", HTMLInputElement),
  originList: cs.DOM.by_id("origin-list", HTMLDataListElement),
  personaSelect: cs.DOM.by_id("persona-select", HTMLInputElement),
  personaList: cs.DOM.by_id("persona-list", HTMLDataListElement),
  previewTargetID: "preview-target", // Can't be obj cuz it takes different shapes at runtime
  previews: cs.DOM.by_tag("aside")[0]!,


  // Static elements (must be configured at startup)
  confirmButton: cs.DOM.by_id("confirm", HTMLButtonElement), // Onclick event is set outside
  switchModeButton: cs.DOM.by_id("switch-mode", HTMLButtonElement), // Onclick event is set outside
  tagButtons: new Map<bn.TagT, HTMLButtonElement>(),


  // Helpers to configure static elements at startup
  set_origin_datalist(): void {
    for (const origin of bn.list_origins()) {
      const option = document.createElement("option")
      option.value = origin.name
      option.label = `with ${origin.list_personas().length} personas`
      this.originList.appendChild(option)
    }
  },


  set_persona_datalist(): void {
    /*
      Sets the persona datalist according to the origin
      input field's value.
    */
    UI.personaList.innerHTML = "" // Clear previous options

    for (const persona of bn.find_origin(UI.originSelect.value)?.list_personas() || []) {
      const option = document.createElement("option")
      option.value = persona.name
      this.personaList.appendChild(option)
    }
  },


  set_originSelect_event_handler(): void {
    UI.originSelect.addEventListener("change", () => this.set_persona_datalist())
  },


  set_personaSelect_event_handler(): void {
    UI.personaSelect.addEventListener("change", () => {
      if (!bn.find_origin(UI.originSelect.value)?.find_persona(UI.personaSelect.value)) {
        alert(`Persona '${UI.personaSelect.value}' doesn't exist`)
        UI.originSelect.value = ""
        UI.personaSelect.value = ""
      }
    })
  },


  create_new_portrayal_by_user(): void {
    console.log("create_new_portrayal_by_user")
    const persona: bn.Persona = cs.or_err(bn.find_origin(UI.originSelect.value)?.find_persona(UI.personaSelect.value))
    const previewElement = document.getElementById(UI.previewTargetID)! as HTMLImageElement | HTMLVideoElement
    console.log(previewElement.src)
    console.log(cs.rm_fileprotocol_from_src(previewElement.src))
    bn.create_portrayal(persona, selectedTags, new cs.File(cs.rm_fileprotocol_from_src(previewElement.src)))
  },


  confirm_filtering_dummy(): void {
    console.log("dummy")
  },


  set_confirm_button_onclick(): void {
    this.confirmButton.onclick = () => {
      if (isSortingMode)
        this.create_new_portrayal_by_user()
      else
        this.confirm_filtering_dummy()
    }
  },


  make_cool_color_tag_button(): string {
    return `#${Math.floor(Math.random() * 16777215).toString(16)}`
  },


  tag_button_onClick_handler(_identifier: bn.TagT): void {
    /*
      Target function for when a tag button is clicked. If
      the tag is already selected, it will unselect itself
      and vice versa.
      Note:
        This function should be called by an event listener
    */
    if (selectedTags.includes(_identifier)) {
      selectedTags = selectedTags.filter((tag) => tag !== _identifier) // Unselect
      this.tagButtons.get(_identifier)!.style.background = ""
    }
    else {
      selectedTags.push(_identifier) // Select
      this.tagButtons.get(_identifier)!.style.backgroundColor = this.make_cool_color_tag_button()
    }
  },


  create_tag_button_in_dom(_identifier: bn.TagT): HTMLButtonElement {
    /*
      Create and insert a tag button inside DOM
    */
    const button = document.createElement("button")
    button.name = _identifier
    button.type = "button"
    button.classList.add("tag-button")
    button.textContent = bn.TAGS_LOOKUP[_identifier]
    button.onclick = () => this.tag_button_onClick_handler(_identifier)
    return button
  },


  init_all_tag_buttons(): void {
    for (const [tagAsChar, meaning] of cs.entries(bn.TAGS_LOOKUP)) {
      const floatingButton = this.create_tag_button_in_dom(tagAsChar)
      cs.DOM.by_id("tags-map", HTMLElement).appendChild(floatingButton)
      this.tagButtons.set(tagAsChar, floatingButton)
    }
  },
} as const
UI.init_all_tag_buttons()
UI.set_origin_datalist()
UI.set_originSelect_event_handler()
UI.set_personaSelect_event_handler()
UI.set_confirm_button_onclick()





// Helpers
function preview_portrayal_onclick_event(_selfHtml: HTMLVideoElement | HTMLImageElement): void {
  /*
    Remove previous preview target and replace with own
  */
  cs.DOM.by_id(UI.previewTargetID, HTMLElement).remove()
  let newElement: typeof _selfHtml
  if (_selfHtml instanceof HTMLVideoElement) {
    newElement = document.createElement("video")
    newElement.controls = true
    newElement.loop = true
  }
  else
    newElement = document.createElement("img")
  cs.DOM.by_tag("main").at(0)!.appendChild(newElement)
  newElement.src = _selfHtml.src
  newElement.id = UI.previewTargetID
}



function insert_into_sidebar(_source: cs.File): HTMLImageElement | HTMLVideoElement {
  /*
    Inserts a media file into the sidebar as an
    img or vid element.
  */

  let element: HTMLImageElement | HTMLVideoElement
  if (bn.EXTENSION_TO_MEDIA[_source.extension()] === bn.MediaT.IMAGE)
    element = document.createElement("img")
  else if (bn.EXTENSION_TO_MEDIA[_source.extension()] === bn.MediaT.VIDEO) {
    element = document.createElement("video")
    element.muted = true
    element.loop = true
    element.addEventListener("mouseover", () => (element as HTMLVideoElement).play())
    element.addEventListener("mouseout", () => (element as HTMLVideoElement).pause())
  }
  else
    throw new bn.A36Err(`Unsupported media type for preview: '${_source.extension()}'`)
  element.src = _source.isAt
  element.onclick = () => preview_portrayal_onclick_event(element)
  element.classList.add("preview") // For styling
  UI.previews.appendChild(element) // Add to DOM as HTML element
  return element
}
insert_into_sidebar(new cs.File("C:\\Users\\BLECHBUCHSE\\Downloads\\hehe.webp")) // DEBUG
insert_into_sidebar(new cs.File("C:\\Users\\BLECHBUCHSE\\Downloads\\cake.png")) // DEBUG
insert_into_sidebar(new cs.File("C:\\Users\\BLECHBUCHSE\\Downloads\\YES YOUR MAJESTY.mp4")) // DEBUG








// // Directly called by user
// function switch_mode(): void {
//   isSortingMode = !isSortingMode
//   document.body.style.cursor = "wait"

//   if (isSortingMode) {
//     cs.element_by_id("ws_control_panel_add_button").innerHTML = "Add unsorted to gallery"
//     cs.element_by_id("ws_control_panel_switch_button").innerHTML = "Switch to filter view"
//     const unsorted = bn.list_all_unsorted_portrayals()
//     set_panel(`${unsorted.length} unsorted files in ${bn.UNSORTED_FOLDER.isAt}`, unsorted)
//   } else {
//     cs.element_by_id("ws_control_panel_add_button").innerHTML = "Select sorted portrayals"
//     cs.element_by_id("ws_control_panel_switch_button").innerHTML = "Switch to sorting view"
//     const sortedRaw = bn.list_all_portrayals()
//     let sorted: cs.File[] = []
//     for (const portrayal of sortedRaw)
//       sorted.push(portrayal.where())
//     set_panel(`${sorted.length} sorted files in ${bn.GALLERY_FOLDER.isAt}`, sorted)
//   }

//   document.body.style.cursor = "default"
// }



// function pressed_confirm_button(): void {
//   if (isSortingMode)
//     bn.out.print("Cannot confirm in sorting mode.")
//   else
//     bn.out.print("Confirmed selection in filter mode.")
// }




// // At startup
// console.log(cs.is_windows())
// switch_mode() // Initial

// // Set origin datalist
// const dataList = cs.element_by_id("origin_list")
// for (const origin of bn.list_origins()) {
//   const option = document.createElement("option")
//   option.value = origin.name
//   dataList.appendChild(option)
// }

// cs.element_by_id("ws_below").innerHTML = "<p>Enjoy!</p>"



// Stupid work around to give html access to module
Object.assign(window, { isSortingMode })
Object.assign(window, { })
Object.assign(window, { selectedPersonaFilters })