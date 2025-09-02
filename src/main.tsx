import * as os from "node:os"
// import React from "react" // React on idle
// import * as ReactDOM from "react-dom/client" // React on idle
import * as cs from "./cslib.js"
import * as bn from "./logic.js"




// Start backend
bn.lets_go()




// Resources
let isSortingMode = true
let selectedPersonaFilters: bn.Persona[] = [] // Origins and personas to filter by
let selectedTags: bn.tag_t[] = []




// Functions
function set_panel(title: string, portrayalsInside: cs.File[]): void {
  cs.element_by_id("portrayal_elements").innerHTML = "" // Reset
  cs.element_by_id("portrayal_previews_title").innerHTML = title

  for (const portrayal of portrayalsInside) {
    bn.out.print(`Processing ${portrayal.isAt}`)
    const type = cs.or_err(bn.EXTENSION_TO_MEDIA[portrayal.extension()], `Unsupported file extension '${portrayal.extension()}' of ${portrayal.isAt}`)
    const display = document.createElement(type === bn.MediaType.IMAGE ? "img" : "video")
    display.className = "portrayal_element"
    display.src = portrayal.isAt
    display.onclick = () => {
      const workspaceMedia = document.createElement(type === bn.MediaType.IMAGE ? "img" : "video")
      if (workspaceMedia instanceof HTMLVideoElement) {
        workspaceMedia.setAttribute("controls", "controls")
        workspaceMedia.autoplay = true
        workspaceMedia.muted = true
        workspaceMedia.loop = true
      }
      workspaceMedia.src = portrayal.isAt
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
})



// Stupid work around
Object.assign(window, { personaInputField_valid, set_persona_datalist, switch_mode })