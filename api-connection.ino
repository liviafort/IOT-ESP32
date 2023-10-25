#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "HTTPClient.h"

const char* ssid = "dat-dcop";
const char* password = "saidaqui";

int value = 0;

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  delay(4000);
  //-----CONEXÃO COM O WIFI----//
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.println("Conectando ao wifi...");
  }
  Serial.println("Conectado à rede!");
  //-----REQUISIÇÃO-----//
  if(value < 10){
    Serial.println("funcionando...");
    value++;
    server.on("/esp-led", HTTP_POST, [](AsyncWebServerRequest *request){
      Serial.println("passei por aqui");
      String postData = "value=" + String(value);
      HTTPClient http;
      http.begin("http://192.168.5.234:3000/esp-led");
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      int httpResponseCode = http.POST(postData);
      if(httpResponseCode > 0){
        String response = http.getString();
        Serial.println(httpResponseCode);
        Serial.println(response);
      }else{
        Serial.println("Erro na requisição HTTP");
      }
      http.end();
    });
  }
}

void loop() {
  
}

