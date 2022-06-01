#include <Servo.h>

#define ESC1_PIN 9
#define ESC2_PIN 10
#define PISTON_PIN 11

// times
#define PRESSED_PISTON_DURATION 1000
#define ESC_POWER_ON_DURATION 1000
#define ESC_POWER_OFF_DURATION 1000

// servo limits
#define PISTON_PRESSED_ANGLE 25
#define PISTON_NOT_PRESSED_ANGLE 150

// ESC limits
#define ESC_POWER 20 // [0, 180]

// brain def
class Brain {
   private:
    Servo Piston;
    Servo ESC1;
    Servo ESC2;

    // servo helper functions
    void press_piston() {
        Piston.write(PISTON_PRESSED_ANGLE);
    }
    void release_piston() {
        Piston.write(PISTON_NOT_PRESSED_ANGLE);
    }
    void turn_on_esc() {
        ESC1.write(ESC_POWER);
        ESC2.write(ESC_POWER);
    }
    void turn_off_esc() {
        ESC1.write(0);
        ESC2.write(0);
    }

   public:
    void setup() {
        Piston.attach(PISTON_PIN);
        ESC1.attach(ESC1_PIN, 1000, 2000);
        ESC2.attach(ESC2_PIN, 1000, 2000);

        turn_off_esc();
        release_piston();
    }

    void loop() {
        // Serial.println("I am class");
        // Piston.write(piston_angle);
    }

    void shoot_once() {
        Serial.println("shoot once");
        // turn on esc
        turn_on_esc();

        // wait for esc to power on
        delay(ESC_POWER_ON_DURATION);

        press_piston();
        delay(PRESSED_PISTON_DURATION);
        release_piston();

        // turn off esc
        turn_off_esc();
        // wait for esc to power off
        delay(ESC_POWER_OFF_DURATION);
    }
};

Brain brain;

void setup() {
    Serial.begin(9600);

    brain.setup();
}

void loop() {
    brain.loop();

    if (Serial.available() > 0) {
        char tmp = Serial.read();
        if (tmp != '\n') {
            switch (tmp) {
                case 's':
                    brain.shoot_once();
                    break;
                case 'S':
                    brain.shoot_once();
                    break;
                default:
                    Serial.print("Invalid command: 0x");
                    Serial.println(tmp, HEX);
                    break;
            }
        }
    }
}