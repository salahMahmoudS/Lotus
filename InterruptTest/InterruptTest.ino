#include <Ticker.h>

#define ledPin D1
Ticker interruptTimer;

void timerISR(void){
if (digitalRead(ledPin) ==LOW)
{
digitalWrite(ledPin,HIGH);  

}
else 
{
digitalWrite(ledPin,LOW);  
}
Serial.print("D1 state is: ");
Serial.println(digitalRead(ledPin));
}
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);  
pinMode(ledPin,OUTPUT);  
interruptTimer.attach(4,timerISR);
}

void loop() {
  // put your main code here, to run repeatedly:

}
