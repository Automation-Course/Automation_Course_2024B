#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Pins for RFID
#define SS_PIN 10
#define RST_PIN 9

// Create instances
MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myServo;

const int redLEDPin = 7;
const int greenLEDPin = 8;
const int trigPin = 5;
const int echoPin = 6;

enum State {IDLE,SCANNED, HAND_DETECTED, THANK_YOU};
State currentState=IDLE;


void setup() {
  // Initialize serial communication
  Serial.begin(9600);
 
  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Scan your card");
 
  // Initialize RFID
  SPI.begin();
  mfrc522.PCD_Init();
 
  // Initialize LEDs
  pinMode(redLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  digitalWrite(redLEDPin, HIGH);
  digitalWrite(greenLEDPin, LOW);
 
  // Initialize distance sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
 
  // Initialize servo motor
  myServo.attach(3);



}

void loop() {
  switch(currentState) {
    case IDLE:
      if (mfrc522.PICC_IsNewCardPresent()) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Wash your hands");
        currentState = SCANNED;
      }
      break;

    case SCANNED:
      if (isHandDetected()) {
        myServo.write(0);
        delay(3000);
        myServo.write(90);
        digitalWrite(redLEDPin, LOW);
        digitalWrite(greenLEDPin, HIGH);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Thank you!");
        lcd.setCursor(0, 1);
        lcd.print("Enjoy your meal");
        currentState = THANK_YOU;
      }
      break;

    case THANK_YOU:
      delay(5000); // Display message for 5 seconds
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Scan your card");
      digitalWrite(redLEDPin, HIGH);
      digitalWrite(greenLEDPin, LOW);
      currentState = IDLE;
      break;
  }
}

bool isHandDetected() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1; // Convert to cm
 
  return distance < 10; // Hand detected within 10 cm
}