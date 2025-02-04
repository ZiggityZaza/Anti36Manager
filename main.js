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

    async fetchData(endpoint) {
        const response = await fetch(`http://localhost:8080/${endpoint}`, {method: 'GET'});
        return await response.json();
    }

    async set_anti36Local() {
        anti36Local = await this.fetchData("anti36local");
    }
    async set_existingTags() {
        existingTags = await this.fetchData("existing_tags");
    }
    async set_unsortedPortrayals() {
        unsortedPortrayals = await this.fetchData("unsorted");
    }
    async set_filteredPortrayals() {
        filteredPortrayals = await this.fetchData("current_portrayal_remix");
    }

    ask_sort_please(pathToUnsortedPortrayalByIndex, tags, origin, persona) {
        /*
            {
              "currentLocationInUnsortedByIndex": 2, ("E:\\$unsorted\\someImage.jpg")
              "origin": "Origin 1",
              "persona": "Persona 1",
              "tags": ["_A", "_B", "_C", "_D"]
            }
        */
        const data = {
            "currentLocationInUnsortedByIndex": pathToUnsortedPortrayalByIndex,
            "origin": origin,
            "persona": persona,
            "tags": tags
        };
        fetch("http://localhost:8080/sort", {
            mode: 'no-cors',
            method: "POST",
            body: JSON.stringify(data),
            headers: {"Content-Type": "application/json"}
        });
    }
    ask_remix_please(filterByPersonas = {}, filterByTags = [], filterByType = "") {
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
        const data = {
            "filterByPersonas": filterByPersonas,
            "filterByTags": filterByTags,
            "filterByType": filterByType
        };
        fetch("http://localhost:8080/remix", {
            mode: 'no-cors',
            method: "POST",
            body: JSON.stringify(data),
            headers: {"Content-Type": "application/json"}
        });
    }
}

const client = new Anti36Proxy();



// Set left panel values
function set_unsorted_panel() {
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
    }
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


function pressed_confirm_button_for_sorting() {
    const personaInputField = document.getElementById("personaInputField");
    if (personaInputField.value !== "") {
        console.log(`Persona selected: ${personaInputField.value} from ${document.getElementById("originInputField").value}`);
        const pathToUnsortedPortrayal = document.getElementById("ws_below").firstChild.src;
        if (pathToUnsortedPortrayal === undefined) {
            console.log("No portrayal selected");
            return;
        }

        // Set correct values
        pathToUnsortedPortrayal = pathToUnsortedPortrayal.substring(8).replace(/\//g, "\\"); // Remove "file:///" prefix and convert / to \\
        const pathToUnsortedPortrayalByIndex = unsortedPortrayals.indexOf(pathToUnsortedPortrayal.toString());

        // Sort and wipe
        console.log(unsortedPortrayals[pathToUnsortedPortrayalByIndex]);
        client.ask_sort_please(pathToUnsortedPortrayalByIndex, selectedTags, document.getElementById("originInputField").value, personaInputField.value);
        unsortedPortrayals.splice(pathToUnsortedPortrayalByIndex, 1);
        document.getElementById("ws_below").innerHTML = "";
        document.getElementsByClassName("portrayal_element")[pathToUnsortedPortrayalByIndex].remove();
    }
}

// function pressed_confirm_button_for_sorting() {
//     const personaInputField = document.getElementById("personaInputField");
//     if (personaInputField.value === "") {
//         console.log("No persona selected");
//     } else {
//         console.log(`Persona selected: ${personaInputField.value} from ${document.getElementById("originInputField").value}`);
//         for (const selectedTag of selectedTags) {
//             console.log(selectedTag);
//         }
//         const pathToUnsortedPortrayal = document.getElementById("ws_below").firstChild.src;
//         if (pathToUnsortedPortrayal === undefined) {
//             console.log("No portrayal selected");
//         } else {
//             const pathToUnsortedPortrayalByIndex = unsortedPortrayals.indexOf(pathToUnsortedPortrayal);
//             console.log(pathToUnsortedPortrayalByIndex);
//             client.ask_sort_please(pathToUnsortedPortrayalByIndex, selectedTags, document.getElementById("originInputField").value, personaInputField.value);
//             unsortedPortrayals.splice(pathToUnsortedPortrayalByIndex, 1);
//             document.getElementsByClassName("portrayal_element")[pathToUnsortedPortrayalByIndex].remove();
//         }
//     }
// }







document.addEventListener("DOMContentLoaded", async function() {
    document.body.style.cursor = "wait";
    await client.set_anti36Local();
    await client.set_existingTags();
    await client.set_unsortedPortrayals();

    set_unsorted_panel();
    add_tags_map_in_workspace();
    add_origin_list();
    document.body.style.cursor = "default";
});