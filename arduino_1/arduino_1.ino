// Copyright Dimitrie David 333CA - 2022

#include <SoftwareSerial.h>
#include <Stepper.h>

#pragma region Pan_Stepper_Config
#define LIMIT_SWITCH_PIN 4
#define LIMIT_SWITCH_SEARCH_TIME 20000

#define STEPPER_LIMIT 7000
#define STEP_SIZE 30
#define MIDDLE_POSITION 3800

// Define number of steps per rotation:
const int stepsPerRevolution = 2048;

bool limitSwitchPressed() { return digitalRead(LIMIT_SWITCH_PIN) == HIGH; }

// Create stepper object called 'myStepper', note the pin order:
// 8 10 9 11
// 1 3 2 4
Stepper myStepper = Stepper(stepsPerRevolution, 10, 8, 9, 7);
int stepperPosition = 0;

void initStepper() {
    // Set the speed to 5 rpm:
    myStepper.setSpeed(15);

    Serial.println("Starting stepper initialization");
    int start_time = millis();

    while (!limitSwitchPressed()) {
        myStepper.step(-5);
        if (millis() - start_time > LIMIT_SWITCH_SEARCH_TIME) {
            Serial.println("Limit switch not found");
            Serial.println("DO NOT USE STEPPER!\n");
            return;
        }
    }

    stepperPosition = 0;

    Serial.println("Stepper initialized. Pos 0\n");
}

int stepperLeft() {
    int steps = STEP_SIZE;
    // if I have enough distance to lower limit
    if (stepperPosition - steps >= 0) {
        stepperPosition -= steps;
        myStepper.step(-steps);

        return 1;
    }

    // limit reached
    return 0;
}

int stepperRight() {
    int steps = STEP_SIZE;
    // if I have enough distance to lower limit
    if (stepperPosition + steps <= STEPPER_LIMIT) {
        stepperPosition += steps;
        myStepper.step(steps);

        return 1;
    }

    // limit reached
    return 0;
}

void stepperMiddle() {
    int steps = MIDDLE_POSITION - stepperPosition;
    stepperPosition = MIDDLE_POSITION;
    myStepper.step(steps);
}
#pragma endregion Pan_Stepper

#pragma region Arduino2_Config
// verde rx
// alb tx
SoftwareSerial Arduino2(2, 3);  // RX | TX

void initArduino2() {
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    Arduino2.begin(9600);
    Serial.println("Arduino 2 serial initialized\n");
}

#pragma endregion Arduino2_Config

#pragma region Bluetooth_Config
/*
    Bluetooth input:
    l - move left
    r - move right

    u - move up
    d - move down

    zp - middle pan
    zt - middle tilt

    s - shoot
*/

SoftwareSerial MyBlue(5, 6);  // RX | TX

void initBluetooth() {
    pinMode(5, INPUT);
    pinMode(6, OUTPUT);
    MyBlue.begin(9600);
    Serial.println("Bluetooth initialized");
    Serial.println("Defualt password is 1234 or 0000\n");
}

void parseBluetoothInput(String tmp) {
    if (tmp.length() == 0) {
        return;
    }

    for (int i = 0; i < tmp.length(); i++) {
        switch (tmp[i]) {
            case 'l':
                if (!stepperLeft()) {
                    MyBlue.println("Left limit reached");
                }
                break;
            case 'r':
                if (!stepperRight()) {
                    MyBlue.println("Right limit reached");
                }
                break;
            case 'z':
                switch (tmp[i + 1]) {
                    case 'p':
                        stepperMiddle();
                        break;
                    case 't':
                        Arduino2.print('zt');
                        break;
                default:
                    MyBlue.print("Invalid input: z");
                    MyBlue.println(tmp[i + 1]);
                    break;
                }
                i++;
                break;
            case 'u':
                Arduino2.print('u');
                break;
            case 'd':
                Arduino2.print('d');
                break;
            case 's':
                Arduino2.print('s');
                break;
            default:
                MyBlue.print("Invalid input: ");
                MyBlue.println(tmp[i]);
                break;
        }
    }
}

#pragma endregion Bluetooth_Config

void setup() {
    Serial.begin(9600);
    Serial.setTimeout(0);
    Serial.println("Starting setup\n");

    // Initialize Arduino 2
    initArduino2();

    // Initialize bluetooth
    // initBluetooth();

    // Initialize stepper
    pinMode(LIMIT_SWITCH_PIN, INPUT_PULLUP);
    initStepper();

    Serial.println("Setup complete\n");
}

void loop() {
    if (Serial.available()) {
        String tmp = Serial.readString();
        // Serial.print("[Bluetooth_in]: ");
        // Serial.println(tmp);
        // Serial.print("[Bluetooth_in_hex]: ");
        // for (int i = 0; i < tmp.length(); i++) {
        //     Serial.print(tmp[i], HEX);
        //     Serial.print(" ");
        // }
        // Serial.println("");
        parseBluetoothInput(tmp);
    }
}