import { initializeApp } from "https://www.gstatic.com/firebasejs/10.10.0/firebase-app.js";
import { getDatabase, ref, set, onValue } from "https://www.gstatic.com/firebasejs/10.10.0/firebase-database.js";
const firebaseConfig = {
    apiKey: "AIzaSyBtC_JRW3ZXEtiO2DeTwin-fGiFw8aScvQ",
    authDomain: "agriot-2-0.firebaseapp.com",
    databaseURL: "https://agriot-2-0-default-rtdb.firebaseio.com",
    projectId: "agriot-2-0",
    storageBucket: "agriot-2-0.appspot.com",
    messagingSenderId: "407001624162",
    appId: "1:407001624162:web:8d53a226c586494b6b6b3b"
};
const app = initializeApp(firebaseConfig);
const firebase = getDatabase(app);

// Send Firebase Function
export function sendData(system_mode, relay_state, sensor_state) {
    const db = getDatabase();
    set(ref(db, 'agriot/system'), {
        mode: system_mode,
        relay_value: relay_state,
        sensor_value: sensor_state
    });
}

// Receive Firebase Function
const db = getDatabase();
const starCountRef = ref(db, 'agriot/system');
onValue(starCountRef, (snapshot) => {
    const dataReceived = snapshot.val();
    var mode_valueReceived = dataReceived.mode;
    var relay_valueReceived = dataReceived.relay_value;
    var sensor_valueReceived = dataReceived.sensor_value;

    
    var percentage = document.querySelector('.percentage');
    percentage.textContent = sensor_valueReceived + "%";

    if (relay_valueReceived == 1)
    {
        document.querySelector('.relay_button').style.backgroundColor = '#21C063';
        document.querySelector('.relay_button').style.color = 'white';
    }
    else
    {
        document.querySelector('.relay_button').style.backgroundColor = '#1c1e26';
        document.querySelector('.relay_button').style.color = '#21C063';
    }

    if (mode_valueReceived == "auto")
    {
        document.querySelector('.mode_state_button').style.backgroundColor = '#E34234';
        document.querySelector('.relay_button').style.pointerEvents = 'none';
        document.querySelector('.mode_state_button').style.color = 'white';
        document.querySelector('.relay_button').style.color = '#E34234';
    }
    else
    {
        document.querySelector('.mode_state_button').style.backgroundColor = '#1c1e26';
        document.querySelector('.mode_state_button').style.color = '#E34234';
        document.querySelector('.relay_button').style.pointerEvents = 'auto';
    }
  
});

window.sendData = sendData;
