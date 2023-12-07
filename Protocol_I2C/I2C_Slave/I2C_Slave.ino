//Declaração da biblioteca
#include <Wire.h>

//Pino LED
int LED = 7;

void setup() {
  Serial.begin(9600);
  //Inicializa o barramento I2C escravo
  Wire.begin(5);
  //Funcao
  Wire.onReceive(RecebeMsg);
  //Define o pino
  pinMode(LED, OUTPUT);
  //Desliga LED do slave
  digitalWrite(LED, LOW);
}
void loop() {
}
void RecebeMsg(int howMany){
  while(Wire.available()){
    //Le mensagem
    char c = Wire.read();
    Serial.println("Wire.read c");
    Serial.println(c);
    if( c == 'H' ){
      //Liga LED
      digitalWrite(LED,HIGH);
    } else if ( c == 'L' ){
      //Desliga LED
      digitalWrite(LED,LOW);
    }
  }
}  
