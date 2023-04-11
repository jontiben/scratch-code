#include "DHT.h"

#define DHTPIN A5 // The digital pin connected to the DHT sensor's signal pin
#define BUTTONPIN 0
#define DHTTYPE DHT11 // Use DHT11 instead of DHT22

DHT dht(DHTPIN, DHTTYPE);

bool data_mode = true; // true is temp, false is humidity
bool reading_button = true;

/* Pins:
1d	tc	tl	2d	3d  tr
bl	bc	dt	br	cc	4d
*/
// tc = top center, rd = fourth digit, etc.

// Digit select pins
const int ds1 = 2;
const int ds2 = 3;
const int ds3 = 4;
const int ds4 = 5;

// Display pins
const int a = 6; // tc
const int b = 7; // tl
const int c = 8; // tr
const int d = 9; // bl
const int e = 10; // bc
const int f = 11; // br
const int g = 12; // cc
const int dt = 13; // dt

void setup() { 
  pinMode(2, INPUT);
  dht.begin();
  pinMode(0, INPUT);

  pinMode(A4, OUTPUT); // temp mode LED

  pinMode(ds1, OUTPUT);
  pinMode(ds2, OUTPUT);
  pinMode(ds3, OUTPUT);
  pinMode(ds4, OUTPUT);

  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(dt, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int button_value = digitalRead(BUTTONPIN);

  if (reading_button) {
    if (button_value == 1) {
      reading_button = false;
      data_mode = !data_mode;
    }
  } else if (button_value == 0) { // low
    reading_button = true;
  }
  
  if (data_mode) {
    float temperature = dht.readTemperature();
    float fahrenheit_temp = temperature * 1.8 + 32;
    analogWrite(A4, 255);
    display_number(fahrenheit_temp);
    Serial.println(String(fahrenheit_temp));
  } else {
    float humidity = dht.readHumidity();
    analogWrite(A4, 0);
    display_number(humidity);
    Serial.println(String(humidity));
  }
  

}

void display_number(float number) {
  String str_number = String(number, 4);
  int current_digit = 0;

  for (int i = 0; i < str_number.length() && current_digit < 4; i++) {
    clear_digits();

    if (str_number[i] == '.') {
      continue; // Skip the current iteration and move to the next character
    }

    switch (current_digit) {
      case 0:
        digit_1();
        break;
      case 1:
        digit_2();
        break;
      case 2:
        digit_3();
        break;
      case 3:
        digit_4();
        break;
    }

    int current_char = int(str_number[i]) - 48;
    bool decimal_point = (i + 1 < str_number.length()) && (str_number[i + 1] == '.');

    display_char(current_char, decimal_point);
    current_digit++;

    delay(5);
  }
}

void clear_digits() {
  digitalWrite(ds1, HIGH);
  digitalWrite(ds2, HIGH);
  digitalWrite(ds3, HIGH);
  digitalWrite(ds4, HIGH);
}

void digit_1() {
  digitalWrite(ds1, HIGH);
  digitalWrite(ds2, HIGH);
  digitalWrite(ds3, LOW);
  digitalWrite(ds4, HIGH);  
}

void digit_2() {
  digitalWrite(ds1, HIGH);
  digitalWrite(ds2, LOW);
  digitalWrite(ds3, HIGH);
  digitalWrite(ds4, HIGH);  
}

void digit_3() {
  digitalWrite(ds1, LOW);
  digitalWrite(ds2, HIGH);
  digitalWrite(ds3, HIGH);
  digitalWrite(ds4, HIGH);
}

void digit_4() {
  digitalWrite(ds1, HIGH);
  digitalWrite(ds2, HIGH);
  digitalWrite(ds3, HIGH);
  digitalWrite(ds4, LOW);
}

//

void display_char(int number, bool decimal_point) {
  digitalWrite(a, number != 1 && number != 4);
  digitalWrite(b, number != 1 && number != 2 && number != 3 && number != 7);
  digitalWrite(c, number != 5 && number != 6);
  digitalWrite(d, number != 1 && number != 3 && number != 4 && number != 5 && number != 7 && number != 9);
  digitalWrite(e, number != 1 && number != 4 && number != 7);
  digitalWrite(f, number != 2);
  digitalWrite(g, number != 0 && number != 1 && number != 7);

  if (decimal_point) {
    dot_on();
  } else {
    dot_off();
  }
}

void dot_on() {
  digitalWrite(dt, HIGH);
}

void dot_off() {
  digitalWrite(dt, LOW);
}

/* Arduino pin hookups:

Digital side:
  0 (RX)  Negative side of temp/humidity toggle button, after lead for resistor to ground.
  2       3rd digit selection pin of display (3d)
  3~      2nd digit selection pin of display (2d)
  4       1st digit selection pin of display (1d)
  5~      4th digit selection pin of display (4d)
  6~      Through 100Ω resistor to a/tc of display
  7       Through 100Ω resistor to b/tl "
  8       Through 100Ω resistor to c/tr "
  9~      Through 100Ω resistor to d/bl "
  10~     Through 100Ω resistor to e/bc "
  11~     Through 100Ω resistor to f/br "
  12      Through 100Ω resistor to g/cc "
  13      Through 100Ω resistor to dt "
Analog side:
  5V  	  Positive strip of board
  GND(#2) Ground/negative strip of board
  A4      Through 1000Ω resistor to positive side of temp mode indicator LED
  A5      To signal wire (red) of temp/humidity sensor   

*/

