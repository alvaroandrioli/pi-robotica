#include "Arduino.h"

#ifndef Servo_h
#include <Servo.h>
#endif

#ifndef robotic_arm_h
#define robotic_arm_h

#define DEBUG 1

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

        // set debug
        void setDebug(int enable);

    private:
        // Cria um novo estado para a lista
        State* createState(int angulo_a, int angulo_b, int angulo_c, int angulo_d);

        // Controle do servo de um estado para outro com velocidade paramétrica
        void servoControler(int timeP, int angulo_inicial, int angulo_final, Servo servo);

        void printSerialState(int a, int b, int c, int d);

        // Inicio
        State *_head;

        // Fim
        State *_tail;

        // Estado atual do braço
        State *_atual;

        // Estado inicial do braço
        State *_initial;

        // debug
        int _debug;

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
    //pinMode(pin_a, OUTPUT);
    // pinMode(pin_b, OUTPUT);
    // pinMode(pin_c, OUTPUT);
    // pinMode(pin_d, OUTPUT);

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

    #ifdef DEBUG
        Serial.print("RoboticArm::addState ");
        Serial.print(" New State ");
        printSerialState(newState->angulo_a, newState->angulo_b, newState->angulo_c, newState->angulo_d);
    #endif

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
    _atual = _initial;
    State *prox = _head;

    Serial.print("Speed a -> ");
    Serial.print(_speed_a);
    Serial.print(" Speed b -> ");
    Serial.print(_speed_b);
    Serial.print(" Speed c -> ");
    Serial.println(_speed_c);

    while (prox != NULL) {
        Serial.print("ATUAL ");
        printSerialState(_atual->angulo_a, _atual->angulo_b, _atual->angulo_c, _atual->angulo_d);

        Serial.print("PROXIMO ");
        printSerialState(prox->angulo_a, prox->angulo_b, prox->angulo_c, prox->angulo_d);

        _atual = prox;
        prox = _atual->next;

        Serial.println("TRANSICAO");
    }

    prox = _initial;

    Serial.print("ATUAL ");
    printSerialState(_atual->angulo_a, _atual->angulo_b, _atual->angulo_c, _atual->angulo_d);

    Serial.print("PROXIMO ");
    printSerialState(prox->angulo_a, prox->angulo_b, prox->angulo_c, prox->angulo_d);


    _atual = _initial;
    Serial.println("TRANSICAO");

    Serial.print("ATUAL ");
    printSerialState(_atual->angulo_a, _atual->angulo_b, _atual->angulo_c, _atual->angulo_d);
}

void RoboticArm::servoControler(int timeP, int angulo_inicial, int angulo_final, Servo servo) {
    int direcao;

    if (angulo_inicial < angulo_final)
        direcao = 1;
    else
        direcao = -1;

    #ifdef DEBUG
        Serial.println();
        Serial.print("RoboticArm::servoControler ");
        Serial.print("INICIAL-> ");
        Serial.print(angulo_inicial);
        Serial.print(" FINAL-> ");
        Serial.print(angulo_final);
        Serial.print(" DIRECAO-> ");
        Serial.println(direcao);
    #endif

    for (int pos_atual = angulo_inicial; pos_atual != angulo_final; pos_atual += direcao) {
        #ifdef DEBUG
            Serial.print(" ");
            Serial.print(pos_atual);
        #endif
        servo.write(pos_atual);
        delay(timeP);
    }

    servo.write(angulo_final);

    #ifdef DEBUG
        Serial.print(" ");
        Serial.println(angulo_final);
    #endif
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
    #ifdef DEBUG
        Serial.print("RoboticArm::init");
        Serial.print(" Go to initial state ");
        printSerialState(_initial->angulo_a, _initial->angulo_b, _initial->angulo_c, _initial->angulo_d);
    #endif
    
    _servo_a.write(_initial->angulo_a);
    _servo_b.write(_initial->angulo_b);
    _servo_c.write(_initial->angulo_c);
    _servo_d.write(_initial->angulo_d);
}

void RoboticArm::setSpeeds(int speed_a, int speed_b, int speed_c) {
    #ifdef DEBUG
        Serial.print("RoboticArm::setSpeeds ");
        Serial.print("SET SPEED ");
        printSerialState(speed_a, speed_b, speed_c, 0);
    #endif
    _speed_a = speed_a;
    _speed_b = speed_b;
    _speed_c = speed_c;
}

void RoboticArm::printSerialState(int a, int b, int c, int d) {
    Serial.print(" a ->");
    Serial.print(a);
    Serial.print(" b ->");
    Serial.print(b);
    Serial.print(" c ->");
    Serial.print(c);
    Serial.print(" d ->");
    Serial.println(d);
}

#endif
