/*{
    "Anti36Local": {
        "Origin 1": {
            "Persona 1": {
                0: null, (this is always null as the key is the index)
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




// Switching between sorting and viewing modes
let isSortingMode = true;

async function switch_mode() {
    isSortingMode = !isSortingMode;
    document.body.style.cursor = "wait";
    await set_left_panel();
    document.getElementById("typeInputField").disabled = isSortingMode;
    // Disable not allowed cursor
    document.getElementById("typeInputField").style.cursor = isSortingMode ? "not-allowed" : "text";
    document.body.style.cursor = "default";
}



// Set left panel values
async function set_unsorted_panel() {
    document.getElementById("portrayal_elements").innerHTML = "";
    const unsortedListHeader = document.getElementById("portrayal_previews_title");
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
            document.getElementById("ws_below").innerHTML = workspaceMedia.outerHTML;
        };
        document.getElementById("portrayal_elements").appendChild(display);
    });
}


let selectedTypeFilter = "";
let selectedOriginFilters = {};

async function set_sorted_panel() {
    document.getElementById("portrayal_elements").innerHTML = "";
    const sortedListHeader = document.getElementById("portrayal_previews_title");
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
            document.getElementById("ws_below").innerHTML = workspaceMedia.outerHTML;
        };
        document.getElementById("portrayal_elements").appendChild(display);
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
function add_origin_datalist() {
    const dataList = document.getElementById("origin_list");
    for (const origin in anti36Local["Anti36Local"]) {
        const option = document.createElement("option");
        option.value = origin;
        dataList.appendChild(option);
    }
}


function set_persona_datalist(writtenOrigin) {
    const dataList = document.getElementById("persona_list");
    dataList.innerHTML = "";
    document.getElementById("personaInputField").value = "";
    for (const persona in anti36Local["Anti36Local"][writtenOrigin]) {
        const option = document.createElement("option");
        option.value = persona;
        dataList.appendChild(option);
    }
}


function personaInputField_valid(writtenPersona) {
    if (anti36Local["Anti36Local"][document.getElementById("originInputField").value][writtenPersona] === undefined) {
        alert("No persona to that origin exists");
        document.getElementById("personaInputField").value = "";
        document.getElementById("originInputField").value = "";
        return false;
    }
    return true;
}



let selectedTags = [];

function add_tags_map_in_workspace() {
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
        document.getElementById("tags_map").appendChild(tagElement);
    });
}


function pressed_confirm_button() {
    const personaInputFieldValue = document.getElementById("personaInputField").value;
    if (!isSortingMode) {
        console.log("putting together remix filters");
        if (personaInputField_valid(personaInputFieldValue)) {
            let typeInputFieldValue = document.getElementById("typeInputField").value;
            switch (typeInputFieldValue) {
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
                    alert("Invalid type.");
                    return;
            }

            // Append origin to selectedOriginFilters map
            const writtenOrigin = document.getElementById("originInputField").value;
            if (selectedOriginFilters[writtenOrigin] === undefined) {
                selectedOriginFilters[writtenOrigin] = [];
            }
            if (!selectedOriginFilters[writtenOrigin].includes(personaInputFieldValue)) {
                selectedOriginFilters[writtenOrigin].push(personaInputFieldValue);
            }
            console.log(selectedOriginFilters);

            set_sorted_panel();
        }
    }

    else {
        console.log("sorting");

        const pathToUnsortedPortrayal = document.getElementById("ws_below").firstChild.src;

        if (anti36Local["Anti36Local"][document.getElementById("originInputField").value][personaInputFieldValue] === undefined) {
            alert("Persona doesn't exist.");
            return;
        }
        else if (pathToUnsortedPortrayal === undefined) {
            alert("No portrayal selected.");
            return;
        }

        // Remove "file:///" prefix and convert / to \\ before finding index
        const pathToUnsortedPortrayalByIndex = unsortedPortrayals.indexOf(
            pathToUnsortedPortrayal.substring(8).replace(/\//g, "\\").toString()); // Special thanks to chatgpt
        client.ask_sort_please(pathToUnsortedPortrayalByIndex, selectedTags, document.getElementById("originInputField").value, personaInputFieldValue);
        unsortedPortrayals.splice(pathToUnsortedPortrayalByIndex, 1);
        document.getElementById("ws_below").innerHTML = "";
        document.getElementsByClassName("portrayal_element")[pathToUnsortedPortrayalByIndex].remove();
    }
}







document.addEventListener("DOMContentLoaded", async function() {
    document.body.style.cursor = "wait";
    anti36Local = await client.fetch_data("anti36local");
    existingTags = await client.fetch_data("existing_tags");
    unsortedPortrayals = await client.fetch_data("unsorted");

    // Set typeInputField datalist
    const typeDataList = document.getElementById("type_list");
    ["Image", "Video", "Both"].forEach(type => {
        const option = document.createElement("option");
        option.value = type;
        typeDataList.appendChild(option);
    });

    set_left_panel();
    add_tags_map_in_workspace();
    add_origin_datalist();
    document.body.style.cursor = "default";
});