#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

const int trigPin = 9;
const int echoPin = 10;
const int buttonPin = 2;
const int ledPin = 6;
const int buzzerPin = 8;
const int servoPin = 7;

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myServo;

void setup() {
  lcd.init();
  lcd.backlight();

// pins setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  myServo.attach(servoPin);
  myServo.write(90); // servo initiatin state
  noTone(buzzerPin); // silent buzzer

  Serial.begin(9600);
  Serial.println("system ready");
}

void loop() {
  //  distance sensor
   long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // conditions to open the door
  if (distance < 50 || digitalRead(buttonPin) == HIGH) {
    if (distance < 50) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Bon apetite Or!");
      Serial.println("Distance sensor activated: Bon apetite Or!");
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Have a good day");
      Serial.println("Button pressed: Have a good day Or!");
    }

    blinkLed(); // Blink led before opening the door

    Serial.println("door begin to open");
    moveServoToAngle(120); 

    delay(3000); 

    moveServoToAngle(60); // mid state
    delay(5000); 
    Serial.println("start alarm before finish closing the door");
    soundAlarm(); 

    moveServoToAngle(90); 
    Serial.println("door closed");
  }
  delay(200); // short pause for preventing repiting startings
}

// Led blinking function
void blinkLed() {
  Serial.println("start led blink");
  digitalWrite(ledPin, HIGH);
  delay(250);
  digitalWrite(ledPin, LOW);
  delay(250);
  digitalWrite(ledPin, HIGH);
  delay(250);
  digitalWrite(ledPin, LOW);
  delay(250);
  digitalWrite(ledPin, HIGH);
  delay(250);
  digitalWrite(ledPin, LOW);
  delay(250);
  digitalWrite(ledPin, HIGH);
  delay(250);
  digitalWrite(ledPin, LOW);
  delay(250);
  digitalWrite(ledPin, HIGH);
  delay(250);
  digitalWrite(ledPin, LOW);
  delay(250);
  Serial.println("finish led blink");
}

// move servo to desired angle
void moveServoToAngle(int angle) {
  myServo.write(angle); 
  delay(6000); // waiting time for the servo to get to the angle
}

// function to sound alarm
void soundAlarm() {
  tone(buzzerPin, 1000); 
  delay(500);
  noTone(buzzerPin); 
  delay(500);
  tone(buzzerPin, 1000); 
  delay(500);
  noTone(buzzerPin); 
  delay(500);
  tone(buzzerPin, 1000);
  delay(500);
  noTone(buzzerPin); 
  delay(500);
  tone(buzzerPin, 1000); 
  delay(500);
  noTone(buzzerPin); 
  delay(500);
  Serial.println("alarm stopped");
}
