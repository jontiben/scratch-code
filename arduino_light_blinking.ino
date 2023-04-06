// Makes an LED hooked up (WITH AT LEAST 150 Ohm RESISTOR) to digital pin 13 and GND flash in the pattern of the Fibonacci Sequence

const int INTER_BLINK_DELAY = 200; // Delay between unit-flashes when 'displaying' a number
const int INTER_VALUE_DELAY = 1000; // Delay between numbers

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

void loop() {
  
  // Fibonacci sequence as a flashing LED
  int i = 0;
  int j = 1;
  int new_value;
  int counter;
  int internal_counter;

  for (counter = 0; counter < 20; ++counter) {

    for (internal_counter = 0; internal_counter < j; ++internal_counter) {
      digitalWrite(13, HIGH);
      delay(INTER_BLINK_DELAY);
      digitalWrite(13, LOW);
      delay(INTER_BLINK_DELAY);
    }

    new_value = i + j;
    i = j;
    j = new_value;
    delay(INTER_VALUE_DELAY);
  }
}
