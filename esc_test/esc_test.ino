#include <Servo.h>

#define ESC1_PIN 9
#define ESC2_PIN 10

Servo ESC1;
Servo ESC2;

int value = 0;

void setup() {
  Serial.begin(9600);
  ESC1.attach(ESC1_PIN, 1000, 2000);
  ESC2.attach(ESC2_PIN, 1000, 2000);
}

void loop() {
  // read value from serial port
  int tmp = Serial.parseInt();
  if (tmp != 0) {
    value = tmp;
  }
  ESC1.write(value);
  ESC2.write(value);
  Serial.println(value);
}