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
#define TEMP_PIN 32
int value = 0;

OneWire oneWire(TEMP_PIN);
DallasTemperature sensors(&oneWire);
float temperatureC;

void sendTemp() {
  sensors.requestTemperatures();
  temperatureC = sensors.getTempCByIndex(0);
}

//-------LOCALIZAÇÃO--------//

float lat, lon;
const char* googleApiKey = "";
const char* ssid = "dat-dcop";
const char* passwd = "saidaqui";

WifiLocation location (googleApiKey);

void setClock () {
    configTime (0, 0, "pool.ntp.org", "time.nist.gov");

    Serial.print ("Waiting for NTP time sync: ");
    time_t now = time (nullptr);
    while (now < 8 * 3600 * 2) {
        delay (500);
        Serial.print (".");
        now = time (nullptr);
    }
    struct tm timeinfo;
    gmtime_r (&now, &timeinfo);
    Serial.print ("\n");
    Serial.print ("Current time: ");
    Serial.print (asctime (&timeinfo));
}

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, passwd);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print("Attempting to connect to WPA SSID: ");
        Serial.println(ssid);
        Serial.print("Status = ");
        Serial.println(WiFi.status());
        delay(500);
    }
    Serial.println ("Connected");
    setClock ();
    
    location_t loc = location.getGeoFromWiFi();
  
    lat = loc.lat;
    lon = loc.lon;

}

void loop() {

  if(value < 1){

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
