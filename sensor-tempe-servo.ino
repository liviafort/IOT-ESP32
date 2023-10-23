//Analog Input
#define ANALOG_PIN_0 36
int analog_value = 0;
// PWM SERVO
#define SERVO_PIN 4
int freq = 50;
int channel = 0;
int resolution = 8;
int dutyCycle = 21;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("ESP32 Servo Control");
  pinMode(LED_BUILTIN, OUTPUT);
  ledcSetup(channel, freq, resolution);
  ledcAttachPin(SERVO_PIN, channel);
  ledcWrite(channel, dutyCycle);
}

void loop() {
  analog_value = analogRead(ANALOG_PIN_0);
  // Convert analog reading to resistance (simulate NTC characteristics)
  float resistance = map(analog_value, 0, 4095, 10000, 100); // Example conversion

  // Use a basic calibration curve to convert resistance to temperature (simulated)
  float temperature = map(resistance, 100, 10000, 25, 30); // Simulated conversion

  Serial.print("Resistance: ");
  Serial.print(resistance);
  Serial.print(" Ohms, Temperature: ");
  Serial.print(temperature);
  Serial.print("°C, Duty Cycle ==> ");
  Serial.println(dutyCycle);

  // Adjust dutyCycle based on simulated temperature
  // Calibrate this part based on your specific simulation and servo behavior
  if (temperature < 25) {
    dutyCycle = 10;
  } else if (temperature > 30) {
    dutyCycle = 33;
  }

  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);

  ledcWrite(channel, dutyCycle);
  delay(50);
}