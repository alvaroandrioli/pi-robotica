#include "RoboticArm.h"
#include <Servo.h>

RoboticArm arm;

void setup() {
 
  Serial.begin(9600);

  arm.addInitialState(180, 90, 0, 0);

  arm.setSpeeds(10, 20, 10);

  arm.init(3, 5, 6, 9);
  
  arm.addState(90, 180, 0, 0);
  arm.addState(70, 70, 0, 0);
 
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
