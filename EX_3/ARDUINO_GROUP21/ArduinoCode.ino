#include <Servo.h>
#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd(0);

// Pins definition
#define led 13
#define servo_pin 9
#define buzer_pin 7
#define PIR_pin 2
#define in_pin 4

int volume = 0;
int button_State = 0;
bool alarm_on = false;
int alarmCounter = 6;
int angel = 0;
bool direction = true;
Servo servo;

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(buzer_pin, OUTPUT);
  pinMode(PIR_pin, INPUT);
  servo.attach(servo_pin);
  digitalWrite(PIR_pin, LOW);
  pinMode(in_pin, INPUT);
}

void loop() {
  button_State = digitalRead(in_pin);
  if (button_State == 1) {
    Serial.print("Push Button");
    push_button();
  }
  if (motion() || alarm_on) {
    alarm(); // turn on the alarm and the buzzer
    alarmCounter--;
  }
    if (alarmCounter == 0) {
      alarm_on = false;
      alarmCounter = 6;
    }
   else {
    no_alarm();
  }
  delay(500);
}

bool motion() { // PIR sensor detection check input
  if (digitalRead(PIR_pin) == HIGH) { // Movement detected
    Serial.println("PIR - high");
    alarm_on = true;
    Serial.print("servo is on!");
    if (direction) {
      angel += 30;
    } else {
      angel -= 30;
    }
    servo.write(angel);
    if (angel == 180) {
      direction = false;
    }
    if (angel == 0) {
      direction = true;
    }
    return true; // Movement detected
  }
  return false; // No movement detected
}

void alarm() {
  digitalWrite(led, HIGH);
  buzer_on();
  write_lcd(true);
}

void no_alarm() {
  digitalWrite(led, LOW);
  noTone(buzer_pin);
  write_lcd(false);
}

void buzer_on() { // Buzzer on for the alarm
  if (volume >= 300) {
    volume = 100;
  } else {
    volume += 10;
  }
  tone(buzer_pin, volume);
  delay(100);
  Serial.print("Buzzer is on, the volume is: " + String(volume));
}

void write_lcd(bool type) { // LCD display for state
  lcd.clear();
  if (type) { // Alarm on
    lcd.print("thief");
    lcd.setCursor(0, 1);
    lcd.print("is here!");
    Serial.print("LCD is on");
  } else { // Alarm off
    lcd.print("Welcome To ");
    lcd.setCursor(0, 1);
    lcd.print("Din's Hotel :)");
    Serial.print("LCD is on");
  }
}

void push_button() {
  servo.write(90); // Restart servo
  Serial.print("servo is off!");
  lcd.clear();
  lcd.print("Calling to");
  lcd.setCursor(0, 1);
  lcd.print("the Police");
  delay(100);
}