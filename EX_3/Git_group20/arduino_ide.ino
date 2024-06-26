// C++ code
// AC system for guest convinience temprature

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Servo.h>

#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

int ledPinGreen = 5;
int ledPinRed = 3;
int ledPinWhite = 6;
int servo_pin = 9;
int pr_pin = A0;
double temp = 0;
int pr_value =0; 
double degrees = 0; 
int servo_angle = 0; 
int servo_speed = 0; 
bool on = true;
bool off = true;

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servo_motor;

void setup()
{
	// initialize the LCD
	lcd.init();
	// Turn on the blacklight and print a message.
	lcd.backlight();
  lcd.print("Welcome !!!");
  delay(2000);

  //pinMode(temp_sensor, INPUT);
  pinMode(pr_pin, INPUT);
  digitalWrite(pr_pin, LOW);

  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinWhite, OUTPUT);

  servo_motor.attach(servo_pin);
  Serial.begin(9600);
  sensors.begin();
}

void loop()
{
  pr_value = analogRead(pr_pin);
  Serial.println(pr_value);

  if (isDayTime(pr_value) && on == true)
  { 
    on = false;
    off = true;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("System is on !!");
  }else if (isDayTime(pr_value))
  {// if the current situation is during the day - check temprature and light the correct led
    sensors.requestTemperatures(); // Request temperature readings
    temp = sensors.getTempCByIndex(0);
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println(" °C");
    controll_leds(temp);
  }else if(!isDayTime(pr_value) && off == true)
  {
    off = false;
    on=true;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("System is off !!");
    turnOff_AC();
    digitalWrite(ledPinGreen, LOW);
    digitalWrite(ledPinRed, LOW);
    digitalWrite(ledPinWhite, LOW);
  }
  delay(1000); // Delay to slow down the loop
}

void turnOn_AC ()
{
  if (servo_angle <= 180)
  {
   servo_motor.write(servo_speed);
   servo_angle ++;
   servo_speed = 180;
  }else
  {
   servo_motor.write(servo_speed);
   servo_angle --;
   servo_speed = 0;
  }
}

void turnOff_AC ()
{
  if(servo_angle != 90) // the servo engine is on
  {
   servo_motor.write(90); // turning off the engine
  }
}

bool isDayTime(int pr_value)
{
  if (pr_value <= 300)
  {
    return true;
  }else
  {
   return false; 
  }
}

void blinkLed(int led)
{  
    digitalWrite(led, HIGH); // set the led on
    delay(50); // wait for a second
    digitalWrite(led, LOW); // turn the LED off
    delay(50); // wait for a second
}

void controll_leds (double temp)
{
  if (temp >= 25)
  {
   digitalWrite(ledPinGreen, LOW);
   blinkLed(ledPinRed); 
   turnOn_AC();

  }else if(temp <= 18)
  {
   digitalWrite(ledPinGreen, LOW);
   blinkLed(ledPinWhite); 
   turnOff_AC();

  }else
  {
   digitalWrite(ledPinGreen, HIGH);
   digitalWrite(ledPinRed, LOW);
   digitalWrite(ledPinWhite, LOW);
  }
}


