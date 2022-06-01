#include <Servo.h>

#define TILT_SERVO_PIN 9

// 60 min inclinat in sus
// 90 straight
// 120 max inclinat in jos

Servo tilt_servo;
void setup() {
    Serial.begin(9600);

    pinMode(TILT_SERVO_PIN, OUTPUT);
    tilt_servo.attach(TILT_SERVO_PIN);
}

int pos = 60;
void loop() {
    for (pos = 60; pos <= 120; pos += 1) {  // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        tilt_servo.write(pos);  // tell servo to go to position in variable 'pos'
        delay(100);           // waits 15ms for the servo to reach the position
    }
    for (pos = 120; pos >= 60; pos -= 1) {  // goes from 180 degrees to 0 degrees
        tilt_servo.write(pos);  // tell servo to go to position in variable 'pos'
        delay(100);           // waits 15ms for the servo to reach the position
    }
}