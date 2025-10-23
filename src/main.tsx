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
let selectedTags: bn.TagChar[] = []



// Important HTMLElements (indent by hierarchy in the HTML body)
const workspace = cs.DOM.by_id("workspace", HTMLDivElement)
  const wsPanelHead = cs.DOM.by_id("ws_panel_head", HTMLParagraphElement)
  const wsPanel = cs.DOM.by_id("ws_panel", HTMLDivElement)
    const tagsMap = cs.DOM.by_id("tags_map", HTMLDivElement)
      function get_tag_elements(): HTMLDivElement[] { // Filled and read at runtime
        return cs.DOM.by_class("tag", HTMLDivElement)
      }
  const wsControlPanel = cs.DOM.by_id("ws_control_panel", HTMLDivElement)
    const wsControlPanelAddButton = cs.DOM.by_id("ws_control_panel_add_button", HTMLDivElement) // Behaves like a button
    const wsControlPanelSwitchButton = cs.DOM.by_id("ws_control_panel_switch_button", HTMLDivElement) // Behaves like a button
  const wsInputPanel = cs.DOM.by_id("ws_input_panel", HTMLDivElement)
    const originInputField = cs.DOM.by_id("originInputField", HTMLInputElement)
    const originList = cs.DOM.by_id("origin_list", HTMLDataListElement)
    const personaInputField = cs.DOM.by_id("personaInputField", HTMLInputElement)
    const personaList = cs.DOM.by_id("persona_list", HTMLDataListElement)
  const wsBelowHead = cs.DOM.by_id("ws_below_head", HTMLParagraphElement)
  const wsBelow = cs.DOM.by_id("ws_below", HTMLDivElement)
    const initMessage = cs.DOM.by_id("initMessage", HTMLParagraphElement)
      // alternatively...
    const portrayalElementSelectedId = "portrayal_element_selected" // Purely for styling purposes

const portrayalPreviews = cs.DOM.by_id("portrayal_previews", HTMLDivElement)
  const portrayalPreviewsTitle = cs.DOM.by_id("portrayal_previews_title", HTMLParagraphElement)
  const portrayalElements = cs.DOM.by_id("portrayal_elements", HTMLDivElement)
    const portrayalElementId = "portrayal_element"
    function get_portrayal_elements(): (HTMLVideoElement | HTMLImageElement)[] { // Filled and read at runtime
      return [
        ...cs.DOM.by_class(portrayalElementId, HTMLImageElement),
        ...cs.DOM.by_class(portrayalElementId, HTMLVideoElement),
      ]
    }




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