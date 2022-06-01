#include <Servo.h>

#define ESC_PIN 9
#define ESC2_PIN 10

Servo ESC;
Servo ESC2;

int value = 180;

void setup() {
  Serial.begin(9600);
  ESC.attach(ESC_PIN, 1000, 2000);
  ESC2.attach(ESC2_PIN, 1000, 2000);
}

void loop() {
  // read value from serial port
  int tmp = Serial.parseInt();
  if (tmp == 1) {
    value = 0;
  }
  ESC.write(value);
  ESC2.write(value);
  Serial.println(value);
}