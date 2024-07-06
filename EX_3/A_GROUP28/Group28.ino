#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define pin for servo motor
#define SERVO_PIN 9
// Create servo object
Servo servo;
// Define pin for temperature sensor
#define TEMP_SENSOR A0
#define LED_AC 13
#define LED_LEFT_DESK 12
#define LED_RIGHT_DESK 7
#define IN_PIN_LEFT 4
#define IN_PIN_RIGHT 2
bool direction = true;
int angle = 0;
int speed = 0;
int buttonLeft = 0;
int buttonRight = 0;


void setup() 
{
  pinMode(IN_PIN_LEFT, INPUT);
  pinMode(IN_PIN_RIGHT, INPUT);
  pinMode(LED_AC, OUTPUT);
  pinMode(LED_LEFT_DESK, OUTPUT);
  pinMode(LED_RIGHT_DESK, OUTPUT);
  servo.attach(SERVO_PIN);
  //servo.write(0);
  lcd.init();
  Serial.begin(9600);
}

void loop() {
//Serial.println(angle);
  float temperature;
  // Measure temperature
  temperature = analogRead(TEMP_SENSOR);
  temperature = (temperature *0.1) - 70; // Convert to degrees Celsius
  Serial.println(temperature);

  if (temperature > 25 && temperature <= 50)
  {
    Serial.println("Too hot, turning on cooling AC");
    digitalWrite(LED_AC, HIGH); // Turn on LED (air conditioner)
    lcd.setBacklight(1);
    lcd.println("Cooling AC ON      ");
    lcd.setCursor(0, 1);
    lcd.print("Temp is " + String(temperature) + " C");
    delay(1000);
    lcd.clear();
  }

  else if (temperature < 18)
  {
    Serial.println("Too cold, turning on heating AC.");
    digitalWrite(LED_AC, HIGH); // Turn on LED (air conditioner)
    lcd.setBacklight(1);
    lcd.println("Heating AC ON      ");
    lcd.setCursor(0, 1);
    lcd.print("Temp is " + String(temperature) + " C");
    delay(1000);
    lcd.clear();
  }

  //Fire Case
  else if (temperature > 50)
  {
    Serial.println("Fire suspection. opening door");
    digitalWrite(LED_AC, LOW); // Turn off LED
    Serial.println("Air conditinior turned off.");
    if (direction)
    {
      angle += 1;
      servo.write(100);
    } 
    if (angle == 90)
    {
      direction = false;
      servo.write(90);
    } 
  }

  //Nice weather Case
  else 
  {
    lcd.setBacklight(1);
    lcd.println(" AC is OFF      ");
    lcd.setCursor(0, 1);
    lcd.print("Temp is " + String(temperature) + " C");
    delay(1000);
    lcd.clear();
    Serial.println("Air conditinior turned off.");
  }

  //Emergemcy Buttons
  buttonLeft = digitalRead(IN_PIN_LEFT);
  digitalWrite(LED_LEFT_DESK, buttonLeft); 
  buttonRight = digitalRead(IN_PIN_RIGHT);  
  digitalWrite(LED_RIGHT_DESK, buttonRight);
}
