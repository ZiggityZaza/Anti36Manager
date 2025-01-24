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


// "true" or "false"
let serverIsBusy = new Boolean;



class Anti36Proxy {
    // Communication with the server
    constructor() {
    }

    set_anti36Local() {
        fetch('http://localhost:8080/anti36local', { method: 'GET'})
        .then(response => response.json())
        .then(data => {
            anti36Local = data;
            console.log(anti36Local);
        });
    }

    set_existingTags() {
        fetch('http://localhost:8080/existing_tags', { method: 'GET'})
        .then(response => response.json())
        .then(data => {
            existingTags = data;
            console.log(existingTags);
        });
    }

    set_unsortedPortrayals() {
        fetch('http://localhost:8080/unsorted', { method: 'GET'})
        .then(response => response.json())
        .then(data => {
            unsortedPortrayals = data;
            console.log(unsortedPortrayals);
        });
    }

    set_filteredPortrayals() {
        fetch('http://localhost:8080/current_portrayal_remix', { method: 'GET'})
        .then(response => response.json())
        .then(data => {
            filteredPortrayals = data;
            console.log(filteredPortrayals);
        });
    }

    set_IsBusy() {
        fetch('http://localhost:8080/are_you_busy', { method: 'GET'})
        .then(response => response.json())
        .then(data => {
            serverIsBusy = data;
            console.log(serverIsBusy);
        });
    }

    ask_sort_please(pathToUnsortedPortrayal, tags, origin, persona) {
        /*
            {
                "currentLocationInUnsorted": "E:\\$unsorted\\someImage.jpg",
                "index": INDEX_AUTO_INCREMENT_CODE,
                "origin": "Origin 1",
                "persona": "Persona 1",
                "tags": ["_A", "_B", "_C", "_D"]
            }
        */
        let data = {
            "currentLocationInUnsorted": pathToUnsortedPortrayal,
            "origin": origin,
            "persona": persona,
            "tags": tags
        };
        fetch('http://localhost:8080/sort_please', {
            mode: 'no-cors',
            method: 'POST',
            headers: {'Content-Type': 'application/json'},
            body: JSON.stringify(data)
        });

        // Refresh everything
        document.getElementById("uns_elements").innerHTML = ""; // Clear unsorted panel

        this.set_unsortedPortrayals();
        setTimeout(function() {
            set_unsorted_panel();
        }, 1000);
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

        console.log("Asking server to make a remix");

        let data = {
            filterByPersonas,
            filterByTags,
            filterByType
        };

        fetch('http://localhost:8080/remix_please', {
            mode: 'no-cors',
            method: 'POST',
            headers: {'Content-Type': 'application/json'},
            body: JSON.stringify(data)
        });
    }
}


let client = new Anti36Proxy();
client.set_anti36Local();
client.set_existingTags();
client.set_unsortedPortrayals();


let selectedTags = [];




function set_tags_map_in_workspace() {
    const workspace = document.getElementById("ws_panel");
    workspace.innerHTML = "";
    const tagsMap = document.createElement("div");
    tagsMap.id = "tags_map";

    existingTags.forEach(tag => {
        const tagElement = document.createElement("div");
        tagElement.className = "tag";
        tagElement.innerHTML = tag;
        tagElement.onclick = () => {
            const index = selectedTags.indexOf(tag);
            if (index > -1) {
                selectedTags.splice(index, 1);
                tagElement.style.backgroundColor = "";
            } else {
                selectedTags.push(tag);
                tagElement.style.backgroundColor = `#${Math.floor(Math.random() * 16777215).toString(16)}`;
            }
            console.log(selectedTags);
        };
        tagsMap.appendChild(tagElement);
    });

    workspace.appendChild(tagsMap);
}



function set_unsorted_panel() {
    const unsortedListHeader = document.getElementById("uns_head");
    unsortedListHeader.innerHTML = `${unsortedPortrayals.length} files in "$unsorted"`;

    unsortedPortrayals.forEach(unsortedFPath => {
        const fileExtension = unsortedFPath.split('.').pop().toLowerCase();
        const isImage = ["jpg", "jpeg", "png", "gif", "bmp", "webp"].includes(fileExtension);
        const isVideo = ["mp4", "webm", "mkv", "avi"].includes(fileExtension);

        let display;
        if (isImage) {
            display = document.createElement("img");
        } else if (isVideo) {
            display = document.createElement("video");
            display.muted = true;
            display.loop = true;
            display.addEventListener("mouseover", () => display.play());
            display.addEventListener("mouseout", () => display.pause());
        }

        display.className = "uns_element";
        display.src = unsortedFPath;
        display.onclick = () => {
            const workspaceMedia = isImage ? document.createElement("img") : document.createElement("video");
            if (!isImage) workspaceMedia.setAttribute("controls", "controls");
            workspaceMedia.src = unsortedFPath;
            workspaceMedia.id = "ws_below";
            document.getElementById("ws_below").innerHTML = workspaceMedia.outerHTML;
        };
        document.getElementById("uns_elements").appendChild(display);
    });
}



function ws_control_panel_confirmed() {
    console.log("Confirmed");
    let personaInputField = document.getElementById("personaInputField");
    if (personaInputField.value === "") {
        console.log("No persona selected");
    } else {
        console.log("Persona selected: " + personaInputField.value + " from " + document.getElementById("originInputField").value);
        for (let selectedTag of selectedTags) {
            console.log(selectedTag);
        }
    }
};



function origin_selected(userInput) {
    let personaInputField = document.getElementById("personaInputField");
    personaInputField.value = "";
    if (anti36Local["Anti36Local"][userInput] !== undefined) {
        let personaList = document.getElementById("persona_list");
        personaList.innerHTML = "";
        for (let persona in anti36Local["Anti36Local"][userInput]) {
            let option = document.createElement("option");
            option.value = persona;
            personaList.appendChild(option);
        }
    }
}



function persona_selected(userInput) {
    console.log(userInput);
}



function set_origin_list() {
    let dataList = document.getElementById("origin_list");
    for (let origin in anti36Local["Anti36Local"]) {
        let option = document.createElement("option");
        option.value = origin;
        dataList.appendChild(option);
    }
}




// Entry point
document.addEventListener("DOMContentLoaded", function() {
    document.body.style.cursor = "wait";
    setTimeout(function() {
        set_unsorted_panel();
        set_tags_map_in_workspace();
        set_origin_list();
        document.body.style.cursor = "default";
    }, 1000);
});