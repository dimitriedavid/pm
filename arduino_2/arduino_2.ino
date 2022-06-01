#include <SoftwareSerial.h>
#include <Servo.h>

#pragma region Arduino2_Config
// verde rx
// alb tx
SoftwareSerial Arduino1(2, 3);  // RX | TX

void initArduino1() {
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    Arduino1.begin(9600);
    Arduino1.setTimeout(0);
    Serial.println("Arduino 1 serial initialized\n");
}

void parseArduinoInput(String tmp) {
    if (tmp.length() == 0) {
        return;
    }

    for (int i = 0; i < tmp.length(); i++) {
        switch (tmp[i]) {
            case 'u':
                tiltServoUp();
                break;
            case 'd':
                tiltServoDown();
                break;
            case 's':
                shoot();
                break;
            default:
                Serial.print("Invalid input: ");
                Serial.println(tmp[i]);
                break;
        }
    }
}

#pragma endregion Arduino2_Config

#pragma region Tilt_Servo_Config
#define TILT_SERVO_PIN 5

#define TILT_SERVO_MIN_ANGLE 60
#define TILT_SERVO_MIDDLE_ANGLE 90
#define TILT_SERVO_MAX_ANGLE 100

#define TILT_SERVO_STEP 1

int tiltServoPosition = TILT_SERVO_MIDDLE_ANGLE;

Servo tilt_servo;

void initTiltServo() {
    pinMode(TILT_SERVO_PIN, OUTPUT);
    tilt_servo.write(TILT_SERVO_MIDDLE_ANGLE);
    tilt_servo.attach(TILT_SERVO_PIN);
}

void tiltServoUp() {
    Serial.println("Tilt servo up");
    if (tiltServoPosition + TILT_SERVO_STEP < TILT_SERVO_MAX_ANGLE) {
        tilt_servo.write(tiltServoPosition + TILT_SERVO_STEP);
        tiltServoPosition += TILT_SERVO_STEP;
    }
}

void tiltServoDown() {
    Serial.println("tiltServoDown");
    if (tiltServoPosition - TILT_SERVO_STEP > TILT_SERVO_MIN_ANGLE) {
        tilt_servo.write(tiltServoPosition - TILT_SERVO_STEP);
        tiltServoPosition -= TILT_SERVO_STEP;
    }
}

#pragma endregion Tilt_Servo_Config

#pragma region Shooter_Config
#define PISTON_PIN 6
#define ESC1_PIN 9
#define ESC2_PIN 10

#define PISTON_PRESSED_ANGLE 22
#define PISTON_NOT_PRESSED_ANGLE 150

#define ESC_MAX_POWER 15 // out of 180

Servo Piston;
Servo ESC1;
Servo ESC2;

void initShooter() {
    pinMode(PISTON_PIN, OUTPUT);
    pinMode(ESC1_PIN, OUTPUT);
    pinMode(ESC2_PIN, OUTPUT);

    Piston.write(PISTON_NOT_PRESSED_ANGLE);
    Piston.attach(PISTON_PIN);
    ESC1.attach(ESC1_PIN, 1000, 2000);
    ESC2.attach(ESC2_PIN, 1000, 2000);
    ESC1.write(0);
    ESC2.write(0);

    Serial.println("Shooter initialized");
}

void shoot() {
    ESC1.write(ESC_MAX_POWER);
    ESC2.write(ESC_MAX_POWER);

    delay(500);

    Piston.write(PISTON_PRESSED_ANGLE);

    delay(500);

    ESC1.write(0);
    ESC2.write(0);
    Piston.write(PISTON_NOT_PRESSED_ANGLE);
}

#pragma endregion Shooter_Config

void setup() {
    Serial.begin(9600);
    Serial.println("Starting setup\n");

    // Initialize Arduino 1 communication
    initArduino1();

    // Initialize Tilt Servo
    initTiltServo();

    // Initialize Shooter
    initShooter();

    Serial.println("Setup complete\n");
}

void loop() {
    if (Serial.available()) {
        String tmp = Serial.readString();
        // Serial.print("[Arduino_1_in]: ");
        // Serial.println(tmp);
        // Serial.print("[Arduino_1_in_hex]: ");
        // for (int i = 0; i < tmp.length(); i++) {
        //     Serial.print(tmp[i], HEX);
        //     Serial.print(" ");
        // }
        // Serial.println("");
        parseArduinoInput(tmp);
        // Serial.println(tiltServoPosition);
    }

    if (Arduino1.available()) {
        String tmp = Arduino1.readString();
        // Serial.print("[Arduino_1_in]: ");
        // Serial.println(tmp);
        // Serial.print("[Arduino_1_in_hex]: ");
        // for (int i = 0; i < tmp.length(); i++) {
        //     Serial.print(tmp[i], HEX);
        //     Serial.print(" ");
        // }
        // Serial.println("");
        parseArduinoInput(tmp);
        // Serial.println(tiltServoPosition);
    }
}