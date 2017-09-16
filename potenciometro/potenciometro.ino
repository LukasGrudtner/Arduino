//Sensor de luz com LDR

#define potPin 5
#define ledPin 4

#include <LCD5110_Basic.h>

LCD5110 tela(8,9,10,12,11);
/*Cria objeto da classe LCD5110
CLK – Pino 8
DIN – Pino 9
DC – Pino 10
RST – Pino 12
CE – Pino 11
*/

//Obtendo as fontes
extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];

int ldrPin = 0; //LDR no pino analógico 0
int ldrValor = 0; //Valor lido do LDR
int valPot = 0;
 
void setup() {
  tela.InitLCD(); //Inicializando o display
  pinMode(ledPin, OUTPUT);
 Serial.begin(9600); //Inicia a comunicação serial
}
 
void loop() {
  valPot = analogRead(potPin);
  valPot = map(valPot, 0, 1023, 0, 255); //Utilizando a função map() para transformar uma escala de 0-1023 em uma escala 0 a 255
  analogWrite(ledPin, valPot); // Aciona o LED proporcionalmente ao valor da leitura analógica
  
 ///ler o valor do LDR
 ldrValor = analogRead(ldrPin); //O valor lido será entre 0 e 1023
 tela.setFont(SmallFont);
 tela.print("LUMINOSIDADE", CENTER, 0);
 
 tela.setFont(BigNumbers);
 tela.printNumI(ldrValor, CENTER, 20);
 delay(1000);
 tela.clrScr();
 
// //se o valor lido for maior que 500, liga o led
// if (ldrValor>= 800) digitalWrite(ledPin,HIGH);
// // senão, apaga o led
// else digitalWrite(ledPin,LOW);
 
 //imprime o valor lido do LDR no monitor serial
 Serial.println(ldrValor);
 delay(100);
}
