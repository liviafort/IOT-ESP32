#include "DHT.h"
#define DHTPIN 23
#define DHTTYPE DHT22
 
DHT dht(DHTPIN, DHTTYPE);

float localHum = 0;
float localTemp = 0;
 
void setup(){
    
    Serial.begin(115200);
    delay(1000);
    Serial.println("");
    Serial.println("ESP32 DHT Temperature and Humidity ");
    Serial.println("");
    dht.begin();
    
}
 
void loop(){
    getDHT();
    Serial.print("Temp: ==&gt; ");
    Serial.print(localTemp);
    Serial.print("  Hum ==&gt; ");
    Serial.println(localHum);
    delay(2000);
}
    
void getDHT(){

    float tempIni = localTemp;
    float humIni = localHum;
    localTemp = dht.readTemperature();
    localHum = dht.readHumidity();
    
    if (isnan(localHum) || isnan(localTemp)){
    
        localTemp = tempIni;
        localHum = humIni;
        return;
    }
}