#define BTN1 0  //liga motor A / Desliga motor A
#define BTN2 1  //Inverte motor A / Inverte Motor A
#define BTN3 2  //Aumenta velocidade do motor A
#define BTN4 3  //Diminui velocidade do motor A
#define BTN5 4  //Liga motor B / Desliga Motor B
#define BTN6 5  //Inverte motor B / Inverte motor B
#define BTN7 6  //Aumenta velocidade motor B
#define BTN8 7  //Diminui velocidade motor B
#define BTN9 8  //Emergencia - desliga os dois motores

#define INPUT_A1 3
#define INPUT_A2 5

#define INPUT_B1 9
#define INPUT_B2 10


//matriz para guardar estado dos botoes
bool state_btn[8] = {1, 1, 1, 1, 1, 1, 1, 1};
bool last_state[8] = {1, 1, 1, 1, 1, 1, 1, 1};


//Matriz com os pinos referentes aos botões
//Segue a ordem BTN1, BTN2, ... , BTN9;
int pins_btn[8] = {19, 18, 17, 16, 15, 14, 11, 12};




//Struct para guardar as informaçoes de cada motor
struct motores {

  bool state;
  char dir;
  int vel;
};

//Cria uma struct para cada motor
motores motor_a = {0, 'e', 20};
motores motor_b = {0, 'e', 20};


void setup() {
  // configura todos os pinos de entrada usando um loop
  for (int i = 0; i < 8; i++) {
    pinMode(pins_btn[i], INPUT_PULLUP);
  } 

  //Associa uma interrupção ao BTN9
  //Configura a interrupção para borda de descida
  attachInterrupt(digitalPinToInterrupt(BTN9), emergencia, FALLING);

  //Configura as saidas analogicas
  pinMode(INPUT_A1, OUTPUT);
  pinMode(INPUT_A2, OUTPUT);
  pinMode(INPUT_B1, OUTPUT);
  pinMode(INPUT_B2, OUTPUT);

}

void loop() {
  //Escaneia todas os botoes utilizando um loop
  for (int i = 0; i < 8; i++) {
    state_btn[i] = digitalRead(pins_btn[i]);
  }

  //liga o motor A
  //utiliza como referencia o ultimo estado pra criar um detector de
  //borda de decidaa, o mesmo conceito é utilizado para todos os outros botoes
  //Para as demais funções, necessita que o estado do motor seja ligado (1)
  if (last_state[BTN1] == 1 && state_btn[BTN1] == 0) {

    //liga ou desliga o motor dependendo do estado atual
    if (motor_a.state == 1) {
      //desliga
      digitalWrite(INPUT_A1, 0);
      digitalWrite(INPUT_A2, 0);
      motor_a.state = 0;
    } else {
      //liga com a velocidade minima
      //Verifica a direção do motor para acionar o PWM correto
      motor_a.state = 1;
      if (motor_a.dir == 'e') {

        digitalWrite(INPUT_A1, 0);
        analogWrite(INPUT_A2, motor_a.vel);
      } else {

        digitalWrite(INPUT_A1, motor_a.vel);
        analogWrite(INPUT_A2, 1);
      }
    }
  }

  //Inverte a rotação do motor
  if (last_state[BTN2] == 1 && state_btn[BTN2] == 0 && motor_a.state == 1) {

    //inverte o sentido de rotação dos motores
    if (motor_a.dir == 'd') {
      digitalWrite(INPUT_A1, 0);
      analogWrite(INPUT_A2, motor_a.dir);
      motor_a.dir = 'e';
    } else {
      analogWrite(INPUT_A1, motor_a.dir);
      digitalWrite(INPUT_A2, 0);
      motor_a.dir = 'd';

    }
  }

  //Aumenta velocidade do motor
  if (last_state[BTN3] == 1 && state_btn[BTN3] == 0 && motor_a.state == 1) {

    motor_a.vel += 10;
    //Verifica se a velocidade é maior que 255
    if (motor_a.vel > 255)
      motor_a.vel = 255;

    if (motor_a.dir == 'e') {
      digitalWrite(INPUT_A1, 0);
      analogWrite(INPUT_A2, motor_a.vel);
    } else {
      analogWrite(INPUT_A1, motor_a.vel);
      digitalWrite(INPUT_A2, 0);
    }

  }

  //Diminui a velocidade do motor
  if (last_state[BTN4] == 1 && state_btn[BTN4] == 0 && motor_a.state == 1) {

    motor_a.vel -= 10;
    //Verifica se a velocidade é menor que 20
    if (motor_a.vel < 20)
      motor_a.vel = 255;

    if (motor_a.dir == 'e') {
      digitalWrite(INPUT_A1, 0);
      analogWrite(INPUT_A2, motor_a.vel);
    } else {
      analogWrite(INPUT_A1, motor_a.vel);
      digitalWrite(INPUT_A2, 0);
    }

  }

  //Liga o motor
  if (last_state[BTN5] == 1 && state_btn[BTN5] == 0) {

    //liga ou desliga o motor dependendo do estado atual
    if (motor_b.state == 1) {
      //desliga
      digitalWrite(INPUT_B1, 0);
      digitalWrite(INPUT_B2, 0);
      motor_b.state = 0;
    } else {
      //liga com a velocidade minima
      //Verifica a direção do motor para acionar o PWM correto
      motor_b.state = 1;
      if (motor_b.dir == 'e') {

        digitalWrite(INPUT_B1, 0);
        analogWrite(INPUT_B2, motor_b.vel);
      } else {

        digitalWrite(INPUT_B1, motor_b.vel);
        analogWrite(INPUT_B2, 1);
      }
    }
  }

  //Inverte a rotação do motor
  if (last_state[BTN6] == 1 && state_btn[BTN6] == 0 && motor_b.state == 1) {

    //inverte o sentido de rotação dos motores
    if (motor_b.dir == 'd') {
      digitalWrite(INPUT_B1, 0);
      analogWrite(INPUT_B2, motor_b.dir);
      motor_b.dir = 'e';
    } else {
      analogWrite(INPUT_B1, motor_b.dir);
      digitalWrite(INPUT_B2, 0);
      motor_b.dir = 'd';

    }
  }

  //Aumenta velocidade do motor
  if (last_state[BTN7] == 1 && state_btn[BTN7] == 0 && motor_b.state == 1) {

    motor_b.vel += 10;
    //Verifica se a velocidade é maior que 255
    if (motor_b.vel > 255)
      motor_b.vel = 255;

    if (motor_b.dir == 'e') {
      digitalWrite(INPUT_B1, 0);
      analogWrite(INPUT_B2, motor_b.vel);
    } else {
      analogWrite(INPUT_B1, motor_b.vel);
      digitalWrite(INPUT_B2, 0);
    }

  }

  //Diminui a velocidade do motor
  if (last_state[BTN8] == 1 && state_btn[BTN8] == 0 && motor_b.state == 1) {

    motor_b.vel -= 10;
    //Verifica se a velocidade é menor que 20
    if (motor_b.vel < 20)
      motor_b.vel = 255;

    if (motor_b.dir == 'e') {
      digitalWrite(INPUT_B1, 0);
      analogWrite(INPUT_B2, motor_b.vel);
    } else {
      analogWrite(INPUT_B1, motor_b.vel);
      digitalWrite(INPUT_B2, 0);
    }

  }

  //Atualiza a matriz last_state
  for (int i=0; i < 8; i++){
    last_state[i] = state_btn[i];
  }
}
//Função de emergencia executada na interrupção
void emergencia(void){
  //Para os dois motores ao mesmo tempo

  //Para o motor A
      digitalWrite(INPUT_A1, 0);
      digitalWrite(INPUT_A2, 0);
  
  //Para o motor B
      digitalWrite(INPUT_B1, 0);
      digitalWrite(INPUT_B2, 0);
  
}