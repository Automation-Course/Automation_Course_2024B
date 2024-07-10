#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // ספרייה עבור חיבור פיזי של LCD
//#include <Adafruit_LiquidCrystal.h> // ספרייה עבור סימולטור של LCD

#define servoPin  9 // פין עבור חיבור הסרבו
#define ledPinGreen 2 // פין עבור חיבור נורית ירוקה
#define ledPinYellow  5  // פין עבור חיבור נורית צהובה
#define ledPinRed 11 // פין עבור חיבור נורית אדומה
#define PhotoresistorPin  A0 // הפין אליו מחובר הפוטורזיסטור ונגד 10K

// אובייקט סרבו
Servo servo;
int speed = 90; // מהירות התחלתית של הסרבו
bool DirectionLeftToClosed = true; // כיוון התנועה של הווילון (לכיוון סגור)
bool DirectionAgainst90 = true; // משתנה עבור כיוון נגד 90 מעלות

// אובייקט LCD
//Adafruit_LiquidCrystal lcd(0); // סימולטור של LCD
LiquidCrystal_I2C lcd(0X27, 16, 2); // חיבור פיזי של LCD עם כתובת I2C, 16 תווים ו-2 שורות

// כפתור לחיצה
int pushButton = 4; // משתנה לאחסון פין החיבור של הכפתור
int switchStatus = 0; // משתנה לאחסון מצב הכפתור, מאתחל לערך 0

// פוטורזיסטור
int PhotoresistorValue = 0; // קריאה אנלוגית מהפוטורזיסטור

bool moveCurtain = false; // משתנה לביצוע תנועה של הווילון
bool curtainClose = false; // משתנה למצב סגור של הווילון

void setup() 
{
    Serial.begin(9600); // אתחול תקשורת סידורית
    servo.attach(servoPin); // חיבור הסרבו לפין המוגדר

    /////// חיבור סימולטור של LCD //////   
    //lcd.begin(16, 2);
    //lcd.setBacklight(1);

    lcd.init(); // אתחול ה-LCD

    // הדלקת תאורת רקע והדפסת הודעה
    lcd.backlight();
    lcd.print("Hello, Yarden!");

    delay(900); 

    // הגדרת פינים כנוריות מוצא
    pinMode(ledPinRed, OUTPUT); 
    pinMode(ledPinGreen, OUTPUT); 
    pinMode(ledPinYellow ,OUTPUT);
    
    // הגדרת פינים כקלט
    pinMode(pushButton , INPUT); 
    pinMode(PhotoresistorPin, INPUT);
}

void loop() 
{
    lcd.clear(); // ניקוי המסך
    PhotoresistorValue = analogRead(PhotoresistorPin); // קריאת ערך אנלוגי מהפוטורזיסטור
    
    // אם הווילונות פתוחים וצריך לסגור אותם
    if ((PhotoresistorValue < 805) and (speed == 90) and (!curtainClose)) 
    {
        blinkingRed();
        lcd.print("Close curtain");
        delay(100);
    }
    
    // אם הווילונות סגורים וצריך לפתוח אותם
    if ((PhotoresistorValue > 805) and (speed == 90) and (curtainClose)) 
    {
        blinkingYellow();
        lcd.print("Open curtain");
        delay(100);
    }
    
    getButton(); // בדיקת מצב הכפתור
    if(moveCurtain)
        moveServo(); // תנועה של הסרבו אם צריך
    
    // הדפסת ערכי הקריאה של הפוטורזיסטור ומהירות הסרבו לסידור
    Serial.print("LDR reading = ");
    Serial.println(PhotoresistorValue);    
    Serial.print("servo speed = ");
    Serial.println(speed);
}

// הפעלת נורית אדומה מהבהבת
void blinkingRed()
{
    digitalWrite(ledPinRed, HIGH);
    delay(100);
    digitalWrite(ledPinRed, LOW);
    delay(100);
}

// הפעלת נורית צהובה מהבהבת
void blinkingYellow()
{
    digitalWrite(ledPinYellow, HIGH);
    delay(100);
    digitalWrite(ledPinYellow, LOW);
    delay(100);
}

void moveServo()
{
    // הגדלת מהירות
    if (DirectionAgainst90)
    { 
        // הגדלת מהירות כשצריך לסגור את הווילון
        if(DirectionLeftToClosed)
        {
            if(speed < 120)
            {
                speed += 1;
            }
            else
            {
                DirectionAgainst90 = false;
            }
        }
        // הגדלת מהירות כשצריך לפתוח את הווילון
        else
        {
            if(speed > 60)
            {
                speed -= 1;
            }
            else
            {
                DirectionAgainst90 = false;
            }
        }
    }
    // הורדת מהירות
    else 
    {
        // הורדת מהירות כשצריך לסגור את הווילון
        if(DirectionLeftToClosed)
        {
            if(speed > 90)
            {
                speed -= 1;
            }
            else
            {
                DirectionAgainst90 = true;
            }
        }
        // הורדת מהירות כשצריך לפתוח את הווילון
        else
        {
            if(speed < 90)
            {
                speed += 1;
            }
            else
            {
                DirectionAgainst90 = true;
            }
        }
    }
      // הווילון סגור
    if((speed == 90) and (DirectionLeftToClosed))
    {
        DirectionLeftToClosed = false;
        DirectionAgainst90 = true;
        
        if(!curtainClose)
        {
            moveCurtain = false; 
            curtainClose = true;
            lcd.print("Curtain closed");
            delay(500);
        }
    }
    // הווילון פתוח
    else if((speed == 90) and (!DirectionLeftToClosed))
    {
        DirectionLeftToClosed = true;
        DirectionAgainst90 = true;
        
        if(curtainClose)
        {
            curtainClose = false;
            moveCurtain = false;
            lcd.print("Curtain open");
            delay(500);
        }
    }
    servo.write(speed); // שליחת ערך המהירות לסרבו
}

// הגדרת מה שקורה כאשר הכפתור נלחץ
void getButton()
{
    // פעולה תבוצע רק כאשר יש צורך בשינוי
    if(((PhotoresistorValue < 805) and (speed == 90) and (!curtainClose)) or
     ((PhotoresistorValue > 805) and (speed == 90) and (curtainClose)))
    {
        // קריאת מצב הכפתור ועדכון המשתנה
        switchStatus = digitalRead(pushButton); 
        
        if(switchStatus == LOW) // אם הכפתור לא לחוץ, הנורית לא תידלק
        {
            digitalWrite(ledPinGreen, LOW);
        }
        else
        {
            digitalWrite(ledPinGreen, HIGH); // אם הכפתור לחוץ, הנורית תידלק
            moveCurtain = true; 
        }
    }
}
