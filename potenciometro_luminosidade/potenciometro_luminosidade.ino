#define potPin 5   // Define o pino analógico em que o potenciômetro vai ser conectado
#define ledPin 7   // Define o pino que terá um LED e um resistência ligada ao terra

int valPot = 0; //Variável que armazena o valor da leitura do potenciômetro

void setup() {

pinMode(ledPin,OUTPUT); // Configura o pino do LED como saída
Serial.begin(9600); //Inicia a comunicação serial
}

void loop() {   

valPot =  analogRead(potPin); //Faz a leitura analógica do pino em que o potenciômetro esta ligado
valPot = map(valPot,0,1023,0,255); //Utilizando a função map() para transformar uma escala de 0-1023 em uma escala 0 a 255
analogWrite(ledPin,valPot ); // Aciona o LED proporcionalmente ao valor da leitura analógica

Serial.println(valPot);
} 
