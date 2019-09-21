#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Ticker.h>

#define MAX_READING 820
#define MIN_READING 415
#define LED_RED D7
#define LED_GREEN D8
#define INTERRUPT_TIME 3
const char *ssid = "AndroidAP";
const char *pass = "salahspot"; 
 
int localPort = 2500; // local port to listen for UDP packets
 
IPAddress ServerIP(192,168,43,216);
//IPAddress ClientIP(192,168,4,2);
 
// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;
Ticker interruptTimer; 
unsigned short packetBuffer[9];   //Where we get the UDP data
//======================================================================
//                Setup
//======================================================================
void setup()
{
  pinMode(LED_GREEN,OUTPUT);
  pinMode(LED_RED,OUTPUT);
  digitalWrite(LED_RED,HIGH); // turn red led on
    Serial.begin(115200);
    WiFi.begin(ssid, pass);   //Connect to access point
  
    Serial.println("");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
    
    //Start UDP
    Serial.println("Starting UDP");
    udp.begin(localPort);
    Serial.print("Local port: ");
    Serial.println(udp.localPort());
    interruptTimer.attach(INTERRUPT_TIME,timerISR);
    digitalWrite(LED_RED,LOW); //turn off red led
}
//======================================================================
//                MAIN LOOP
//======================================================================
int intSendUDPDataToModuleOnPort(WiFiUDP usedUDP,IPAddress recieverIP,unsigned int communicationPort,unsigned short data){
  int cb = usedUDP.parsePacket();
    if (!cb) 
    {
//unsigned char a = analogRead(A0);
usedUDP.beginPacket(recieverIP,communicationPort);
udp.write(data);
Serial.print("sent data is: ");
Serial.println(data);
usedUDP.endPacket();

return 1;
    }
    else {
     return 0;
    } 
}
void timerISR(void)
{

if (!digitalRead(LED_GREEN)){
  digitalWrite(LED_GREEN,HIGH);
}
else 
{
digitalWrite(LED_GREEN,LOW);  
}
unsigned short readData = analogRead(A0);
Serial.print("Analog reading data pure is: ");
Serial.println(readData);

unsigned char humidityPercentage = (unsigned char)((double)(((readData*1.0-MIN_READING)/(MIN_READING*1.0-MAX_READING))*100.0+100.0));
Serial.print("Analog reading data % is: ");
Serial.println(humidityPercentage);


intSendUDPDataToModuleOnPort(udp,ServerIP,localPort,humidityPercentage);


}


void loop()
{
   
}
