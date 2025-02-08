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
    async ask_current_portrayal_remix(filterByPersonas = {}, filterByTags = [], filterByType = "") {
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
        await this.send_data("current_portrayal_remix", {
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
    document.body.style.cursor = "default";
}



// Set left panel values
function set_unsorted_panel() {
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


async function set_sorted_panel() {
    document.getElementById("portrayal_elements").innerHTML = "";
    const sortedListHeader = document.getElementById("portrayal_previews_title");
    sortedListHeader.innerHTML = `${filteredPortrayals.length} files in "Anti36Local"`;

    await client.tell_filters({}, ["_C"], "");
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


function set_persona_datalist(origin) {
    const dataList = document.getElementById("persona_list");
    dataList.innerHTML = "";
    document.getElementById("personaInputField").value = "";

    if (anti36Local["Anti36Local"][origin] !== undefined) {
        for (const persona in anti36Local["Anti36Local"][origin]) {
            const option = document.createElement("option");
            option.value = persona;
            dataList.appendChild(option);
        }
    } else {
        alert("Origin doesn't exist.");
    }
}

function make_sure_personaInputField_valid(writtenPersona) {
    const originInputField = document.getElementById("originInputField").value;
    if (anti36Local["Anti36Local"][originInputField] === undefined) {
        alert("Origin itself doesn't exist. Enter correct origin.");
        document.getElementById("personaInputField").value = "";
    } else if (anti36Local["Anti36Local"][originInputField][writtenPersona] === undefined) {
        alert("Origin exists but persona doesn't. Enter correct persona.");
    }
    document.getElementById("personaInputField").value = "";
    // let existsInAnti36Local = false;
    // if (anti36Local["Anti36Local"][originInputField] !== undefined) {
    //     if (anti36Local["Anti36Local"][originInputField][writtenPersona] !== undefined) {
    //         existsInAnti36Local = true;
    //     }
    // }
    // if (originInputField === "" || originInputField === undefined) {
    //     alert("I need to know which persona you're referring to. Enter correct origin.");
    //     document.getElementById("personaInputField").value = "";
    // }
}



let selectedTags = [];

function add_tags_map_in_workspace() {
    existingTags.forEach(tag => {
        const tagElement = document.createElement("div");
        tagElement.className = "tag";
        tagElement.innerHTML = tag;
        tagElement.onclick = () => {
            if (selectedTags.includes(tag)) {
                selectedTags = selectedTags.filter(t => t !== tag); // lambda function to remove tag from selectedTags
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
    const personaInputField = document.getElementById("personaInputField");
    const pathToUnsortedPortrayal = document.getElementById("ws_below").firstChild.src;

    if (personaInputField.value !== "") {
        alert("Please select a persona0.");
        return;
    }
        
    if (personaInputField.value !== undefined) {
        alert("Please select a persona1.");
        return;
    }
        
    if (pathToUnsortedPortrayal !== "") {
        alert("Please select a persona2.");
        return;
    }

    if (pathToUnsortedPortrayal !== undefined) {
        alert("Please select a persona3.");
        return;
    }

    if (personaInputField.value !== "" && personaInputField.value !== undefined && pathToUnsortedPortrayal !== "" && pathToUnsortedPortrayal !== undefined) {
        // Remove "file:///" prefix and convert / to \\ before finding index
        const pathToUnsortedPortrayalByIndex = unsortedPortrayals.indexOf(
            pathToUnsortedPortrayal.substring(8).replace(/\//g, "\\").toString()); // Special thanks to chatgpt

        // Sort and wipe
        client.ask_sort_please(pathToUnsortedPortrayalByIndex, selectedTags, document.getElementById("originInputField").value, personaInputField.value);
        unsortedPortrayals.splice(pathToUnsortedPortrayalByIndex, 1);
        document.getElementById("ws_below").innerHTML = "";
        document.getElementsByClassName("portrayal_element")[pathToUnsortedPortrayalByIndex].remove();
    } else {
        alert("Please select a persona.");
    }
}







document.addEventListener("DOMContentLoaded", async function() {
    document.body.style.cursor = "wait";
    anti36Local = await client.fetch_data("anti36local");
    existingTags = await client.fetch_data("existing_tags");
    unsortedPortrayals = await client.fetch_data("unsorted");

    set_left_panel();
    add_tags_map_in_workspace();
    add_origin_datalist();
    document.body.style.cursor = "default";
});