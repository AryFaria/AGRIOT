#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <FirebaseArduino.h>


#define FIREBASE_HOST "agriot-2-0-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "lXAfi1roOWBGw8CkdsElHqQpIulBW64wp2deIMzA"


#define relay_pin 5
#define red_led 14
#define yellow_led 12
#define green_led 13
#define sensor_pin A0

void internetError();
void systemOk();

void setup()
{
  WiFi.mode(WIFI_AP_STA);
  Serial.begin(115200);
  WiFiManager manager;

  pinMode(relay_pin, OUTPUT);
  pinMode(red_led, OUTPUT);
  pinMode(yellow_led, OUTPUT);
  pinMode(green_led, OUTPUT);

  internetError();

  bool res;
  res = manager.autoConnect("ESP8266Config", "123456789");

  if (!res) {
    Serial.println("Falha ao se conectar, verifique as credencias!");
    internetError();
  }
  else {
    Serial.println("AGRIOT conectado ao WiFi com sucesso!");
    systemOk();
  }


  WiFi.begin();
  delay(2000);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop()
{
  if (WiFi.status() == 3) {
    systemOk();
    if (Firebase.failed())
    {
      Serial.println("Falha de conexão com o Firebase...");
      digitalWrite(red_led, HIGH);
      digitalWrite(green_led, HIGH);
      digitalWrite(yellow_led, HIGH);
      return;
    }
    else
    {
      int sensor_value = analogRead(sensor_pin);
      int filter_sensor_value = map(sensor_value, 0, 1023, 0, 100);
      String _system_mode = Firebase.getString("agriot/system/mode");
      Firebase.setString("agriot/system/sensor_value", String(filter_sensor_value));
      if (_system_mode == "manual")
      {
        int _relay_status = Firebase.getInt("agriot/system/relay_value");
        if (_relay_status)
        {
          digitalWrite(relay_pin, HIGH);
          digitalWrite(yellow_led, HIGH);
        }
        else
        {
          digitalWrite(relay_pin, LOW);
          digitalWrite(yellow_led, LOW);
        }
      }
      else if (_system_mode == "auto")
      {
        if (filter_sensor_value < 20)
        {
          digitalWrite(relay_pin, HIGH);
          Firebase.setInt("agriot/system/relay_value", 1);
        }
        else
        {
          digitalWrite(relay_pin, LOW);
          Firebase.setInt("agriot/system/relay_value", 0);
        }
      }
    }
  }
  else {
    internetError();
  }
}

void internetError()
{
  digitalWrite(red_led, HIGH);
  digitalWrite(green_led, LOW);
  Serial.println("Desconectado");
  Serial.println("Verificar acesso a internet ou ponto de acesso (Router) com as suas respectivas credencias!");
}
void systemOk()
{
  digitalWrite(red_led, LOW);
  digitalWrite(green_led, HIGH);
  Serial.println("Conectado");
  Serial.println("Sistema operacional e em funcionamento!");
}
