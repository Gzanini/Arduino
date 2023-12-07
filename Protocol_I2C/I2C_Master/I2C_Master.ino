//Declaração de bibliotecas

#include <Wire.h>

//Endereco do dispositivo
const int SLAVE_ADDR1 = 5;
//Pino do botoo
const int PINO_BUTTON1 = 2;
//Mensagem pressionado
const char BTN_PRESSIONADO = 'H';
//Mensagem liberado
const char BTN_LIBERADO = 'L';
//Estado dos botoes
int estado_btn1 = 0;
bool pressed1 = false;

void setup(){
  //Inicializa o barramento I2C mestre
  Wire.begin();
  Serial.begin(9600);
  //Define o pino
pinMode(PINO_BUTTON1,INPUT_PULLUP);
}

void loop()
{
//Leitura do botao
  estado_btn1 = digitalRead(PINO_BUTTON1);
  if ((estado_btn1 == LOW) && (!pressed1))
  {
      //Inicia a transmissão slave
      Wire.beginTransmission(SLAVE_ADDR1);
    Serial.println("Slave:");
    Serial.println(SLAVE_ADDR1); //5
    //Envia a informacao do botao
      Wire.write(BTN_PRESSIONADO);
    Serial.println("BTN_PRESSIONADO:");
    Serial.println(BTN_PRESSIONADO); //H
    //Finaliza a transmissão
      Wire.endTransmission();
    //Atualiza o estado do botão
      pressed1 = true;
  }
  else if ((estado_btn1 == HIGH) && pressed1)
  {
      //Inicia a transmissao para o slave
      Wire.beginTransmission(SLAVE_ADDR1);
    Serial.println("SLAVE_ADDR1:");
    Serial.println(SLAVE_ADDR1); //5
    //Envia a informação do botao
      Wire.write(BTN_LIBERADO);
    Serial.println("BTN_LIBERADO:");
    Serial.println(BTN_LIBERADO);
    //Finaliza a transmissão
      Wire.endTransmission();
    //Atualiza o estado do botão
      pressed1 = false;
  }
  delay(50);
}
