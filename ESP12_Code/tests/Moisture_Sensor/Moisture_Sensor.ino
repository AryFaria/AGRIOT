#define sensor_pin A0

String color = "";
void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensor_value = analogRead(sensor_pin);
  int filter_sensor_value = map(sensor_value, 0, 1023, 0, 100);

  Serial.println("Color: " + String(color) + " | Value: " + String(filter_sensor_value));
  delay(500);
}
