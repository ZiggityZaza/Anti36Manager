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




document.addEventListener("DOMContentLoaded", async function() {
    document.body.style.cursor = "wait";
    await client.set_anti36Local();
    await client.set_existingTags();
    await client.set_unsortedPortrayals();

    set_unsorted_panel();
    set_tags_map_in_workspace();
    set_origin_list();
    document.body.style.cursor = "default";
});