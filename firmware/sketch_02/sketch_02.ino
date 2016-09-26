#include "RoboticArm.h"

RoboticArm arm(8, 9, 10, 11);

void setup() {
  Serial.begin(9600);
  
  arm.addInitialState(0, 0, 0, 0);

  arm.addState(50, 60, 70, 80);
  arm.addState(80, 70, 60, 50);
  arm.addState(100, 100, 100, 100);

  arm.init();
}

void loop() {
  if (Serial.read() == 'a')
    arm.printSerial();
}
