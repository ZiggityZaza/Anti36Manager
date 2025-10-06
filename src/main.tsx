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
let selectedTags: bn.tag_t[] = []


// Important HTMLElements (indent by hierarchy in the HTML body)
const workspace = cs.DOM.byId("workspace", HTMLDivElement)
  const wsPanelHead = cs.DOM.byId("ws_panel_head", HTMLParagraphElement)
  const wsPanel = cs.DOM.byId("ws_panel", HTMLDivElement)
    const tagsMap = cs.DOM.byId("tags_map", HTMLDivElement)
      const tag = cs.DOM.byClass("tag", HTMLDivElement)
  const wsControlPanel = cs.DOM.byId("ws_control_panel", HTMLDivElement)
    const wsControlPanelAddButton = cs.DOM.byId("ws_control_panel_add_button", HTMLDivElement) // Behaves like a button
    const wsControlPanelSwitchButton = cs.DOM.byId("ws_control_panel_switch_button", HTMLDivElement) // Behaves like a button
  const wsInputPanel = cs.DOM.byId("ws_input_panel", HTMLDivElement)
    const originInputField = cs.DOM.byId("originInputField", HTMLInputElement)
    const originList = cs.DOM.byId("origin_list", HTMLDataListElement)
    const personaInputField = cs.DOM.byId("personaInputField", HTMLInputElement)
    const personaList = cs.DOM.byId("persona_list", HTMLDataListElement)
  const wsBelowHead = cs.DOM.byId("ws_below_head", HTMLParagraphElement)
  const wsBelow = cs.DOM.byId("ws_below", HTMLDivElement)
    const initMessage = cs.DOM.byId("initMessage", HTMLParagraphElement)

const portrayalPreviews = cs.DOM.byId("portrayal_previews", HTMLDivElement)
  const portrayalPreviewsTitle = cs.DOM.byId("portrayal_previews_title", HTMLParagraphElement)
  const portrayalElements = cs.DOM.byId("portrayal_elements", HTMLDivElement)
    const portrayalElement: (HTMLVideoElement | HTMLImageElement)[] =
      rawElements.map(el >= el as HTMLVideoElement | HTMLImageElement)

    // const portrayalElement = cs.DOM.byClass("portrayal_element", HTMLVideoElement | HTMLImageElement)



// Helpers
function insertIntoSidebar(source: cs.File): void {

}









// Helpers
function set_panel(selectedFiles: cs.File[], newTitle: string | undefined): void {
  /*
    Clear and populate the sidebar with new imgs
    or vids regardless of source.
  */
  bn.out.print()

  cs.element_by_id("portrayal_elements").innerHTML = "" // Reset
  if (newTitle)
    cs.element_by_id("portrayal_previews_title").innerHTML = newTitle

  for (const media of selectedFiles) {
    bn.out.print(`Processing ${media.isAt}`)
    const type = cs.or_err(bn.EXTENSION_TO_MEDIA[media.extension()], `Unsupported file extension '${media.extension()}' of ${media.isAt}`)
    const display = document.createElement(type === bn.MediaType.IMAGE ? "img" : "video")
    display.className = "portrayal_element"
    display.src = media.isAt
    display.onclick = () => {
      const workspaceMedia = document.createElement(type === bn.MediaType.IMAGE ? "img" : "video")
      if (workspaceMedia instanceof HTMLVideoElement) {
        workspaceMedia.setAttribute("controls", "controls")
        workspaceMedia.autoplay = true
        workspaceMedia.muted = true
        workspaceMedia.loop = true
      }
      workspaceMedia.src = media.isAt
      workspaceMedia.id = "portrayal_element_selected"
      cs.element_by_id("ws_below").innerHTML = workspaceMedia.outerHTML
    }
    cs.element_by_id("portrayal_elements").appendChild(display)
  }
}


function set_persona_datalist(): void {
  const dataList = cs.input_element_by_id("persona_list")
  dataList.innerHTML = ""; // Needs semicolon
  cs.input_element_by_id("personaInputField").value = ""
  for (const persona of bn.list_all_personas(bn.find_origin(cs.input_element_by_id("originInputField").value))) {
    const option = document.createElement("option")
    option.value = persona.name
    dataList.appendChild(option)
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
window.addEventListener("load", () => {
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
})



// Stupid work around
Object.assign(window, { personaInputField_valid, set_persona_datalist, switch_mode, pressed_confirm_button })