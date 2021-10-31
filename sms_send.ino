#include <SoftwareSerial.h>
SoftwareSerial mySerial(12,13);//RX , TX
void sendCommand(String,int);
void readSerial();
void sendsms();
char inchar;

void setup(){
  Serial.begin(9600);
  Serial.println("*AMIR SENSOR'S");
  mySerial.begin(9600);
  delay(2000);
  sendCommand("AT",2000);
  delay(1000);
  sendsms();
  
}
void loop(){
  
}
void readSerial() {
  while (mySerial.available())
    Serial.write(mySerial.read());

}
void sendCommand(String cmd, int t)
{
  mySerial.println(cmd);
  delay(200);
  readSerial();
}
void sendsms(){
  mySerial.println("ATD09910225046;");
  delay(200);
  readSerial();
  delay(10000);
  mySerial.println("ath");
  delay(200);
  mySerial.println("AT+CMGF=1");
  delay(200);
  readSerial();
  mySerial.println("AT+CSMP=17,167,0,0");
  delay(200);
  readSerial();
  mySerial.println("AT+CMGS=\"+989910225046\""); 
  delay(500);
  readSerial();
  mySerial.print("Salam\r\n ...ALARM... !\x1A");
  delay(20000);
}
