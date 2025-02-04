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

    ask_sort_please(pathToUnsortedPortrayalByIndex, tags, origin, persona) {
        /*
            {
              "currentLocationInUnsortedByIndex": 2, ("E:\\$unsorted\\someImage.jpg")
              "origin": "Origin 1",
              "persona": "Persona 1",
              "tags": ["_A", "_B", "_C", "_D"]
            }
        */

        let data = {
            "currentLocationInUnsortedByIndex": pathToUnsortedPortrayalByIndex,
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
        let pathToUnsortedPortrayal = document.getElementById("ws_below").firstChild.src; // Careful: file:///E:/$unsorted/someImage.jpg
        if (pathToUnsortedPortrayal === undefined) {
            console.log("No portrayal selected");
        } else {
            // Remove the "file:///" prefix
            pathToUnsortedPortrayal = pathToUnsortedPortrayal.substring(8);
            // Covert / to \\
            pathToUnsortedPortrayal = pathToUnsortedPortrayal.replace(/\//g, "\\");
            let pathToUnsortedPortrayalByIndex = 0;
            for (let i = 0; i < unsortedPortrayals.length; i++) {
                console.log(`Comparing ${unsortedPortrayals[i]} with ${pathToUnsortedPortrayal}`);
                if (unsortedPortrayals[i] === pathToUnsortedPortrayal.toString()) {
                    pathToUnsortedPortrayalByIndex = i;
                    break;
                }
            }
            console.log(pathToUnsortedPortrayalByIndex);
            client.ask_sort_please(pathToUnsortedPortrayalByIndex, selectedTags, document.getElementById("originInputField").value, personaInputField.value);
            unsortedPortrayals.splice(pathToUnsortedPortrayalByIndex, 1); // Remove entry from unsorted container
            document.getElementsByClassName("uns_element")[pathToUnsortedPortrayalByIndex].remove(); // Remove instance from uns_elements class by index
        }

    }
};





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