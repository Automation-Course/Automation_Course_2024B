#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
 
#define SS_PIN 10 // RFID
#define RST_PIN 3 // RFID
#define ledRFID1 5 // LED Green
#define ledRFID2 6 // LED Red
#define servoPin 9 // Servo

// LCD
LiquidCrystal_I2C LCD(0x27, 16, 2); // Set the LCD address to 0x27 for a 16 chars and 2 line display

// RFID
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

// Servo
Servo servo;
int pos = 0;

// PIR
int PIRsensor = 2;

void setup() {
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  pinMode(ledRFID1, OUTPUT);
  pinMode(ledRFID2, OUTPUT);
  servo.attach(servoPin);
  pinMode(PIRsensor, INPUT);
  LCD.init(); // Initialization of the LCD screen
  LCD.backlight(); // Turn on the backlight
	LCD.clear();
  Serial.println("start simulation");
}

void loop() {

  int pirValue = digitalRead(PIRsensor);
  if (pirValue == HIGH) {
    Serial.println("Entering to the room");
    LCD.setCursor(0, 0); // Set cursor to column 0, row 0
    LCD.print("Maya welcome to");
    LCD.setCursor(3, 1); // Set cursor to column 0, row 3
    LCD.print("your room!");
    delay(4000);
    LCD.clear();
  }

  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  
  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  
  // Show UID on serial monitor
  Serial.print("UID tag :");
  String content = "";
  
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  
  if (content.substring(1) == "C3 3F B6 A9") { // Change here the UID of the card/cards that you want to give access
    Serial.println("Authorized access");
    digitalWrite(ledRFID1, HIGH);
    delay(2000);
    digitalWrite(ledRFID1, LOW);
    servo.write(45);
    delay(520);
    Serial.println("door opened");
    servo.write(90); // servo stops
  }
  else {
    Serial.println("Access denied");
    digitalWrite(ledRFID2, HIGH);
    delay(2000);
    digitalWrite(ledRFID2, LOW);
  }


 
}
