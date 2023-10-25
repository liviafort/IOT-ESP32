#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "HTTPClient.h"
#include "ArduinoJson.h"
#include "DallasTemperature.h"
#include "OneWire.h"
#include "Arduino.h"
#include "WifiLocation.h"
 #include "QuickDebug.h"

//--------TEMPERATURA--------//

#define MAX_TEMP 28
#define TEMP_PIN 18

OneWire oneWire(TEMP_PIN);
DallasTemperature sensors(&oneWire);
float temperatureC;

void sendTemp() {
  sensors.requestTemperatures();
  temperatureC = sensors.getTempCByIndex(0);
}

//-------LOCALIZAÇÃO --------//

const char* googleApiKey = "";
WifiLocation location(googleApiKey);
float lat, lon;

void sendLoc(){
  Serial.println(location.getStatus());
  location_t loc = location.getGeoFromWiFi();
  lat = loc.lat;
  lon = loc.lon;
}

//--------------------------//

const char* ssid = "dat-dcop";
const char* password = "saidaqui";

int value = 0;

AsyncWebServer server(80);

void setup() {
  
  Serial.begin(115200);
  sensors.begin();
  delay(4000);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); 
  
  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.println("Conectando ao wifi..");
  }
  Serial.println("Conectado!!!");
  
}
  
void loop() {

  if(value < 1){

    sendLoc();
    delay(1000);
    sendTemp();

    if(WiFi.status()== WL_CONNECTED){ 
      HTTPClient http;   
      http.begin("http://192.168.5.234:3000/esp-led");
      http.addHeader("Content-Type", "application/json");    

      StaticJsonDocument<200> doc;
      doc["value"] = value;
      doc["temp"] = temperatureC;
      doc["lat"] = lat;
      doc["lon"] = lon;
      
      String body;
      serializeJson(doc, body);
      
      int httpResponseCode = http.POST(body);
      
      if(httpResponseCode>0){
        String response = http.getString();                      
        Serial.println(httpResponseCode); 
        Serial.println(response);           
      }else{
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);
      }
      http.end();
      
    }else{
        Serial.println("Error in WiFi connection");   
    }
    delay(10000);
    value++;
  }
  
}

