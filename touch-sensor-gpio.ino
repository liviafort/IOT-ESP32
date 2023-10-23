//LER O TOUCH SENSOR 0 (T0) ASSOCIADO AO GPIO

/*T0: GPIO 4
T1: GPIO 0
T2: GPIO 2
T3: GPIO 15
T4: GPIO 13
T5: GPIO 12
T6: GPIO 14
T7: GPIO 27
T8: GPIO 33
T9: GPIO 32*/

#define TOUTCH_PIN T0
#define LED_PIN 2
 
int touch_value = 100;
 
void setup(){
  Serial.begin(115200);
  delay(1000);
  Serial.println("ESP32 Touch Test");
  pinMode(LED_PIN, OUTPUT);
  digitalWrite (LED_PIN, LOW);
}
 
void loop(){
  touch_value = touchRead(TOUTCH_PIN);
  Serial.println(touch_value);
  if (touch_value < 50){
    Serial.println("OIIIIIIIIIII");
    digitalWrite (LED_PIN, HIGH);
  }
  else{
    digitalWrite (LED_PIN, LOW);
  }
  delay(1000);
}