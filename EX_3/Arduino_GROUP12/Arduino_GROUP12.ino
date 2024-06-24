#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h> // כולל את הספרייה של ה-Servo

// הגדרות פינים
#define LdrPin  A0
#define LedPin  5
#define servoPin  9
#define gasSensorPin A1
#define buzzer 3
#define trigPin 11
#define echoPin 10


// משתנים גלובליים
int LdrValue = 0;
int LedBrightness;
int angle = 0;
bool Direction = true;
const int threshold = 300;
int gasValue;
int buttonState = 0;
int lastButtonState = 0;
int ledState = LOW;
long duration, distance;

LiquidCrystal_I2C lcd_1(0x27,16,2);
Servo servo;

void setup() {
    // הגדרות פינים
    pinMode(LdrPin, INPUT);
    pinMode(LedPin, OUTPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    Serial.begin(9600);
    servo.attach(servoPin);
    pinMode(gasSensorPin, INPUT);
    pinMode(buzzer, OUTPUT);
    
    // אתחול ה-LCD
    lcd_1.init();
}

void loop() {
    // קריאת חיישן גז
    gasValue = analogRead(gasSensorPin);
    UltraSonic();
    Distance_Calculation();
    GasSensor(gasValue, threshold);
    
    // הדפסת המרחק במסך הקונסול
    // Serial.print("Distance: ");
    // Serial.print(distance);
    // Serial.println(" cm");
    
    if (distance < 50) {
        lcd();
        lightSensor();
        servo1();
    } else {
        return_normal();
    }
}

void return_normal() {
    servo.write(90); // החזר את המנוע למקום
    digitalWrite(LedPin, LOW); // כבה את ה-LED
    lcd_1.clear();
    digitalWrite(buzzer, HIGH);

}

void lightSensor() {
 LdrValue = analogRead(LdrPin);
// Serial.print("LDR reading = ");
// Serial.println(LdrValue); // the raw analog reading
if (LdrValue < 500)
digitalWrite(LedPin, LOW);
else
digitalWrite(LedPin, HIGH);
delay(100);
}

void lcd() {
    lcd_1.setBacklight(1);
    lcd_1.setCursor(0, 0);
    lcd_1.print("Welcome! Enjoy");
    delay(1000);
    lcd_1.clear();
    lcd_1.setBacklight(0);
    delay(1000);
}

void servo1() {
    if (Direction) {
        angle += 180;
    } else {
        angle -= 180;
    }
    servo.write(angle);
    delay(15);
    if (angle == 180) Direction = false;
    if (angle == 0) Direction = true;
}

void UltraSonic() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
}

void Distance_Calculation() {
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
}

void GasSensor(int gasValue, int threshold) {
    if (gasValue < threshold) {
        Serial.println(gasValue);
         digitalWrite(buzzer, HIGH);

    } else {
        Serial.println("high Gas Value: ");
        Serial.println("Gas Value: ");
        Serial.println(gasValue);
        digitalWrite(buzzer, LOW);
    }
}