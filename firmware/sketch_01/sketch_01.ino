#include <Servo.h>
Servo servo;

void setup() {
  Serial.begin(9600);
  
  servo.attach(10);
  servo.write(145);
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
