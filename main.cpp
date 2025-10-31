Carte transsmiteur donnee:

#include <SPI.h>
#include <LoRa.h>

int trig_PIN = 10;
int echo_PIN = 12;

void setup() {
  Serial.begin(9600);

  pinMode(trig_PIN, OUTPUT);
  pinMode(echo_PIN, INPUT);

  while(!Serial);
  Serial.println("LoRa transsmiteur");
  if( !LoRa.begin(433E6)){
    Serial.println("Starting LoRa failed !");
    while(1);
  }
 
}

void loop() {
 
   digitalWrite(trig_PIN, LOW);
   delayMicroseconds(5);
   digitalWrite(trig_PIN, HIGH);
   delayMicroseconds(10);
   digitalWrite(trig_PIN, LOW);
 
   long duree = pulseIn(echo_PIN, HIGH);
 
   int distance = duree*0.034/2;
 
   Serial.print("Distance : ");
   Serial.print(distance);
   Serial.println("cm");

   LoRa.beginPacket();
   LoRa.print(distance);
   LoRa.endPacket();
   delay(50);

 
}


Carte resepteur donnee:


#include <SPI.h>
#include <LoRa.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);

int LED_20 = 2;
int LED_40 = 3;
int LED_60 = 4;
int LED_80 = 5;
int LED_100 = 6;
int Relay_POMP = 7;
String inString = "";
int distance = 0;

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);

  pinMode(LED_20, OUTPUT);
  pinMode(LED_40, OUTPUT);
  pinMode(LED_60, OUTPUT);
  pinMode(LED_80, OUTPUT);
  pinMode(LED_100, OUTPUT);
  pinMode(Relay_POMP, OUTPUT);

  while(!Serial);
  Serial.println("LoRa Resepteur");
  if(!LoRa.begin(433E6)){
    Serial.println("Starting LoRa failed !");
    while(1);
  }

  lcd.init();
  lcd.backlight();
  // Positionne le curseur en haut à gauche (colonne 0, ligne 0)
  lcd.setCursor(0, 0);
 
}

void loop() {
  int paCketSize = LoRa.parsePacket();
  if(paCketSize){
    while(LoRa.available()){
      int inChar = LoRa.read();
      inString += (char)inChar ;
      distance = inString.toInt();
    }
    inString = "";
    LoRa.packetRssi();
  }
 

 Serial.println("Distance : ");
 Serial.println(distance);
 Serial.println("cm");

 lcd.setCursor(0, 0);
 lcd.print("Distance :");
 lcd.print(distance);
 lcd.print("cm");


 if(distance == 100 ){
 digitalWrite(LED_20,HIGH);
 digitalWrite(Relay_POMP,HIGH);
 lcd.setCursor(0, 1);
 lcd.print("Marche pomp");

 }
 else if(distance == 100){
 digitalWrite(LED_20,HIGH);
 digitalWrite(LED_40,HIGH);
 digitalWrite(Relay_POMP,HIGH);
 lcd.setCursor(0, 1);
 lcd.print("Marche pomp");

 }
 else if(distance == 100){
 digitalWrite(LED_20,HIGH);
 digitalWrite(LED_40,HIGH);
 digitalWrite(LED_60,HIGH);
 digitalWrite(Relay_POMP,HIGH);
 lcd.setCursor(0, 1);
 lcd.print("Marche pomp");
 }
 else if(distance == 100 ){
 digitalWrite(LED_20,HIGH);
 digitalWrite(LED_40,HIGH);
 digitalWrite(LED_60,HIGH);
 digitalWrite(LED_80,HIGH);
 digitalWrite(Relay_POMP,HIGH);
 lcd.setCursor(0, 1);
 lcd.print("Marche pomp");
 }
 else if(distance == 100 ){
 digitalWrite(LED_20,HIGH);
 digitalWrite(LED_40,HIGH);
 digitalWrite(LED_60,HIGH);
 digitalWrite(LED_80,HIGH);
 digitalWrite(LED_100,HIGH);
 digitalWrite(Relay_POMP,HIGH);
 lcd.setCursor(0, 1);
 lcd.print("Arret pomp");

 }
}