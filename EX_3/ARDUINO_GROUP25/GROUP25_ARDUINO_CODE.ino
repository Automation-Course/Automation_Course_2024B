#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // הגדרת הכתובת והגודל של ה-LCD

Servo servo;

int servoPin = 5; // הפין המחובר למנוע הסרוו
int angle = 0; // זווית התחלתית למנוע הסרוו
bool Direction = true; // משתנה כיוון למנוע הסרוו
bool Is_LED_OFF = true; // משתנה למצב ה-LED
int ledRed = 2; // הפין המחובר ל-LED האדום
int trigPin = 11; // הפין המחובר לפין הטריגר של חיישן האולטרסוניק
int echoPin = 10; // הפין המחובר לפין האקו של חיישן האולטרסוניק
int piezoPin = 3; // הפין המחובר לרכיב הפייזו
long duration, distance, previousDistance = -1; // משתנים לשמירת הזמן, המרחק שנמדד והמרחק הקודם

// משתנים למדידה והגדרת אינטרוולים (מרווחי זמן)
unsigned long ultraSonicPreviousMillis = 0;
const long ultraSonicInterval = 60;  // אינטרוול למדידה בחיישן האולטרסוניק (במילישניות)

unsigned long pigeonPreviousMillis = 0;
const long pigeonInterval = 1000;  // אינטרוול להפעלת פונקציית ההפחדה (במילישניות)

unsigned long servoPreviousMillis = 0;
const long servoInterval = 15;  // אינטרוול להפעלת מנוע הסרוו (במילישניות)

void setup() {
  lcd.init(); // אתחול ה-LCD
  lcd.backlight(); // הפעלת התאורה האחורית

  pinMode(trigPin, OUTPUT); // הגדרת פין הטריגר כפלט
  pinMode(echoPin, INPUT); // הגדרת פין האקו כקלט
  pinMode(ledRed, OUTPUT); // הגדרת פין ה-LED כפלט
  pinMode(piezoPin, OUTPUT); // הגדרת פין הפייזו כפלט
  servo.attach(servoPin); // חיבור מנוע הסרוו לפין המתאים
  Serial.begin(9600); // אתחול תקשורת סריאלית במהירות 9600
}

void loop() {
  triggerUltraSonicSensor(); // הפעלת חיישן האולטרסוניק
  calculateDistance(); // חישוב המרחק
  displayDistanceOnLCD(); // הצגת המרחק על ה-LCD

  // בדיקת מרחק - האם המרחק קטן מ-70 ס"מ
  if (distance < 70 && distance != previousDistance) {
    scarePigeon(); // הפעלת פעולת ההפחדה
  } else {
    resetToNormal(); // החזרת המערכת למצב רגיל
  }

  previousDistance = distance; // שמירת המרחק הקודם
}

// פונקציה להפעלת חיישן האולטרסוניק
void triggerUltraSonicSensor() {
  unsigned long currentMillis = millis(); // שמירת הזמן הנוכחי במילישניות

  if (currentMillis - ultraSonicPreviousMillis >= ultraSonicInterval) { 
    ultraSonicPreviousMillis = currentMillis; // עדכון הזמן האחרון בו הפונקציה פעלה

    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
  }
}

// פונקציה לחישוב המרחק על פי חיישן האולטרסוניק
void calculateDistance() {
  duration = pulseIn(echoPin, HIGH); // מדידת זמן האקו
  distance = duration * 0.034 / 2; // חישוב המרחק על פי הזמן שנמדד
}

// פונקציה להצגת המרחק על ה-LCD
void displayDistanceOnLCD() {
  Serial.print("Distance: ");
  Serial.print(distance); // הדפסת המרחק למסך הסריאלי
  Serial.println(" cm");
  String disp = String(distance); // המרת המרחק למחרוזת

  lcd.clear(); // ניקוי המסך
  lcd.setCursor(0, 0); // הגדרת המיקום להתחלת ההדפסה
  lcd.print("Distance :"); // הדפסת התווית "Distance :"
  lcd.setCursor(0, 1); // הגדרת המיקום להמשך ההדפסה
  lcd.print(disp); // הדפסת המרחק
  lcd.print(" cm"); // הדפסת יחידת המדידה
  delay(200);
}

void scarePigeon() {
  unsigned long currentMillis = millis(); // שמירת הזמן הנוכחי במילישניות

  if (currentMillis - pigeonPreviousMillis >= pigeonInterval) { 
    pigeonPreviousMillis = currentMillis; // עדכון הזמן האחרון בו הפונקציה פעלה

    blinkLED(ledRed); // הפעלת ה-LED
    moveServoMotor(); // הזזת מנוע הסרוו
    tone(piezoPin, 1000); // הפעלת רכיב הפייזו עם תדר 1000Hz
  }
}

void resetToNormal() {
  stopServoMotor(); // עצירת מנוע הסרוו
  digitalWrite(ledRed, LOW); // כיבוי ה-LED
  noTone(piezoPin); // כיבוי רכיב הפייזו
}


void blinkLED(int led) {
  if (Is_LED_OFF) {
    digitalWrite(led, HIGH); // הפעלת ה-LED
    Is_LED_OFF = false; // עדכון מצב ה-LED
  } else {
    digitalWrite(led, LOW); // כיבוי ה-LED
    Is_LED_OFF = true; // עדכון מצב ה-LED
  }
}


void moveServoMotor() {
  if (Direction) {
    angle = 0; // Start from 0 degrees
    Direction = false;
  } else {
    angle = 180; // Move to 180 degrees
    Direction = true;
  }
  servo.write(angle);
}


void stopServoMotor() {
  servo.write(90); // קביעת זווית מנוע הסרוו ל-90 מעלות
}