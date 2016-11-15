#include "Arduino.h"

#ifndef Servo_h
#include <Servo.h>
#endif

#ifndef robotic_arm_h
#include "RoboticArm.h"
#endif

#ifndef robotic_arm_parse_h
#define robotic_arm_parse_h

//#define DEBUG 1

class RoboticArmParse {
    public:
        RoboticArmParse(RoboticArm arm);

    private:
        RoboticArm _arm;
};

RoboticArmParse::RoboticArmParse(RoboticArm arm) {
    _arm = arm;
}

#endif
