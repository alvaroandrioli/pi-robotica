#include "RoboticArm.h"
#include <Servo.h>

RoboticArm arm;

void setup() {

  Serial.begin(9600);

  arm.addInitialState(0, 0, 0, 0);

  arm.setSpeeds(30, 30, 30);

  arm.init(3, 5, 6, 9);

  arm.addState(90, 90, 90, 90);
  arm.addState(180, 180, 180, 180);

  arm.printSerial();
}

void loop() {
    char res = Serial.read();
    if (res == 'a') {
      arm.clearActions();
    }
    if (res == 'b') {
     // arm.executeActions();
    }
}
