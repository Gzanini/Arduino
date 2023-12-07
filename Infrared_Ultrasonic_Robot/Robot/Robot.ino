#include "Wire.h"
#include "Ultrasonic.h"

int spd = 255;

int pin1, pin2, pin3, pin4;

const int sensorDireita = 8;  // pinagem do sensor infravermelho da direita
const int sensorEsquerda = 9; // pinagem do sensor infravermelho da esquerda
const int sensorContador = 11;  // pinagem do sensor infravermelho que conta os cruzamentos

Ultrasonic ultrasonic(12, 13);  //pinagens do ultrasom

bool entrou_no_if = 0;  // variavel de estado para o if do contaLinhas não ficar incrementando ate o infinito
int contaLinhas = 0;    // variavel para contar o numero de linhas horizontais que o robo ja passou



void setup()
{
  pinagemMotor1(5,6); // IN1 = pin5 ;; IN2 = pin6
  pinagemMotor2(4,3); // IN3 = pin4 ;; IN4 = pin3
  
  pinMode(sensorDireita, INPUT);  // pinagem sensor direita
  pinMode(sensorEsquerda, INPUT); // pinagem sensor esquerda
  pinMode(sensorContador, INPUT); // pinagem sensor contador de linhas

  Serial.begin(9600);
  
}

void loop()
{
  
  int right_sensor    = digitalRead(sensorDireita); // seta os dados de leitura do sensor infravermelho da direita para a variavel right_sensor
  int left_sensor     = digitalRead(sensorEsquerda);  // seta os dados de leitura do sensor infravermelho da esquerda para a variavel left_sensor
  int contador_sensor = digitalRead(sensorContador);  // seta os dados de leitura do sensor infravermelho contador de linhas para a variavel contador_sensor
  
  int distance = ultrasonic.read();     // seta os dados de leitura (distancia) do ultrassom da direita para a variavel distance
  

  // HIGH = Com linha ;; LOW = Sem Linha

  frente();   // robo anda para frente

  if((contador_sensor == HIGH) && (entrou_no_if == 0)) // se passa por cruzamento, incrementa o conta linhas
  {
    contaLinhas++;
    entrou_no_if = 1;
  }

  if((contador_sensor == LOW) && (entrou_no_if == 1)) // se nao esta em cima de um cruzamento e a variavel entrou_no_if estiver em 1, seta ela para 0
  {
    entrou_no_if = 0;
  }


  // se nao tiver nada na frente do robo ate uma distancia de 29cm ele segue
  if (distance > 29){
  

  // se o sensor infravermelho da esquerda detecta linha preta (esta mais para direita que deveria), robo vira um pouco para a esquerda
  if(right_sensor == LOW && left_sensor == HIGH)
  {
    esquerda();
  }
    // se o sensor infravermelho da direita detecta linha preta (esta mais para esquerda que deveria), robo vira um pouco para a direita
  if(right_sensor == HIGH && left_sensor == LOW)
  {
    direita();
  }

  
  if(contaLinhas == 3)  // se o robo passa pelo terceiro cruzamento, vira para a direita (em direcao ao numero 3)
  {
    delay(200);
    parar();
    delay(500);
    direita();
    delay(400);
    parar();
    delay(500);
    
    contaLinhas = 0;  // zera a variavel contadora de linhas
  }
  
  }
  else{
    parar();  // se tiver algo dentro de 29cm na frente do robo, ele fica parado
  }
  
}
 



void pinagemMotor1(int in1, int in2)
{
  pin1 = in1;
  pin2 = in2;
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
}

void pinagemMotor2(int in3, int in4)
{
  pin3 = in3;
  pin4 = in4;
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
}

void velocidade(int in1)
{
  spd = in1;
}

void frente()
{
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, HIGH);
  digitalWrite(pin4, LOW);
}

void parar()
{
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
}

void direita()
{
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, HIGH);
}

void esquerda()
{
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
  digitalWrite(pin3, HIGH);
  digitalWrite(pin4, LOW);
}
