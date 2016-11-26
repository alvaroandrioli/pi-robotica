#include "RoboticArm.h"
#include "RoboticArmParser.h"

RoboticArm arm;
RoboticArmParse parse(&arm);

void setup() {

  Serial.begin(9600);

  arm.addInitialState(0, 60, 130, 0);

  arm.setSpeeds(15, 15, 15);

  arm.init(3, 5, 6, 9);
}

void loop() {
  if (Serial.available()) {
    String code = Serial.readString();
    parse.parseString(code);

    arm.printSerial();
  }
}
