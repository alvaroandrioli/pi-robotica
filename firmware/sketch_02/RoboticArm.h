#include "Arduino.h"

#ifndef Servo_h
#include <Servo.h>
#endif

#ifndef robotic_arm_h
#define robotic_arm_h

typedef struct node {
    int angulo_a;
    int angulo_b;
    int angulo_c;
    int angulo_d;
    struct node *next;
} State;

class RoboticArm {
    public:
        // construtor
        RoboticArm(int pin_a, int pin_b, int pin_c, int pin_d);

        // adiciona um estado para a lista
        void addState(int angulo_a, int angulo_b, int angulo_c, int angulo_d);

        void printSerial();

    private:
        // Cria um novo estado para a lista
        State* createState(int angulo_a, int angulo_b, int angulo_c, int angulo_d);

        // Inicio
        State *_head;

        // Fim
        State *_tail;

        // Tamanho da lista
        int _size;

        // Servos
        Servo _servo_a;  //base
        Servo _servo_b;
        Servo _servo_c;
        Servo _servo_d;  //pinsa
};

RoboticArm::RoboticArm(int pin_a, int pin_b, int pin_c, int pin_d) {
    // iniciando pinos como saída
    pinMode(pin_a, OUTPUT);
    pinMode(pin_b, OUTPUT);
    pinMode(pin_c, OUTPUT);
    pinMode(pin_d, OUTPUT);

    // adicionando os pinos nos servos
    _servo_a.attach(pin_a);
    _servo_b.attach(pin_b);
    _servo_c.attach(pin_c);
    _servo_d.attach(pin_d);

    // criando e inicializando a lista
    _head = NULL;
    _tail = NULL;
    _size = 0;
}

void RoboticArm::addState(int angulo_a, int angulo_b, int angulo_c, int angulo_d) {
    State *newState = createState(angulo_a, angulo_b, angulo_c, angulo_d);

    if (_size == 0) {
        _head = newState;
    } else {
        _tail->next = newState;
    }

    _size++;
    _tail = newState;
}

State* RoboticArm::createState(int angulo_a, int angulo_b, int angulo_c, int angulo_d) {
    State *newState = new State;

    newState->angulo_a = angulo_a;
    newState->angulo_b = angulo_b;
    newState->angulo_c = angulo_c;
    newState->angulo_d = angulo_d;

    newState->next = NULL;

    return newState;
}

void RoboticArm::printSerial() {
    newState *state;

    for (state = _head; state->next != NULL; state = state->next) {
        Serial.print("a -> ");
        Serial.print(state->angulo_a);
        Serial.print(" b -> ");
        Serial.print(state->angulo_b);
        Serial.print(" c -> ");
        Serial.print(state->angulo_c);
        Serial.print(" d -> ");
        Serial.print(state->angulo_d);
        Serial.println();
    }

    Serial.print("a -> ");
    Serial.print(state->angulo_a);
    Serial.print(" b -> ");
    Serial.print(state->angulo_b);
    Serial.print(" c -> ");
    Serial.print(state->angulo_c);
    Serial.print(" d -> ");
    Serial.print(state->angulo_d);
    Serial.println();
}

#endif
