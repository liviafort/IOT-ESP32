int dutyCycle = 0;

// Analog Input
#define ANALOG_PIN_0 36
int analog_value = 0;

// PWM LED
#define LED_PIN 4
int freq = 5000;
int ledChannel = 0;
int resolution = 8;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("ESP32 Analog IN/OUT Test");
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(LED_PIN, ledChannel);
  ledcWrite(ledChannel, dutyCycle);
}
 
void loop() {
  analog_value = analogRead(ANALOG_PIN_0);
  Serial.println(analog_value);
  int mappedValue = map(analog_value, 0, 4095, 0, 255);
  ledcWrite(ledChannel, mappedValue);
  Serial.println("OIIIIIIIIIII");
  Serial.println(mappedValue);
  delay(500);
}

//canal PWM usando ledcSetup(ledChannel, freq, resolution). Isso define as características do canal PWM, incluindo a frequência em hertz (freq) e 
//a resolução em bits (resolution). No seu código, a frequência é definida como 5000 Hz e a resolução como 8 bits.
//pino LED ao canal PWM usando ledcAttachPin(LED_PIN, ledChannel). Isso direciona o sinal PWM gerado pelo canal para o pino LED (pino 4, no seu caso).
//o ciclo de trabalho do PWM usando ledcWrite(ledChannel, mappedValue). O valor de mappedValue controla a largura dos pulsos PWM enviados para o pino LED. 
//Quanto maior o valor, maior será a largura dos pulsos, o que resulta em um brilho mais intenso no LED.