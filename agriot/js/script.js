import * as firebase from "/js/firebase.js"

function saveRelayState(state) 
{
    var percentage = document.querySelector('.percentage');
    var percentage = percentage.textContent.replace("%", "");
    firebase.sendData('manual', state, percentage);
}

let relay_button_state = 0;
function changeRelayState() 
{

    if (relay_button_state == 0)
    {
        document.querySelector('.relay_button').style.backgroundColor = '#21C063';
        document.querySelector('.relay_button').style.color = 'white';
        var newEl = document.createElement("i");
        newEl.classList = "fa-solid fa-power-off fa-2xl";
        var title = document.querySelector(".fa-beat");
        var master_elem = title.parentNode;
        master_elem.replaceChild(newEl, title);
        relay_button_state = 1;
        saveRelayState(relay_button_state);
    }
    else
    {
        document.querySelector('.relay_button').style.backgroundColor = '#1c1e26';
        document.querySelector('.relay_button').style.color = '#21C063';
        var newEl = document.createElement("i");
        newEl.classList = "fa-solid fa-power-off fa-beat fa-2xl";
        var title = document.querySelector(".fa-power-off");
        var master_elem = title.parentNode;
        master_elem.replaceChild(newEl, title);
        relay_button_state = 0;
        saveRelayState(relay_button_state);
    }

}


export var mode_button_state = 'manual';
export function changeMode() 
{

    if (mode_button_state == 'manual') 
    {
        relay_button_state = 0;
        mode_button_state = 'auto';
        document.querySelector('.mode_state_button').style.backgroundColor = '#E34234';
        document.querySelector('.relay_button').style.backgroundColor = '#1c1e26';
        document.querySelector('.relay_button').style.pointerEvents = 'none';
        document.querySelector('.mode_state_button').style.color = 'white';
        document.querySelector('.relay_button').style.color = '#E34234';
        var percentage = document.querySelector('.percentage');
        var percentage = percentage.textContent.replace("%", "");
        firebase.sendData('auto', relay_button_state, percentage);
    }
    else
    {
        mode_button_state = 'manual';
        document.querySelector('.mode_state_button').style.backgroundColor = '#1c1e26';
        document.querySelector('.relay_button').style.backgroundColor = '#1c1e26';
        document.querySelector('.mode_state_button').style.color = '#E34234';
        document.querySelector('.relay_button').style.pointerEvents = 'auto';
        document.querySelector('.relay_button').style.color = '#21C063';
        relay_button_state = 1;
        changeRelayState();
    }

}

window.changeMode = changeMode;
window.saveRelayState = saveRelayState;
window.changeRelayState = changeRelayState;
