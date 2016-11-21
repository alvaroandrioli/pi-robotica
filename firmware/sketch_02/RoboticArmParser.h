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
        RoboticArmParse(RoboticArm *arm);

        void parseString(String code);

    private:
        void _clearAcc();

        void _addChar();

        void _getNextChar();

        void _addState();

        RoboticArm *_arm;

        String _code;

        String _acc;

        char _nextChar;

        int _pos;
};

RoboticArmParse::RoboticArmParse(RoboticArm *arm) {
    _arm = arm;
}

void RoboticArmParse::_clearAcc() {
    _acc.remove(0);
}

void RoboticArmParse::_getNextChar() {
    _pos++;
    _nextChar = _code.charAt(_pos);
}

void RoboticArmParse::_addChar() {
    _acc.concat(_nextChar);
    _getNextChar();
}

void RoboticArmParse::_addState() {
    _clearAcc();
    _getNextChar();
    while (_nextChar != 'f') {
        _addChar();
    }
    String a = _acc.substring(1,3);
    String b = _acc.substring(4,6);
    String c = _acc.substring(7,9);
    String d = _acc.substring(10,12);
    _arm->addState(a.toInt(), b.toInt(), c.toInt(), d.toInt());
}

void RoboticArmParse::parseString(String code) {
    _code = code;
    _pos = 0;
    _nextChar = code.charAt(0);
    _arm->clearActions();

    if (_nextChar != 'b')
        Serial.println("String not valid");

    while (_nextChar != 'e') {
        if (_nextChar == 's') {
            _addState();
        }

        _getNextChar();
    }
}

// b
//     s
//         a033
//         b034
//         c035
//         d000
//     f
//     s
//         a033
//         b034
//         c052
//         d001
//     f
//     s
//         a038
//         b034
//         c052
//         d001
//     f
// e

#endif