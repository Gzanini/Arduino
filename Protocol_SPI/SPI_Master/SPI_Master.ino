/*Exemplo de envio de dados via SPI*/

// Bibliotecas
// Pinagem
#define  tx_data 11  //MOSI
#define sclk  10  //SCLK
#define selecao 9 //Chip Select
#define botao 4 //Botão

// Constantes e Objetos
#define  tx_rate_bps   9600 //bits por segundo
// Protótipo das Funções
void send_data(char *mensagem);
// Variáveis Globais
 char *mensagem = "D";
 int bot_estado;
 
// Configurações Iniciais
void setup()
{
  pinMode(botao, INPUT_PULLUP);
  pinMode(tx_data, OUTPUT);
  pinMode(sclk, OUTPUT);
  pinMode(selecao,  OUTPUT);
  digitalWrite(selecao, HIGH);
  Serial.begin(9600);
  Serial.println("Mensagem transmitida via SPI");
}

// Função principal
void loop()
{
  bot_estado = digitalRead(botao);
  if (!bot_estado && mensagem == "D")
  {
    mensagem = "L";
    send_data(mensagem);
  }
  if (bot_estado)
  {
    mensagem = "D";
  } 
  delay(50);
}

// Função de envio de dados via SPI
void send_data(char *mensagem)
{
    //A variável local tx_byte irá armazenar cada byte da mensagem a ser enviada
      char tx_byte = mensagem[0];
      //Imprime na serial
      Serial.print(tx_byte);
 Serial.print( "->");
      //Loop para enviar cada bit de um byte
      for(int j=0; j<8; j++)
      {
        //A variável auxiliar tx_bit será o resultado d operação AND entre o caracter E 0x80 (1000 0000) deslocado para a direito j bits
          bool tx_bit = tx_byte & (0x80 >> j);
          // Habilita o slave
          digitalWrite(selecao, LOW);
          //Escreve o valor do bit a ser transmitido no referido pino MOSI
          digitalWrite(tx_data,tx_bit);
          //Imprime o bit transmitido na Serial
          Serial.print(tx_bit);
          //Aguarda metade por metade do tempo necessário para transmitir cada bit
          delay((1000/tx_rate_bps) / 2);
          //Gera uma borda de subida de clock
          digitalWrite(sclk, HIGH);
          //Aguarda metade por metade do tempo necessário para transmitir cada bit
          delay((1000/tx_rate_bps) / 2);
          //Gera uma borda de descida de clock
          digitalWrite(sclk, LOW);
      }
      Serial.println("");
  //Escreve 0 no MOSI
  digitalWrite(tx_data, LOW);
  //Desabilita o slave após o término da transmissão
  digitalWrite(selecao, HIGH);
} 
