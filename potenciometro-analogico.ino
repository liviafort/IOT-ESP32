//ler uma entrada analógica
#define ANALOG_PIN_0 27
int analog_value = 0;
 
void setup(){
  Serial.begin(115200);
  delay(1000);
  Serial.println("ESP32 Analog IN Test");
}
 
void loop(){
  analog_value = analogRead(ANALOG_PIN_0);
  Serial.println(analog_value);
  delay(500);
}
