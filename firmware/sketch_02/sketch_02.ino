#include "RoboticArm.h"
#include <Servo.h>

RoboticArm arm(3, 5, 6, 9);

void setup() {
 
  Serial.begin(9600);

  arm.addInitialState(0, 0, 0, 0);
  arm.addState(90, 0, 0, 0);

  arm.setSpeeds(10, 10, 10);

  arm.init();

  arm.executeActions();
}

void loop() {
    char res = Serial.read();
    if (res == 'a') {
      //arm.printSerial();
    } 
    if (res == 'b') {
     // arm.executeActions();
    }
}
