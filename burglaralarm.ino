#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 10, 4, 5, 6, 7);
SoftwareSerial mySerial(12,13);//RX , TX
int sensor1 = 23;
void sendCommand(String,int);
void readSerial();
void sendsms();
char inchar;

void setup(){
  Serial.begin(9600);
  Serial.println("*AMIR SENSOR'S*");
  lcd.begin(16,2);
  lcd.clear();
  lcd.home();
  lcd.print("*AMIR SENSOR'S*");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("HAVE A GOOD TIME SIR...");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  mySerial.begin(9600);
  delay(2000);
  sendCommand("AT",2000);
  delay(1000);
  readSerial();
  //sendsms();
  sendCommand("AT+CMGF=1",2000);
  delay(200);
  readSerial();
  sendCommand("AT+CSMP=17,167,0,0",2000);
  delay(200);
  readSerial();
  sendCommand("AT+CNMI=2,2,0,0,0\r",2000);
  delay(200);
  readSerial();
  sendCommand("AT+CSQ",2000);
  readSerial();
  delay(200);
  pinMode(sensor1,INPUT);
  Serial.println("Ready...");
  lcd.println("...READY...");
  
}
void loop(){
  recive_sms();
}
void readSerial() {
  while (mySerial.available())
    Serial.write(mySerial.read());

}
void recive_sms(){
if (sensor1 == 22){
  sensor_pirpin(); 
}
else if(mySerial.available()>0)
 {
   sensor1 = 23;
   delay(200);
   inchar=mySerial.read();
   if(inchar=='#')
   {
     delay(10);
     inchar=mySerial.read();
     if (inchar=='a')
     {
       delay(10);
       inchar=mySerial.read();
       if (inchar=='0')
       {
         sensor1 = 23;
         lcd.print("TURN OFF SENSOR 1...");
         Serial.println("sensor1 off...");
         delay(5000);
         lcd.clear();
         lcd.setCursor(0,0);
       }
       else if (inchar=='1')
       {
         sensor1 = 22;
         lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("TURN ON SENSOR 1...");
         Serial.println("sensor1 on...");
         delay(5000);
         lcd.clear();
         lcd.setCursor(0,0);
         sensor_pirpin();
       }
       delay(10);
   }
}
  //mySerial.println("AT+CMGD=1,4"); // delete all SMS
  //delay(200);
  //readSerial();
}
}
void sendCommand(String cmd, int t)
{
  mySerial.println(cmd);
  delay(200);
  readSerial();
}
void sendsms(){
  //mySerial.println("ATD09910225046;");
  //delay(200);
  //readSerial();
  //delay(10000);
  //mySerial.println("ath");
  //delay(200);
  mySerial.println("AT+CMGS=\"+\""); 
  delay(500);
  readSerial();
  delay(1000);
  mySerial.print("\r\nI am sens a motion! enter again #a1 or turn your camera up...!\x1A");
  delay(3000);
  mySerial.println("AT+CMGD=1,4"); // delete all SMS
  delay(200);
  readSerial();
  delay(1000);
  //sensor1 = 22;
}
void sensor_pirpin()
 {
  if (digitalRead(sensor1) == HIGH and sensor1==22) {
    Serial.println("MOTION...");
    sensor1 = 23;
    sendsms();
    delay(1000);
  }
   
  /*else if(digitalRead(sensor1)==LOW){
    Serial.println("NO MOTION...");
    delay(200);
  }*/
  }
