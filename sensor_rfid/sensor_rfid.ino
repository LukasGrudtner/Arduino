//Autor : FILIPEFLOP
 
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.
 
char st[20];
int output_led = 2;
 
void setup() 
{
  Serial.begin(9600); // Inicia a serial
  SPI.begin();    // Inicia  SPI bus
  mfrc522.PCD_Init(); // Inicia MFRC522
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println();
  //Define o número de colunas e linhas do LCD:  
  mensageminicial();

  pinMode(output_led, OUTPUT);
}
 
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Mostra UID na serial
  Serial.print("UID da tag :");
  String conteudo= "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Mensagem : ");
  conteudo.toUpperCase();
  if (conteudo.substring(1) != "BD 38 70 8B") //UID 1 - Chaveiro
  {
    digitalWrite(output_led, HIGH);
    Serial.println("Acesso liberado!");
    delay(3000);
    digitalWrite(output_led, LOW);
    mensageminicial();
  }
 
  if (conteudo.substring(1) == "ED E8 E2 2B") //UID 2 - Cartao
  {
    digitalWrite(output_led, LOW);
    Serial.println("Acesso negado!");
    delay(3000);
    mensageminicial();
  }
} 
 
void mensageminicial()
{
  Serial.println("Aproxime o seu cartão de leitor!"); 
}
