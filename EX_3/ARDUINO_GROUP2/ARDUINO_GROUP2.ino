//Upload libraries
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

//define pins
#define trigPin 11
#define echoPin 10
#define ledPin 12
#define buttonPin 2
#define servoPin 9

//define servo and lcd
Servo myServo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

//initial variables
int speed=0;
long duration;
double distance;
bool buttonPressed = false;
int buttonState = 0;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  //initial LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();

  //initial servo
  myServo.attach(servoPin);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  distance = measureDistance();
  //if there is people near the mirror
  if (distance < 50) {
    Serial.println("Ligth ON");
    //turn on the led
    digitalWrite(ledPin, HIGH);
    //print on the lcd
    lcd.setCursor(0, 0);
    lcd.print("Mirror mirror on");
    lcd.setCursor(0, 1);
    lcd.print("the wall Who's");
    delay(1000);
    //check if someone turn on the steam cleaner
    checkButtonState();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("the prettiest");
    lcd.setCursor(0, 1);
    lcd.print("of them all ?");
    delay(1000);
    checkButtonState();
    lcd.clear();
  } else {
    Serial.println("Ligth OFF");
    //turn off the led
    digitalWrite(ledPin, LOW);
    lcd.clear();
  }
  checkButtonState();
  // Check if the pushbutton is pressed
  if (buttonPressed) {
    Serial.println("Steam cleaner ON");
    moveServo();
    delay(1000);
  } else {
    Serial.println("Steam cleaner OFF");
    myServo.write(90);
  }
  delay(50);
}

//measure the distance of the people from the mirror
double measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  //Normalize the speed of light
  return duration * 0.034 / 2;
}

void moveServo() {
  //move the servo
  myServo.attach(servoPin);
  speed = 180;
  myServo.write(speed);
}

//check the button state
void checkButtonState() {
  buttonState = digitalRead(buttonPin);
  //if the button is pressed
  if (buttonState == HIGH && !buttonPressed) {
    buttonPressed = true;
  }
  //if the button is unpressed
  if (buttonState == LOW && buttonPressed) {
    buttonPressed = false;
  }
  if (buttonPressed) {
    moveServo();
  }
}