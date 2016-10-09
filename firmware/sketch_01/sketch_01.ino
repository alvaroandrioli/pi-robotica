#include <Servo.h>
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

void setup() {
  Serial.begin(9600);
  
  servo1.attach(3);
  servo2.attach(5);
  servo3.attach(6);
  servo4.attach(9);
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);
  servo_control(20, 0, 90, servo4);
  servo_control(10, 90, 180, servo4);
}

void loop() {
  
}

void servo_control(int tempo, int angulo_inicial, int angulo_final, Servo servo) {
  int direcao;

  if (angulo_inicial < angulo_final)
    direcao = 1;
  else
    direcao = -1;

  for (int pos_atual = angulo_inicial; pos_atual != angulo_final; pos_atual += direcao) {
    servo.write(pos_atual);
    delay(tempo);
  }
 
  servo.write(angulo_final);
}
