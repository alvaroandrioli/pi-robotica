  #include "RoboticArm.h"
#include "RoboticArmParser.h"

RoboticArm arm;
RoboticArmParse parse(&arm);

void setup() {

  Serial.begin(9600);

  arm.addInitialState(0, 0, 0, 0);

  arm.setSpeeds(30, 30, 30);

  arm.init(3, 5, 6, 9);
}

void loop() {
    char res = Serial.read();
    if (Serial.available()) {
        parse.parseString(Serial.readString());
        arm.printSerial();
    }
}
