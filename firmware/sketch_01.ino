typedef struct node {
  int servo_a;
  int servo_b;
  int servo_c;
  int servo_d;
  
  struct node *next;
} Node;

typedef struct list {
  int quant;
  Node *head;
} List;

List* createList() {
  List *list = new List;
  list->head = NULL;
  list->quant = 0;
}

Node* createState(int servo_a, int servo_b, int servo_c, int servo_d) {
  Node *node = new Node;
  
  node->servo_a = servo_a;
  node->servo_b = servo_b;
  node->servo_c = servo_c;
  node->servo_d = servo_d;
  
  node->next = NULL;
  return node;
}

void push(List *list, Node *state) {
  if (list->quant != 0)
    state->next = list->head;
  
  list->quant += 1;
  list->head = state;
}

void printSerialList(List *stateList) {
  Node *state = NULL;

  for (state = stateList->head; state->next != NULL; state = state->next) {
    Serial.print("a -> ");
    Serial.print(state->servo_a);
    Serial.print(" b -> ");
    Serial.print(state->servo_b);
    Serial.print(" c -> ");
    Serial.print(state->servo_c);
    Serial.print(" d -> ");
    Serial.print(state->servo_d);
    Serial.println();
  }
  
  Serial.print("a -> ");
  Serial.print(state->servo_a);
  Serial.print(" b -> ");
  Serial.print(state->servo_b);
  Serial.print(" c -> ");
  Serial.print(state->servo_c);
  Serial.print(" d -> ");
  Serial.print(state->servo_d);
  Serial.println();
}

void goToState(Node *initialState, Node *finalState) {
  //fazer algo aqui 
}

void servo_control(int tempo, int angulo_inicial, int angulo_final) {
  int direcao;

  if (angulo_inicial < angulo_final)
    direcao = 1;
  else
    direcao = -1;

  for (int pos_atual = angulo_inicial; pos_atual != angulo_final; pos_atual += direcao) {
    //servo.write(pos_atual);
    delay(tempo);
  }
 
  //servo.write(angulo_final);
}

List *stateList = createList();

void setup() {
  Serial.begin(9600);
  
  push(stateList, createState(0, 10, 20, 30));
  push(stateList, createState(40, 50, 60, 70));
  push(stateList, createState(80, 55, 65, 70));

}

void loop() {
  if (Serial.read() == 'a')
    printSerialList(stateList);
}
