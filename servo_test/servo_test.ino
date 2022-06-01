#include <Servo.h>

#define PISTON_PIN 11

// timers
#define PRESSED_PISTON_DURATION 1000

// servo limits
#define PISTON_PRESSED_ANGLE 25
#define PISTON_NOT_PRESSED_ANGLE 150

// brain def
class Brain {
   private:
    Servo Piston;

    // servo helper functions
    void press_piston() {
        Piston.write(PISTON_PRESSED_ANGLE);
    }
    void release_piston() {
        Piston.write(PISTON_NOT_PRESSED_ANGLE);
    }

   public:
    void setup() {
        Piston.attach(PISTON_PIN);
        release_piston();
    }

    void loop() {
        // Serial.println("I am class");
        // Piston.write(piston_angle);
    }

    void shoot_once() {
        press_piston();
        delay(PRESSED_PISTON_DURATION);
        release_piston();
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