/*Exemplo de envio de dados via SPI*/

// Pinagem
#define  rx_data 11  //MISO
#define sclk  10  //SCLK
#define selecao 9 //Chip Select
#define led   2 //Led

// Protótipo das Funções
void recebe_data();
int estado;

// Configurações Iniciais
void setup()
{
  pinMode(led, OUTPUT);
  pinMode(rx_data, INPUT);
  pinMode(sclk, INPUT);
  pinMode(selecao,  INPUT);
  Serial.begin(9600);
  Serial.println("Mensagem transmitida via SPI");
}

// Função principal
void loop()
{
  if (!digitalRead(selecao))
  {
    recebe_data();
  }
}
// Função de recebimento de dados via SPI
void recebe_data()
{
    bool rx_bit, dado;
    int teste=0, j=0;
    char *mensagem = "L";
    char tx_byte;
    tx_byte = mensagem[0];
    Serial.print(tx_byte);
    Serial.print(" -> ");
    while(!digitalRead(selecao))
    {
          rx_bit = digitalRead(rx_data);
          dado = tx_byte & (0x80 >> j);
          if (rx_bit == dado && j<8)
            {
                Serial.print(rx_bit);
                j++;
              if (j==8)
              {
                estado = !digitalRead(led);
          digitalWrite(led, estado); 
              }
            }
    }
    Serial.println("");
}
