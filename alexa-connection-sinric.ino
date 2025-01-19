#include <WiFi.h>
#include <ArduinoJson.h>
#include <SinricPro.h>
#include <SinricProFan.h> 

const char* SSID = "Wokwi-GUEST";
const char* PASSWORD = "";

const char* APP_KEY = "76d65884-9bed-4842-a119-30d7892818e7";
const char* APP_SECRET = "01d5ef5c-6cb7-4e84-bb6a-32f92f01febd-ed033060-be79-46ec-b890-284b611a75aa"; 

const char* DEVICE_ID = "678d0adcb15d6ea198e425c9";

#define RELAY_PIN 23

bool relayState = false;

bool onPowerState(const String &deviceId, bool &state) {
  relayState = state;
  digitalWrite(RELAY_PIN, relayState ? HIGH : LOW); 
  Serial.printf("Ventilador %s\n", relayState ? "Ligado" : "Desligado");
  return true;
}

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  WiFi.begin(SSID, PASSWORD);
  Serial.print("Conectando ao WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado!");

  Serial.println("Configurando Sinric Pro...");
  SinricPro.begin(APP_KEY, APP_SECRET); 
  SinricPro.restoreDeviceStates(true);

  SinricProFan& fan = SinricPro[DEVICE_ID];
  fan.onPowerState(onPowerState); 

  Serial.println("Sinric Pro inicializado!");
}


void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Desconectado do WiFi! Tentando reconectar...");
    WiFi.reconnect();
    delay(5000);
  }
  
  SinricPro.handle();  
  delay(500);
}
