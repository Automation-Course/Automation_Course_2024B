#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Wire.h> 
#include<IRremote.h>
#include <SPI.h>
#include <MFRC522.h>



const byte redledPin = 4;    //using the built in LED
const byte greenledPin=2;
const byte servoPin=3;
const byte irPin=7;
IRrecv reciver(irPin);
decode_results rs;
int counter=0;
float duration;
float distance;
Servo servo1;
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN); 


LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  Serial.begin(9600);
  pinMode(redledPin, OUTPUT);
  pinMode(greenledPin, OUTPUT);
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0,1);
  lcd.print("door is closed");
  digitalWrite(redledPin,HIGH);
  servo1.attach(servoPin); 
  servo1.write(90);
  reciver.enableIRIn();
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
}

void loop()
{
  if(reciver.decode(&rs))
  {
    reciver.disableIRIn();
    Serial.println(rs.value,HEX);
    delay(2000);
     servo1.write(120);
     delay(1000);
     servo1.write(90);
    digitalWrite(greenledPin,HIGH);  
    digitalWrite(redledPin,LOW);
     lcd.clear();
    lcd.setCursor(0,3);
    lcd.print("welcome");
     delay(5000);
    digitalWrite(greenledPin,LOW);
    digitalWrite(redledPin,HIGH);
    delay(10); 
     lcd.clear();
    lcd.setCursor(0,3);
    lcd.print("door is closed");
     servo1.write(60);
     delay(930);
     servo1.write(90);
     reciver.enableIRIn();
     reciver.resume() ;
  }

  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "5A A8 14 B0") //change here the UID of the card/cards that you want to give access
  {
    delay(2000);
     servo1.write(120);
     delay(1000);
     servo1.write(90);
    digitalWrite(greenledPin,HIGH);  
    digitalWrite(redledPin,LOW);
     lcd.clear();
    lcd.setCursor(0,3);
    lcd.print("welcome");
     delay(5000);
    digitalWrite(greenledPin,LOW);
    digitalWrite(redledPin,HIGH);
    delay(10); 
     lcd.clear();
    lcd.setCursor(0,3);
    lcd.print("door is closed");
     servo1.write(60);
     delay(930);
     servo1.write(90);
     reciver.enableIRIn();
     reciver.resume() ;
 }
}