#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// initiate variables:
// LCD, Set the LCD address to 0x27 for a 16 chars and 2 line display
int seconds = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Servo
#include <Servo.h>
#define servoPin 3
Servo servo;
int angle = 0;
bool Direction = true;

// ultrasonic
//#include <Servo.h>
#define trig 7
#define echo 5
double duration, distance; // משתנים המחשבים את מידת הזמן והמרחק המודדים

// led & button, Turn on led when the button is pushed
int buttonState = 0;
int buttonHold = 0;
#define led 4
#define inPin 2
int counter = 0;
bool isWork = false;

void setup() {
  servo_init();
  ultraSonic_init();
  led_button_init();
  LCD_init();
}

void loop() {
  servo_loop();
  ultraSonic_loop();
  led_button_loop();
  LCD_loop();
  dayWork_loop();
  led_loop();
}

// LCD:
void LCD_init() {
  // initialize the LCD
  lcd.init();
  // Turn on the blacklight and print a message.
  lcd.backlight();
}

void LCD_loop() {
  if (isWork) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(String("Distance: ") + String(distance));
    lcd.setBacklight(1);
    delay(200); // Wait for 200 millisecond(s)
    lcd.setBacklight(1);
    delay(200); // Wait for 200 millisecond(s)
    seconds += 1;
    if (distance <= 10) {
      lcd.setCursor(0, 1);
      lcd.print(String("Back off!"));
    }
  } else {
    lcd.clear();
  }
}

// servo:
void servo_init() {
  servo.attach(servoPin);
}

void servo_loop() {
  // round the servo
  if (distance >= 10 && isWork) {
    if (Direction){
      angle=180;
    } else {
       angle=0;
    }
    servo.write(angle);
    if (angle == 180)
      Direction=false;
    if (angle == 0)
      Direction=true;
  }
}

// ultrasonic:
// setUp ultrasonic sensor
void ultraSonic_init() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void ultraSonic_loop() {
  // // Initialize the trigger pin of the ultrasonic sensor, TRIG
  digitalWrite(trig, LOW); //
  delayMicroseconds(2);
  digitalWrite(trig, HIGH); // Sending a pulsed signal
  delayMicroseconds(10);
  digitalWrite(trig, LOW); // Sending a pulsed signal
  duration = pulseIn(echo, HIGH); // Capturing and measuring the pulse duration
  distance = duration / 29 / 2;  // Calculating the distance
  Serial.print("distance[cm]=");
  Serial.println(distance);
  delay(500);
}

void led_button_init() {
  pinMode(inPin, INPUT);
  pinMode(led, OUTPUT);
   isWork = false;
}

void led_button_loop() {
  buttonHold = digitalRead(inPin); // read the state of the pushbutton value
  if ((buttonHold && !buttonState))
    buttonState = true;
  else if (isWork && buttonHold)
    buttonState = false;
}

void led_loop() {
  digitalWrite(led, isWork);
}

void dayWork_loop() {
  Serial.println(String("isWork: ") + isWork);
  Serial.print("buttonstate: ");
  Serial.println(buttonState);
  Serial.print("buttonhold: ");
  Serial.println(buttonHold);
  if (buttonState == 1)
    isWork = true;
  else{
    isWork = false;
    //servo.write(90);
  }
}