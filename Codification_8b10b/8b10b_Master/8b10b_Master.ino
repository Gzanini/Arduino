#include <SoftwareSerial.h>

int refPrincipal = 0;
SoftwareSerial conexao(11, 12);

String getFirstThreeChars(String str) {
  return str.substring(0, 3);
}

String getLastFiveChars(String str) {
  return str.substring(str.length() - 5); 
}

String getReferencia(int ref) {
  if (ref > 0) { 
        return "positivo";
    } 
    else if (ref < 0) {
        return "negativo";
    }
    else {
        return "positivo";
    }
}

String get3b4b(String str, int ref) {
  String referencia = getReferencia(ref);
  
  if (str == "000" && referencia == "negativo") {return "1011";}
  if (str == "000" && referencia == "positivo") {return "0100";}
  if (str == "001") {return "1001";}
  if (str == "010") {return "0101";}
  if (str == "011" && referencia == "negativo") {return "1100";}
  if (str == "011" && referencia == "positivo") {return "0011";}
  if (str == "100" && referencia == "negativo") {return "1101";}
  if (str == "100" && referencia == "positivo") {return "0010";}
  if (str == "101") {return "1010";}
  if (str == "110") {return "0110";}
  if (str == "111" && referencia == "negativo") {return "1110";}
  if (str == "111" && referencia == "positivo") {return "0001";}
}

String get5b6b(String str, int ref) {
  String referencia = getReferencia(ref);
  
  if (str == "00000" && referencia == "negativo") {return "100111";}
  if (str == "00000" && referencia == "positivo") {return "011000";}
  if (str == "00001" && referencia == "negativo") {return "011101";}
  if (str == "00001" && referencia == "positivo") {return "100010";}
  if (str == "00010" && referencia == "negativo") {return "101101";}
  if (str == "00010" && referencia == "positivo") {return "010010";}
  if (str == "00011") {return "110001";}
  if (str == "00100" && referencia == "negativo") {return "110101";}
  if (str == "00100" && referencia == "positivo") {return "001010";}
  if (str == "00101") {return "101001";}
  if (str == "00110") {return "011001";}
  if (str == "00111" && referencia == "negativo") {return "111000";}
  if (str == "00111" && referencia == "positivo") {return "000111";}
  if (str == "01000" && referencia == "negativo") {return "111001";}
  if (str == "01000" && referencia == "positivo") {return "000110";}
  if (str == "01001") {return "100101";}
  if (str == "01010") {return "010101";}
  if (str == "01011") {return "110100";}
  if (str == "01100") {return "001101";}
  if (str == "01101") {return "101100";}
  if (str == "01110") {return "011100";}
  if (str == "01111" && referencia == "negativo") {return "010111";}
  if (str == "01111" && referencia == "positivo") {return "101000";}
  if (str == "10000" && referencia == "negativo") {return "011011";}
  if (str == "10000" && referencia == "positivo") {return "100100";}
  if (str == "10001") {return "100011";}
  if (str == "10010") {return "010011";}
  if (str == "10011") {return "110010";}
  if (str == "10100") {return "001011";}
  if (str == "10101") {return "101010";}
  if (str == "10110") {return "011010";}
  if (str == "10111" && referencia == "negativo") {return "111010";}
  if (str == "10111" && referencia == "positivo") {return "000101";}
  if (str == "11000" && referencia == "negativo") {return "110011";}
  if (str == "11000" && referencia == "positivo") {return "001100";}
  if (str == "11001") {return "100110";}
  if (str == "11010") {return "010110";}
  if (str == "11011" && referencia == "negativo") {return "110110";}
  if (str == "11011" && referencia == "positivo") {return "001001";}
  if (str == "11100") {return "001110";}
  if (str == "11101" && referencia == "negativo") {return "101110";}
  if (str == "11101" && referencia == "positivo") {return "010001";}
  if (str == "11110" && referencia == "negativo") {return "011110";}
  if (str == "11110" && referencia == "positivo") {return "100001";}
  if (str == "11111" && referencia == "negativo") {return "101011";}
  if (str == "11111" && referencia == "positivo") {return "010100";}
}

int sumRef(String str, int ref) {
  int contaUm = 0;
  int contaZero = 0;

  for (unsigned int i = 0; i < str.length(); i++) {
    if (str.charAt(i) == '1') {
      contaUm++;
    } else if (str.charAt(i) == '0') {
      contaZero++;
    }
  }

  return (ref + (contaUm - contaZero));
}

String get8b10b(String str) {
  //Serial.print("Ref inicial: ");
  //Serial.println(refPrincipal);
  
  String run3b4b = get3b4b(getFirstThreeChars(str),refPrincipal);
  refPrincipal = sumRef(run3b4b,refPrincipal);
  
  //Serial.print("Entrada run3b4b: ");
  //Serial.println(getFirstThreeChars(str));
  //Serial.print("Saida run3b4b: ");
  //Serial.println(run3b4b);
  //Serial.print("Referencial pos run3b4b: ");
  //Serial.println(refPrincipal);
  
  String run5b6b = get5b6b(getLastFiveChars(str),refPrincipal);
  refPrincipal = sumRef(run5b6b,refPrincipal);
  
  //Serial.print("Entrada run5b6b: ");
  //Serial.println(getLastFiveChars(str));
  //Serial.print("Saida run5b6b: ");
  //Serial.println(run5b6b);
  //Serial.print("Referencial pos run5b6b: ");
  //Serial.println(refPrincipal);
  
  return run5b6b + run3b4b;
}

void setup() {
  Serial.begin(9600); 
  conexao.begin(9600);
}

void loop() {
  if (Serial.available()) {
    char receivedChar = Serial.read();
    String binString = "";
    
    // Converte o valor do caractere para binário e adiciona na binString.
    for (int i = 7; i >= 0; i--) {
      binString += ((receivedChar >> i) & 1) ? "1" : "0";
    }
     
  //Serial.println("----------------------------------------");
  //Serial.print("Entrada Serial: ");
  //Serial.println(receivedChar);
  //Serial.print("Converte entrada 8b: ");
  //Serial.println(binString);

  String run8b10b = get8b10b(binString);
  //Serial.print("Saida completa 8b10b: ");
  //Serial.println(run8b10b);
    
    for (int i = 0; i < run8b10b.length(); i++) {
      conexao.write(run8b10b[i]);
      delay(10);
    }
    
    Serial.print("Voce escreveu: ");
  Serial.println(receivedChar);
  }
}
