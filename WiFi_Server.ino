#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
 
const char *ssid = "SK";
const char *pass = "karimsalah"; 
 
unsigned int localPort = 2000; // local port to listen for UDP packets
unsigned int ServerPort = 50;
 
IPAddress ServerIP(192,168,2,15);
IPAddress ClientIP(192,168,2,4);
 
// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;
WiFiUDP Server_udp; 
unsigned char packetBuffer[UDP_TX_PACKET_MAX_SIZE + 1];   //Where we get the UDP data
//=======================================================================
//                Setup
//=======================================================================
void setup()
{
    Serial.begin(115200);
    WiFi.softAP(ssid, pass);
Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
    //Create Access point
 Serial.println("SSID");
    //Start UDP
    Serial.println("Starting UDP");
    udp.begin(localPort);
    Serial.print("Local IP:");
    Serial.println(WiFi.localIP());
    Serial.print("Local port: ");
    
    Serial.println(udp.localPort());

//Initialize the Server connection
    Server_udp.begin(ServerPort);
     Serial.print("Local IP:");
    Serial.println(Server_udp.localPort());
    
}
//======================================================================
//                MAIN LOOP
//======================================================================
void loop()
{
    int cb = udp.parsePacket();
    if (!cb) 
    {
      //If serial data is recived send it to UDP
      if(Serial.available()>0)
        {
        udp.beginPacket(ClientIP, 2000);
        //Send UDP requests are to port 2000
        
        char a[1];
        a[0]=char(Serial.read()); //Serial Byte Read
        udp.write(a,1); //Send one byte to ESP8266 
        udp.endPacket();
        }
    }
    else {
      // We've received a UDP packet, send it to serial
      //udp.read(); // read the packet into the buffer, we are reading only one byte
    udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
     Serial.println(packetBuffer[0]);
     Server_udp.parsePacket();
    Server_udp.beginPacket(ServerIP,ServerPort);
    Server_udp.write(packetBuffer[0]);
    Server_udp.endPacket();
//    packetBuffer[n] = 0;
   
    
    //Serial.println(udp.read());
          delay(20);
    }
}
