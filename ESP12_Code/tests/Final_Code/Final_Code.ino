#define relay 5
#define sensor_pin A0

String color, relay_status = "";
char value_mode = '0';

void manual_mode() {
  while (value_mode == '0' && char(Serial.read()) != '1') {
    int sensor_value = analogRead(sensor_pin);
    int filter_sensor_value = map(sensor_value, 0, 1023, 0, 100);

    Serial.print("Manual mode working ==> ");

    if (filter_sensor_value < 16) {
      color = "Red";
    }
    else if ((filter_sensor_value > 15) && (filter_sensor_value < 31)) {
      color = "Orange";
    }
    else if ((filter_sensor_value > 30) && (filter_sensor_value < 46)) {
      color = "Yellow";
    }
    else if ((filter_sensor_value > 45) && (filter_sensor_value < 100)) {
      color = "Green";
    }
    else {
      color = " ";
    }
    relay_status = (digitalRead(relay) == 0)? "LOW" : "HIGH";
    Serial.println("Color: " + String(color) + " | Value: " + String(filter_sensor_value) + " | Relay Status: " + String(relay_status));
    delay(1000);
  }
}
void automatic_mode() {
  while (value_mode == '1' && char(Serial.read()) != '0') {
    int sensor_value = analogRead(sensor_pin);
    int filter_sensor_value = map(sensor_value, 0, 1023, 0, 100);

    Serial.print("Automatic mode working ==> ");
    if (filter_sensor_value < 16) {
      color = "Red";
      digitalWrite(relay, HIGH);
    }
    else if ((filter_sensor_value > 15) && (filter_sensor_value < 31)) {
      color = "Orange";
      digitalWrite(relay, LOW);
    }
    else if ((filter_sensor_value > 30) && (filter_sensor_value < 46)) {
      color = "Yellow";
      digitalWrite(relay, LOW);
    }
    else if ((filter_sensor_value > 45) && (filter_sensor_value < 100)) {
      color = "Green";
      digitalWrite(relay, LOW);
    }
    else {
      color = " ";
      digitalWrite(relay, LOW);
    }
    
    relay_status = (digitalRead(relay) == 0)? "LOW" : "HIGH";
    Serial.println("Color: " + String(color) + " | Value: " + String(filter_sensor_value) + " | Relay Status: " + String(relay_status));
    delay(1000);
  }
}


void setup() {
  Serial.begin(9600);
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("#########################");
  Serial.println("#   CHANGING THE MODE   #");
  Serial.println("#      MANUAL MODE      #");
  Serial.println("#########################");
  manual_mode();
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);
}
void loop() {
  if (Serial.available() > 0) {
    value_mode = Serial.read();
    if (value_mode == '0') {
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("#########################");
      Serial.println("#   CHANGING THE MODE   #");
      Serial.println("#      MANUAL MODE      #");
      Serial.println("#########################");
      digitalWrite(relay, LOW);
      manual_mode();
    }
    else if (value_mode == '1') {
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("");
      Serial.println("#########################");
      Serial.println("#   CHANGING THE MODE   #");
      Serial.println("#    AUTOMATIC  MODE    #");
      Serial.println("#########################");
      digitalWrite(relay, LOW);
      automatic_mode();
    }
  }
}
