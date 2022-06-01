#include <Servo.h>

Servo ESC1;  // create servo object to control the ESC
Servo ESC2;  // create servo object to control the ESC

int potValue;  // value from the analog pin

void setup() {
    Serial.begin(9600);
    // Attach the ESC on pin 9
    ESC1.attach(
        9, 1000,
        2000);  // (pin, min pulse width, max pulse width in microseconds)
    // Attach the ESC on pin 10
    ESC2.attach(
        10, 1000,
        2000);  // (pin, min pulse width, max pulse width in microseconds)
}

void loop() {
    potValue = analogRead(
        A0);  // reads the value of the potentiometer (value between 0 and 1023)
    potValue =
        map(potValue, 0, 1023, 0, 180);  // scale it to use it with the servo
                                         // library (value between 0 and 180)
    ESC1.write(potValue);                 // Send the signal to the ESC
    ESC2.write(potValue);                 // Send the signal to the ESC
    Serial.println(potValue);
}