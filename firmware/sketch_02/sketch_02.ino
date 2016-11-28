#include "RoboticArm.h"
#include "RoboticArmParser.h"

RoboticArm arm;
RoboticArmParse parser(&arm);
int sample;

#define BTN 1
#define LED 2

void setup() {

  Serial.begin(9600);

  arm.addInitialState(0, 60, 130, 0);

  arm.setSpeeds(15, 15, 15);

  arm.init(3, 5, 6, 9);

  sample = 0;
}

void loop() {
    if (Serial.available()) {
        String code = Serial.readString();
        if (!sample && code.charAt(0) == 'b')
            parser.parseString(code);

        if (sample && code.charAt(0) == 's') {
            sample = 1;
            parser.parseState(code);
        }
    }

    if (digitalRead(BTN)) {
        if (sample) {
            parser.toInitialState();
            sample = 0;
        } else {
            arm.executeActions();
        }
    }

    digitalWrite(LED, sample);
}
