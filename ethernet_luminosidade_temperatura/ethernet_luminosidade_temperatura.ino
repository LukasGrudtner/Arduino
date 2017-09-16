#include <SPI.h>
#include <Ethernet.h>
#include <Adafruit_BMP085.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(150, 162, 63, 157); // Endereço IP que a Ethernet Shield terá. Deve ser alterado para um endereço livre da sua rede.
EthernetServer server(80);     // Cria um servidor WEB
Adafruit_BMP085 bmp180;

int ldrPin = 0; //LDR no pino analógico 0
int ldrValor = 0; //Valor lido do LDR
int mostrador = 0;

void setup() {
    Ethernet.begin(mac, ip);  // Inicializa a Ethernet Shield
    server.begin();           // Inicia esperando por requisições dos clientes (Browsers)
    Serial.begin(9600);
    if (!bmp180.begin()) 
  {
    Serial.println("Sensor nao encontrado !!");
    while (1) {}
  }
} // fim do setup

void loop() {

  double temp = bmp180.readTemperature();

  ldrValor = analogRead(ldrPin); // Pega valor da luminosidade

    EthernetClient client = server.available();  // Tenta pegar uma conexão com o cliente (Browser)

    if (client) {  // Existe um cliente em conexão ?
      
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) {   // os dados do cliente estão disponiveis para serem lidos
                char c = client.read(); // lê 1 byte (character) do cliente
                
                // a ultima linha da requisição do cliente é branca e termina com o caractere \n
                // responde para o cliente apenas após a última linha recebida
                if (c == '\n' && currentLineIsBlank) {
                  
                    // envia o cabeçalho de uma resposta http padrão
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: text/html");
                    client.println("Connection: close");
                    client.println();
                    
                    // ENVIA A PÁGINA WEB
                    client.println("<!DOCTYPE html>");
                    client.println("<html>");
                    client.println("<head>");
                    client.println("<meta http-equiv='refresh' content='5';url=150.162.63.156'>");
                    client.println("<title>Dados</title>");
                    client.println("</head>");
                    client.println("<body>");
                    client.println("<h1>Luminosidade</h1>");
                    client.println(ldrValor);

                    client.println("<h2>Temperatura: ");
                    client.println(temp);
                    client.println("</h2>");

                    client.println("<h2>Pressao: ");
                    client.println(bmp180.readPressure());
                    client.println("</h2>");
    
                    
                    client.println("</body>");
                    client.println("</html>");
                    break;
                }
                // toda linha de texto recebida do cliente termina com os caracteres \r\n
                if (c == '\n') {
                    // ultimo caractere da linha do texto recebido
                    // iniciando nova linha com o novo caractere lido
                    currentLineIsBlank = true;
                } 
                else if (c != '\r') {
                    // um caractere de texto foi recebido do cliente
                    currentLineIsBlank = false;
                }
            } // fim do if (client.available())
        } // fim do while (client.connected())
        
        delay(1);      // da um tempo para o WEB Browser receber o texto
        client.stop(); // termina a conexão
        
    } // fim do if (client)
} // fim do loop
