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

        // adiciona o estado inicial
        void addInitialState(int angulo_a, int angulo_b, int angulo_c, int angulo_d);

        // Adiciona a velocidade dos servos
        void setSpeeds(int speed_a, int speed_b, int speed_c);

        // Coloca o braço no estado inicial
        void init();

        // printa a lista na serial
        void printSerial();

        // executa cada estado da lista
        void executeActions();

    private:
        // Cria um novo estado para a lista
        State* createState(int angulo_a, int angulo_b, int angulo_c, int angulo_d);

        // Controle do servo de um estado para outro com velocidade paramétrica
        void servoControler(int timeP, int angulo_inicial, int angulo_final, Servo servo);

        // Inicio
        State *_head;

        // Fim
        State *_tail;

        // Estado atual do braço
        State *_atual;

        // Estado inicial do braço
        State *_initial;

        // Tamanho da lista
        int _size;

        // Servos
        Servo _servo_a;  //base
        Servo _servo_b;
        Servo _servo_c;
        Servo _servo_d;  //pinsa

        int _speed_a = 30;
        int _speed_b = 30;
        int _speed_c = 30;
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
    _atual = NULL;
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
    State *state;

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

void RoboticArm::servoControler(int timeP, int angulo_inicial, int angulo_final, Servo servo) {
    int direcao;

    if (angulo_inicial < angulo_final)
        direcao = 1;
    else
        direcao = -1;

    for (int pos_atual = angulo_inicial; pos_atual != angulo_final; pos_atual += direcao) {
        servo.write(pos_atual);
        delay(timeP);
    }

    servo.write(angulo_final);
}

void RoboticArm::addInitialState(int angulo_a, int angulo_b, int angulo_c, int angulo_d) {
    _initial = createState(angulo_a, angulo_b, angulo_c, angulo_d);
}

void RoboticArm::executeActions() {
    _atual = _initial;
    State *prox = _head;

    while (prox != NULL) {
        servoControler(_speed_a, _atual->angulo_a, prox->angulo_a, _servo_a);
        servoControler(_speed_b, _atual->angulo_b, prox->angulo_b, _servo_b);
        servoControler(_speed_c, _atual->angulo_c, prox->angulo_c, _servo_c);
        servoControler(0, _atual->angulo_d, prox->angulo_d, _servo_d);
        
        _atual = prox;
        prox = _atual->next;
    }

    prox = _initial;

    servoControler(_speed_a, _atual->angulo_a, prox->angulo_a, _servo_a);
    servoControler(_speed_b, _atual->angulo_b, prox->angulo_b, _servo_b);
    servoControler(_speed_c, _atual->angulo_c, prox->angulo_c, _servo_c);
    servoControler(0, _atual->angulo_d, prox->angulo_d, _servo_d);

    _atual = _initial;
}

void RoboticArm::init() {
    _servo_a.write(_initial->angulo_a);
    _servo_b.write(_initial->angulo_b);
    _servo_c.write(_initial->angulo_c);
    _servo_d.write(_initial->angulo_d);
}

void RoboticArm::setSpeeds(int speed_a, int speed_b, int speed_c) {
    _speed_a = speed_a;
    _speed_b = speed_b;
    _speed_c = speed_c;
}

#endif
