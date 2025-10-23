import * as os from "node:os"
// import React from "react" // React on idle
// import * as ReactDOM from "react-dom/client" // React on idle
import * as cs from "./cslib.js"
import * as bn from "./logic.js"
import type { HTMLElementType } from "react"



// Start backend
bn.lets_go()



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
  previewTarget: cs.DOM.by_id("preview-target", HTMLElement),
  previews: cs.DOM.by_tag("aside")[0]!, // There is only one aside element


  // Static elements (must be configured at startup)
  confirmButton: cs.DOM.by_id("confirm", HTMLButtonElement),
  switchModeButton: cs.DOM.by_id("switch-mode", HTMLButtonElement),
  tagButtons: new Map<bn.TagT, HTMLButtonElement>(),



  // Helpers to configure static elements
  insert_tag_buttons_to_dom: function (): void {
    const section = cs.DOM.by_id("tags-map", HTMLElement) // <section>
    for (const [tagAsChar, meaning] of Object.entries(bn.TAGS_LOOKUP)) {
      const button = document.createElement("button")
      button.textContent = meaning
      section.appendChild(button)
      this.tagButtons.set(tagAsChar as bn.TagT, button) // Yes, 'char' is the key from TAGS_LOOKUP
      button.addEventListener("click", () => {
        this



} as const








// Helpers
function insertIntoSidebar(_source: cs.File): HTMLImageElement | HTMLVideoElement {
  /*
    Inserts a media file into the sidebar as an
    img or vid element.
  */

  let element: HTMLImageElement | HTMLVideoElement
  if (bn.EXTENSION_TO_MEDIA[_source.extension()] === bn.MediaT.IMAGE)
    element = document.createElement("img")
  else if (bn.EXTENSION_TO_MEDIA[_source.extension()] === bn.MediaT.VIDEO) {
    element = document.createElement("video")
    element.controls = true
    element.onclick = () => {
      element.id = portrayalElementSelectedId // For styling
    }
  }
  else
    throw new bn.A36Err(`Unsupported media type for preview: '${_source.extension()}'`)
  element.src = `file:///${_source.isAt}`
  element.classList.add(portrayalElementId) // For styling
  portrayalElements.appendChild(element) // Add to DOM as HTML element
  return element
}



function set_persona_datalist(): void {
  /*
    Sets the persona datalist according to the origin
    input field's value.
  */
  while (personaList.firstChild)
    personaList.removeChild(personaList.firstChild) // Clear existing options

  if (!bn.list_origins().some(o => o.name === originInputField.value))
    return

  const origin: bn.Origin | undefined = bn.find_origin(originInputField.value)
  if (origin === undefined)
    return // Origin doesn't exist

  const personas: bn.Persona[] = origin.list_personas()
  for (const persona of personas) {
    const option = document.createElement("option")
    option.value = persona.name
    personaList.appendChild(option)
  }
}



function personaInputField_valid(): boolean {
  // Also allows confirm button to be pressed
  const originInputField = cs.input_element_by_id("originInputField").value
  if (!bn.list_origins().some(o => o.name === originInputField)) {
    alert("Origin doesn't exist."); // Needs semicolon
    cs.input_element_by_id("personaInputField").value = ""
    return false
  } else if (bn.personasByOrigin.get(bn.find_origin(originInputField)) === undefined) {
    alert("Origin exists but persona field is empty or invalid."); // Needs semicolon
    cs.input_element_by_id("personaInputField").value = ""
    return false
  }
  return true
}



// Vague functionalities





// Directly called by user
function switch_mode(): void {
  isSortingMode = !isSortingMode
  document.body.style.cursor = "wait"

  if (isSortingMode) {
    cs.element_by_id("ws_control_panel_add_button").innerHTML = "Add unsorted to gallery"
    cs.element_by_id("ws_control_panel_switch_button").innerHTML = "Switch to filter view"
    const unsorted = bn.list_all_unsorted_portrayals()
    set_panel(`${unsorted.length} unsorted files in ${bn.UNSORTED_FOLDER.isAt}`, unsorted)
  } else {
    cs.element_by_id("ws_control_panel_add_button").innerHTML = "Select sorted portrayals"
    cs.element_by_id("ws_control_panel_switch_button").innerHTML = "Switch to sorting view"
    const sortedRaw = bn.list_all_portrayals()
    let sorted: cs.File[] = []
    for (const portrayal of sortedRaw)
      sorted.push(portrayal.where())
    set_panel(`${sorted.length} sorted files in ${bn.GALLERY_FOLDER.isAt}`, sorted)
  }

  document.body.style.cursor = "default"
}



function pressed_confirm_button(): void {
  if (isSortingMode)
    bn.out.print("Cannot confirm in sorting mode.")
  else
    bn.out.print("Confirmed selection in filter mode.")
}




// At startup
console.log(cs.is_windows())
switch_mode() // Initial

// Set origin datalist
const dataList = cs.element_by_id("origin_list")
for (const origin of bn.list_origins()) {
  const option = document.createElement("option")
  option.value = origin.name
  dataList.appendChild(option)
}

cs.element_by_id("ws_below").innerHTML = "<p>Enjoy!</p>"



// Stupid work around
Object.assign(window, { personaInputField_valid, set_persona_datalist, switch_mode, pressed_confirm_button })