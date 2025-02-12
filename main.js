/*{
    "Anti36Local": {
        "Origin 1": {
            "Persona 1": {
                1: {
                    path: "E:\\Anti36Local\\Origin 1\\Persona 1\\1_ABCD_.jpg",
                    tags: ["_A", "_B", "_C", "_D_"]
                },
                2: {
                    path: "E:\\Anti36Local\\Origin 1\\Persona 1\\2_EFGH_.jpg",
                    tags: ["_E", "_F", "_G", "_H_"]
                },
                ...
            },
            "Persona 2": {
                ...
            },
            ...
        },
        "Origin 2": {
            ...
        },
        ...
    }
}*/
let anti36Local = {};

// ["_A", "_B",..., "_Z", "_a", "_b",..., "_z", "_0", "_1",..., "_9"]
let existingTags = [];

/* ["E:\\$unsorted\\someImage.jpg","E:\\$unsorted\\someVideo.mp4",...
"E:\\$unsorted\\someOtherImage.png","E:\\$unsorted\\someGif.mp4"] */
let unsortedPortrayals = [];

// ["E:\\Origina 1\\Persona 1\\1_ABCD_.jpg", "E:\\Origina 1\\Persona 1\\2_EFGH_.jpg",...]
let filteredPortrayals = [];


class Anti36Proxy {
    constructor() {}
    async fetch_data(endpoint) {
        const response = await fetch(`http://localhost:8080/${endpoint}`, {method: 'GET'});
        return await response.json();
    }
    async send_data(endpoint, data) {
        await fetch(`http://localhost:8080/${endpoint}`, {
            mode: 'no-cors',
            method: "POST",
            body: JSON.stringify(data),
            headers: {"Content-Type": "application/json"}
        });
    }
    async ask_sort_please(pathToUnsortedPortrayalByIndex, tags, origin, persona) {
        /*
            {
              "currentLocationInUnsortedByIndex": 2, ("E:\\$unsorted\\someImage.jpg")
              "origin": "Origin 1",
              "persona": "Persona 1",
              "tags": ["_A", "_B", "_C", "_D"]
            }
        */
        await this.send_data("sort_please", {
            "currentLocationInUnsortedByIndex": pathToUnsortedPortrayalByIndex,
            "origin": origin,
            "persona": persona,
            "tags": tags
        });
    }
    async tell_filters(filterByPersonas = {}, filterByTags = [], filterByType = "") {
        /*
            {
                "filterByPersonas": {
                    "Origin 1": ["Persona 1", "Persona 2",...],
                    "Origin 2": ["Persona 1", "Persona 2",...],
                    ...
            },
                "filterByTags": ["_A", "_B", "_C", "_D",...],
                "filterByType": "Image" (or "Video" for vids, "" for both)
            }
        */
        await this.send_data("remix_please", {
            "filterByPersonas": filterByPersonas,
            "filterByTags": filterByTags,
            "filterByType": filterByType
        });
    }
}

const client = new Anti36Proxy();



// Helper
function elementById(id) {
    return document.getElementById(id);
}
function valueById(id) {
    return document.getElementById(id).value;
}



// Switching between sorting and viewing modes
let isSortingMode = true;

async function switch_mode() {
    isSortingMode = !isSortingMode;
    document.body.style.cursor = "wait";
    await set_left_panel();
    elementById("typeInputField").disabled = isSortingMode;
    // Disable not allowed cursor
    elementById("typeInputField").style.cursor = isSortingMode ? "not-allowed" : "text";
    document.body.style.cursor = "default";
}



// Set left panel values
async function set_unsorted_panel() {
    elementById("portrayal_elements").innerHTML = "";
    const unsortedListHeader = elementById("portrayal_previews_title");
    unsortedListHeader.innerHTML = `${unsortedPortrayals.length} files in "$unsorted"`;

    unsortedPortrayals.forEach(unsortedFPath => {
        const fileExtension = unsortedFPath.split('.').pop().toLowerCase();
        const isImage = ["jpg", "jpeg", "png", "gif", "bmp", "webp"].includes(fileExtension);
        const isVideo = ["mp4", "webm", "mkv", "avi"].includes(fileExtension);

        let display = isImage ? document.createElement("img") : document.createElement("video");
        display.className = "portrayal_element";
        display.src = unsortedFPath;
        display.onclick = () => {
            const workspaceMedia = isImage ? document.createElement("img") : document.createElement("video");
            if (isVideo) {
                workspaceMedia.setAttribute("controls", "controls");
                workspaceMedia.autoplay = true;
                workspaceMedia.muted = true;
                workspaceMedia.loop = true;
            }
            workspaceMedia.src = unsortedFPath;
            workspaceMedia.id = "portrayal_element_selected";
            elementById("ws_below").innerHTML = workspaceMedia.outerHTML;
        };
        elementById("portrayal_elements").appendChild(display);
    });
}


let selectedTypeFilter = "";
let selectedOriginFilters = {};
let selectedTags = []; // In general

async function set_sorted_panel() {
    elementById("portrayal_elements").innerHTML = "";
    const sortedListHeader = elementById("portrayal_previews_title");
    sortedListHeader.innerHTML = `${filteredPortrayals.length} files in "Anti36Local"`;

    await client.tell_filters(selectedOriginFilters, selectedTags, selectedTypeFilter);
    filteredPortrayals = await client.fetch_data("current_portrayal_remix");

    filteredPortrayals.forEach(sortedFPath => {
        console.log(sortedFPath);
        const fileExtension = sortedFPath.split('.').pop().toLowerCase();
        const isImage = ["jpg", "jpeg", "png", "gif", "bmp", "webp"].includes(fileExtension);
        const isVideo = ["mp4", "webm", "mkv", "avi"].includes(fileExtension);

        let display = isImage ? document.createElement("img") : document.createElement("video");
        display.className = "portrayal_element";
        display.src = sortedFPath;
        display.onclick = () => {
            const workspaceMedia = isImage ? document.createElement("img") : document.createElement("video");
            if (isVideo) {
                workspaceMedia.setAttribute("controls", "controls");
                workspaceMedia.autoplay = true;
                workspaceMedia.muted = true;
                workspaceMedia.loop = true;
            }
            workspaceMedia.src = sortedFPath;
            workspaceMedia.id = "portrayal_element_selected";
            elementById("ws_below").innerHTML = workspaceMedia.outerHTML;
        };
        elementById("portrayal_elements").appendChild(display);
    });
}


async function set_left_panel() {
    if (isSortingMode) {
        await set_unsorted_panel();
    } else {
        await set_sorted_panel();
    }
}



// Set right panel values
function set_persona_datalist() {
    const dataList = elementById("persona_list");
    dataList.innerHTML = "";
    elementById("personaInputField").value = "";
    for (const persona in anti36Local["Anti36Local"][elementById("originInputField").value]) {
        const option = document.createElement("option");
        option.value = persona;
        dataList.appendChild(option);
    }
}


async function personaInputField_valid() {
    // Also allows confirm button to be pressed
    const originInputField = elementById("originInputField").value;
    const personaInputField = elementById("personaInputField").value;

    if (anti36Local["Anti36Local"][originInputField] === undefined) {
        alert("Origin doesn't exist.");
        elementById("personaInputField").value = "";
        return false;
    }
    else if (anti36Local["Anti36Local"][originInputField][personaInputField] === undefined) {
        alert("Origin exists but persona field is empty or invalid.");
        elementById("personaInputField").value = "";
        return false;
    }

    return true;
}





function pressed_confirm_button() {
    if (personaInputField_valid()) {
        alert("Please enter a valid origin and persona.");
        return;
    }

    const personaInputFieldValue = elementById("personaInputField").value;
    if (!isSortingMode) {
        console.log("putting together remix filters");

        switch (elementById("typeInputField").value) {
            case "":
            case "Both":
                selectedTypeFilter = "";
                break;
            case "Image":
                selectedTypeFilter = "Image";
                break;
            case "Video":
                selectedTypeFilter = "Video";
                break;
            default:
                alert("Only image and video are supported as types.");
                return;
        }
        // Append origin to selectedOriginFilters map
        const writtenOrigin = elementById("originInputField").value;
        if (selectedOriginFilters[writtenOrigin] === undefined) {
            selectedOriginFilters[writtenOrigin] = [];
        }
        if (!selectedOriginFilters[writtenOrigin].includes(personaInputFieldValue)) {
            selectedOriginFilters[writtenOrigin].push(personaInputFieldValue);
        }
        console.log(selectedOriginFilters);
        set_sorted_panel();
    }

    else {
        console.log("sorting unsorted portrayal");

        const pathToUnsortedPortrayal = elementById("ws_below").firstChild.src;
        if (pathToUnsortedPortrayal === undefined) {
            alert("No portrayal selected.");
            return;
        }
        // Remove "file:///" prefix and convert / to \\ before finding index
        const pathToUnsortedPortrayalByIndex = unsortedPortrayals.indexOf(
            pathToUnsortedPortrayal.substring(8).replace(/\//g, "\\").toString()); // Special thanks to chatgpt
        client.ask_sort_please(pathToUnsortedPortrayalByIndex, selectedTags, elementById("originInputField").value, personaInputFieldValue);
        unsortedPortrayals.splice(pathToUnsortedPortrayalByIndex, 1);
        elementById("ws_below").innerHTML = "";
        document.getElementsByClassName("portrayal_element")[pathToUnsortedPortrayalByIndex].remove();
    }
}







document.addEventListener("DOMContentLoaded", async function() {
    document.body.style.cursor = "wait";
    anti36Local = await client.fetch_data("anti36local");
    existingTags = await client.fetch_data("existing_tags");
    unsortedPortrayals = await client.fetch_data("unsorted");

    // Set typeInputField datalist
    const typeDataList = elementById("type_list");
    ["Image", "Video", "Both"].forEach(type => {
        const option = document.createElement("option");
        option.value = type;
        typeDataList.appendChild(option);
    });



    set_left_panel();


    // Set tags map in workspace
    existingTags.forEach(tag => {
        const tagElement = document.createElement("div");
        tagElement.className = "tag";
        tagElement.innerHTML = tag;
        tagElement.onclick = () => {
            if (selectedTags.includes(tag)) {
                selectedTags = selectedTags.filter(t => t !== tag); // if t ain't tag keep it
                tagElement.style.backgroundColor = "";
            } else {
                selectedTags.push(tag);
                tagElement.style.backgroundColor = `#${Math.floor(Math.random() * 16777215).toString(16)}`;
            }
        };
        elementById("tags_map").appendChild(tagElement);
    });


    // Set originInputField datalist
    const dataList = elementById("origin_list");
    for (const origin in anti36Local["Anti36Local"]) {
        const option = document.createElement("option");
        option.value = origin;
        dataList.appendChild(option);
    }

    document.body.style.cursor = "default";
});
