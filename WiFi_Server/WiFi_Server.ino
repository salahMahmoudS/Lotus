#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


//define the name and password of the router
const char *authenticate = "NA8-hA-yGl3o_ohr84-laFrXfE4x5Hu0";
const char *ssid = "AndroidAP";
const char *pass = "salahspot"; 
#define MAX_HUMIDITY 100
#define MIN_HUMIDITY 50
#define PUMP_PIN1 D0
#define PUMP_PIN2 D1
#define IRRIGTATION_TIME_MILLI_SECONDS 5000
//define the ports we will connect to 
#define Sensors_Modules_Port 2500 // local port to listen for UDP packets 
#define ServerPort 50

//define the addresses we will connect to 
IPAddress ServerIP(192,168,43,16);
IPAddress ClientIP(192,168,2,4);

//Arrays that will store the sensors readings
unsigned char Sensor_One_Last_Ten_Readings[10] = {0,0,0,0,0,0,0,0,0,0}; 
int sensor_one_counter = 0;
int sensor_one_decision =0;

// A UDP instance to let us send and receive packets over UDP
int packetRecievedSize =0;
WiFiUDP Modules_udp;
WiFiUDP Server_udp; 
unsigned char packetBuffer[UDP_TX_PACKET_MAX_SIZE + 1];   //Where we get the UDP data
//=======================================================================
//                Setup
//=======================================================================

int intCreateAccessPoint(WiFiUDP Modules_udp,int Connection_Port){
Serial.println("Starting the Modules UDP connection");
if(Modules_udp.begin(Connection_Port)){
    Serial.print("Control box Local IP:");
    Serial.println(WiFi.localIP());
    Serial.print("Recieve from modules port: ");
    Serial.println(Modules_udp.localPort()); 
    return 1; 
}
else {
  return 0;
}
}


void setup()
{
    Serial.begin(115200);
    WiFi.begin(ssid, pass);
    Serial.println("Connecting");
    while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
   pinMode(PUMP_PIN1,OUTPUT);
   pinMode(PUMP_PIN2,OUTPUT); 
   digitalWrite(PUMP_PIN1,HIGH);
   digitalWrite(PUMP_PIN2,HIGH);
  }
    
    Serial.println("SSID");
    //Start UDP
    Serial.println("Starting the Modules UDP connection");
    Modules_udp.begin(Sensors_Modules_Port);
    Serial.print("Control box Local IP:");
    Serial.println(WiFi.localIP());
    Serial.print("Recieve from modules port: ");
    
    Serial.println(Modules_udp.localPort());

//Initialize the Server connection
    Server_udp.begin(ServerPort);
     Serial.print("Send to server Port:");
    Serial.println(Server_udp.localPort());
    
    //intCreateAccessPoint(Modules_udp,Sensors_Modules_Port);
    //intCreateAccessPoint(Server_udp,ServerPort);
 Blynk.begin(authenticate, ssid, pass);
}
//======================================================================
//                MAIN LOOP
//======================================================================
void loop()
{
  Blynk.run();
   packetRecievedSize = Modules_udp.parsePacket();
   if(packetRecievedSize !=0)
    {
     Serial.print("The size of buffer is "); 
     Serial.println(packetRecievedSize);
     Serial.print(" Buffer data ");
     if (sensor_one_counter < 10){
   Modules_udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    Serial.print("packetBuffer data is: ");
    Serial.println(packetBuffer[0]);
    Sensor_One_Last_Ten_Readings[sensor_one_counter] =packetBuffer[0];
    Blynk.virtualWrite(V1,Sensor_One_Last_Ten_Readings[sensor_one_counter]);
    Serial.print("CB Array reading is: ");
    Serial.println(Sensor_One_Last_Ten_Readings[sensor_one_counter]);
     sensor_one_counter++;
    }
    else {
    int result =0;  
    Serial.println("Sensor is full, printing data");
    for (int i=0;i<sizeof(Sensor_One_Last_Ten_Readings)/sizeof(char);i++)
      {
      Serial.print(Sensor_One_Last_Ten_Readings[i]);
      result+=Sensor_One_Last_Ten_Readings[i];
      }
      Serial.println("");
      double averageReading = result/(sizeof(Sensor_One_Last_Ten_Readings)/sizeof(char)) *1.0;
      Serial.print("Average reading is: ");
      Serial.println(averageReading);
          if (averageReading < MIN_HUMIDITY){
        digitalWrite(PUMP_PIN1,LOW);  
        delay(IRRIGTATION_TIME_MILLI_SECONDS);
        digitalWrite(PUMP_PIN1,HIGH);
          }
      sensor_one_counter =0;
      memset(Sensor_One_Last_Ten_Readings,0,sizeof(Sensor_One_Last_Ten_Readings)/sizeof(char));    
      Serial.println("Readings after reset");
       for (int i=0;i<sizeof(Sensor_One_Last_Ten_Readings)/sizeof(char);i++)
      {
      Serial.print(Sensor_One_Last_Ten_Readings[i]);
      }
      Serial.println("");
        }
        }
    else {

    }
    }
    /*Server_udp.beginPacket(ServerIP,ServerPort);
    Server_udp.write(packetBuffer[0]);
    Server_udp.endPacket();
    delay(10);*/
    
    //all what is between /* and */ should be removed to return to return to previous version
    /*if (!cb) 
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
    else {*/
      // We've received a UDP packet, send it to serial
      //udp.read(); // read the packet into the buffer, we are reading only one byte
   
   
//    packetBuffer[n] = 0;
   
    
    //Serial.println(udp.read());
          

  
  /*}*/
  
