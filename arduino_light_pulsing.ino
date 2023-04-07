// Pulses an LED on and off slowly and smoothly

const int PULSE_LENGTH = 2000;
const int TARGET_PIN = 11; // Apparently the only PWM-capable pins are 3, 5, 6, 9, 10, and 11

int fadeAmount = 2;
int brightness = 0;

int delayTime = (PULSE_LENGTH * 2) / (PULSE_LENGTH / fadeAmount);

void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  analogWrite(TARGET_PIN, brightness);
  brightness += fadeAmount;
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  delay(delayTime); 
}
