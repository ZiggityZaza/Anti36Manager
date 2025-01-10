let counter = 0;
let counterOn = true;


class HttpClient {
    constructor() {
        this.messageReceived = {};
        this.messageToSend = {};
    }

    get() {
        fetch('http://localhost:8080')
        .then(response => response.json())
        .then(data => {
            console.log('Message received:', data);
            this.messageReceived = data;
        });
    }

    post() {
        this.messageToSend = {
            counter: counter,
            counterOn: counterOn
        };
        fetch('http://localhost:8080/post', {mode: 'no-cors', method: 'POST', headers: {'Content-Type': 'application/json'}, body: JSON.stringify(this.messageToSend)});
    }

    update() {
        this.get();
        this.post();
    };
}

let client = new HttpClient();
client.update();






function set_unsorted_values() {
    let unsortedList = document.getElementsByClassName("unsorted");
    let unsortedListHeader = document.getElementById("uns_head");
    unsortedListHeader.innerHTML = "Fetching data...";

    for (let i = 0; i < client.messageReceived["unsortedPortrayals"].length; i++) {
        let path = client.messageReceived["unsortedPortrayals"][i];
        let display = null;
        let extension = path.split('.').pop();
        switch (extension) {
            case "jpg": case "jpeg": case "png": case "gif": case "bmp": case "webp":
                display = document.createElement("img");
                break;
            case "mp4": case "webm": case "mkv": case "avi":
                display = document.createElement("video");
                display.muted = true;
                display.addEventListener("mouseover", function() {
                    display.play();
                });
                display.addEventListener("mouseout", function() {
                    display.pause();
                });
        }

        display.setAttribute("loading", "lazy"); // Not sure if it really does anything
        display.className = "uns_element";
        display.src = path;

        // When clicked
        display.onclick = function() {
            let workspace = document.getElementById("ws_selected");

            // Place the media in the workspace
            let workspaceMedia = null;
            switch (extension) {
                case "jpg": case "jpeg": case "png": case "gif": case "bmp": case "webp":
                    workspaceMedia = document.createElement("img");
                    break;
                case "mp4": case "webm": case "mkv": case "avi":
                    workspaceMedia = document.createElement("video");
                    workspaceMedia.setAttribute("controls", "controls");
            }
            workspaceMedia.src = path;
            workspaceMedia.id = "ws_selected";

            // Clear the workspace when clicked
            workspace.innerHTML = workspaceMedia.outerHTML;
        }

        unsortedList[0].appendChild(display); // Only supports first unsorted list
    }

    unsortedListHeader.innerHTML = client.messageReceived["unsortedPortrayals"].length;
    unsortedListHeader.innerHTML += " files in \"";
    unsortedListHeader.innerHTML += client.messageReceived["UNSORTED_FOLDER_PATH"] += '"';

    document.body.style.cursor = "default";
}


// Entry point
document.addEventListener("DOMContentLoaded", function() {
    document.body.style.cursor = "wait";
    setTimeout(function() {
        set_unsorted_values(); // Takes care of returning the cursor to normal
    }, 1000);
});





function addSomething() {
    let path = client.messageReceived["files"][counter];
    const container = document.getElementById("f");
    const img = document.createElement("img");
    img.src = path;
    img.width = 100;
    container.appendChild(img);
}

function refreshCounter() {
    document.getElementById("c").innerHTML = counter;
    if (!counterOn) {
        document.getElementById("c").innerHTML = "";
    }
    client.post();
}

function decreaseCounter() {
    if (counterOn) {
        counter--;
    }
    refreshCounter();
}

function increaseCounter() {
    if (counterOn) {
        counter++;
    }
    refreshCounter();
}

function resetCounter() {
    document.getElementById("f").innerHTML = "";
    if (counterOn) {
        counter = 0;
    }
    refreshCounter();
}

function toggleCounter() {
    counterOn = !counterOn;
    refreshCounter();
}


