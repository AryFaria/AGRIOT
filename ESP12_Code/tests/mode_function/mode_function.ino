char value_mode = '0';

void manual_mode() {
  while (value_mode == '0' && char(Serial.read()) != '1') {
    Serial.println("Manual mode working");
    delay(300);
  }
}
void automatic_mode() {
  while (value_mode == '1' && char(Serial.read()) != '0') {
    Serial.println("Automatic mode working");
    delay(300);
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
      automatic_mode();
    }
  }
}
