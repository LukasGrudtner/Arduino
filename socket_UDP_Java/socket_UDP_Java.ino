#include <SPI.h>         // needed for Arduino versions later than 0018
#include <Ethernet.h>
#include <EthernetUdp.h>        

// Enter a MAC address and IP address for your controller below.
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(150, 162, 63, 156);

int localPort = 9090;      // local port to listen on


// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];  //buffer to hold incoming packet,
char  ReplyBuffer[38];//[] = "acknowledged";       // a string to send back
char  temp[38];
String replay;
float h, t; //for temp and himity

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

void setup() {


  // start the Ethernet and UDP:
  Ethernet.begin(mac, ip);
  Udp.begin(localPort);
  Serial.begin(9600);
  Serial.println("Start");
 
}

void loop() {
 
  int packetSize = Udp.parsePacket();
  
  if (packetSize) { // when receive the packet the arduino
    Serial.print("Received packet of size ");
    Serial.println(packetSize); // show the size of packet and the ip which came
    Serial.print("From ");
    IPAddress remote = Udp.remoteIP();
    String te = "Ola mundo";
    te.toCharArray(temp, 40);

    // read the packet into packetBufffer
    Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    Serial.println("Contents:");
    Serial.println(packetBuffer);
    
    if (strcmp(packetBuffer, "Temp") == 0) {
      Serial.println("Temperature send");
      Serial.println(temp);
      //make a packet udp to send to the 
      //IP and the port which receive the packet
      //temp
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
      //write in packet the temper and him
      Udp.write(temp);
      //end the packet and is ready for send
      Udp.endPacket();
    } 
    // clear the char arrays for the next receive packet and send
    memset(ReplyBuffer, 0, sizeof(ReplyBuffer));
    memset(packetBuffer, 0, sizeof(packetBuffer));

  }

  delay(10);

}



