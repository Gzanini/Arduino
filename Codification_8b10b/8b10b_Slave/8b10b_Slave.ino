#include <SoftwareSerial.h>

SoftwareSerial conexao(12, 11);

String receivedChars = "";
int numOfChars = 0;

String getFirstSixChars(String str) {
  return str.substring(0, 6);
}

String getLastFourChars(String str) {
  return str.substring(str.length() - 4); 
}

char binToChar(String binaryString) {
  // Converte a string binária em um número inteiro usando base 2
  int asciiValue = strtol(binaryString.c_str(), NULL, 2);

  // Converte o número inteiro em um char em ASCII e o retorna
  return (char) asciiValue;
}

String get4b3b(String str) {
  
  if (str == "1011") {return "000";}
  if (str == "0100") {return "000";}
  if (str == "1001") {return "001";}
  if (str == "0101") {return "010";}
  if (str == "1100") {return "011";}
  if (str == "0011") {return "011";}
  if (str == "1101") {return "100";}
  if (str == "0010") {return "100";}
  if (str == "1010") {return "101";}
  if (str == "0110") {return "110";}
  if (str == "1110") {return "111";}
  if (str == "0001") {return "111";}
}

String get6b5b(String str) {
  
  if (str == "100111") {return "00000";}
  if (str == "011000") {return "00000";}
  if (str == "011101") {return "00001";}
  if (str == "100010") {return "00001";}
  if (str == "101101") {return "00010";}
  if (str == "010010") {return "00010";}
  if (str == "110001") {return "00011";}
  if (str == "110101") {return "00100";}
  if (str == "001010") {return "00100";}
  if (str == "101001") {return "00101";}
  if (str == "011001") {return "00110";}
  if (str == "111000") {return "00111";}
  if (str == "000111") {return "00111";}
  if (str == "111001") {return "01000";}
  if (str == "000110") {return "01000";}
  if (str == "100101") {return "01001";}
  if (str == "010101") {return "01010";}
  if (str == "110100") {return "01011";}
  if (str == "001101") {return "01100";}
  if (str == "101100") {return "01101";}
  if (str == "011100") {return "01110";}
  if (str == "010111") {return "01111";}
  if (str == "101000") {return "01111";}
  if (str == "011011") {return "10000";}
  if (str == "100100") {return "10000";}
  if (str == "100011") {return "10001";}
  if (str == "010011") {return "10010";}
  if (str == "110010") {return "10011";}
  if (str == "001011") {return "10100";}
  if (str == "101010") {return "10101";}
  if (str == "011010") {return "10110";}
  if (str == "111010") {return "10111";}
  if (str == "000101") {return "10111";}
  if (str == "110011") {return "11000";}
  if (str == "001100") {return "11000";}
  if (str == "100110") {return "11001";}
  if (str == "010110") {return "11010";}
  if (str == "110110") {return "11011";}
  if (str == "001001") {return "11011";}
  if (str == "001110") {return "11100";}
  if (str == "101110") {return "11101";}
  if (str == "010001") {return "11101";}
  if (str == "011110") {return "11110";}
  if (str == "100001") {return "11110";}
  if (str == "101011") {return "11111";}
  if (str == "010100") {return "11111";}
}

String get10b8b(String str) {
  String run4b3b = get4b3b(getLastFourChars(str));
  
  //Serial.print("Entrada run4b3b: ");
  //Serial.println(getLastFourChars(str));
  //Serial.print("Saida run4b3b: ");
  //Serial.println(run4b3b);
  
  String run6b5b = get6b5b(getFirstSixChars(str));
  
  //Serial.print("Entrada run6b5b: ");
  //Serial.println(getFirstSixChars(str));
  //Serial.print("Saida run6b5b: ");
  //Serial.println(run6b5b);
  
  return run4b3b + run6b5b;
}

void setup() {
  Serial.begin(9600);
  conexao.begin(9600);
}

void loop() {
  delay(10);
  if (conexao.available()) {
    char incomingChar = conexao.read();
    //Serial.println(incomingChar);
    
    if (incomingChar == '1') {receivedChars += incomingChar; numOfChars++;}
    if (incomingChar == '0') {receivedChars += incomingChar; numOfChars++;}
    
    //Serial.println(receivedChars);
    
    if (numOfChars == 10) {
        String run10b8b = get10b8b(receivedChars);
        
        char character = binToChar(run10b8b);
        Serial.print("Voce escreveu: ");
        Serial.println(character);

        // limpar para receber a próxima entrada
        receivedChars = "";
        numOfChars = 0;
    }
  }
}
