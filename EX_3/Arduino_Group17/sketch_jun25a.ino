#include <Servo.h>
#include <OneWire.h>
#include <LiquidCrystal_I2C.h>
#include <DallasTemperature.h>


// Constants and Macros
#define TRIG_PIN 12
#define ECHO_PIN 10
#define SERVO_PIN 7
#define TEMP_SENSOR 13
#define LED_PIN 4

// Globals
LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD with I2C address 0x27
Servo servo;
bool isInside = false;
long duration = 0;
long distance = 0;
float temperature = 0;
OneWire onewire(TEMP_SENSOR);
DallasTemperature sensors(&onewire);

// Function Prototypes
void initializeSystem();
void measureDistance();
void controlDoor();
void measureAndDisplayTemperature();
void controlAC();

// Setup function
void setup() {
  Serial.begin(9600);
  sensors.begin();
  initializeSystem();
}

//.........................Main loop function........................
void loop() {
  measureDistance();
  controlDoor();
  lcd.clear();
  
  if (isInside== true) {
    measureAndDisplayTemperature();
    controlAC();
    delay(1000); // Avoid flickering and clear before next update
    lcd.clear();
  }
}
//.....................................................................

// Function Definitions

// Initializes system components
void initializeSystem() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  servo.attach(SERVO_PIN);
  
  lcd.init();
  lcd.backlight();
  lcd.print("Initializing...");
  delay(1000); // Display initializing message
  lcd.clear();
}

// Measures distance using the ultrasonic sensor
void measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration / 2) / 29.1; // Calculate distance in cm (duration / 29 / 2 is approximately duration * 0.034 / 2)
  
  
  if (distance > 60 && distance <= 0) {
    Serial.println("the distance is more than 60");
  } else {
    Serial.println(distance);
    Serial.println("cm");
  }
  delay(500);
}



// Controls the door based on the distance measured
void controlDoor() {
  if (distance < 50 && isInside==false) {
  servo.write(180);  // set servo to full speed in one direction
  delay(500);          // wait for 500ms (adjust this value to get approximately 90 degrees)

  // Stop the servo
  servo.write(90);   // stop the servo
  isInside=true;
  lcd.print("WELCOME!!!!!");
  delay(1000);

  } else if(isInside==true && distance > 50){
    // Turn the servo to the left
  servo.write(0);    // set servo to full speed in the opposite direction
  delay(500);          // wait for 500ms (adjust this value to get approximately 90 degrees)

  // Stop the servo
  servo.write(90);   // stop the servo
  delay(1000);
  isInside=false;
  }

  }


// Measures temperature and displays it on the LCD
void measureAndDisplayTemperature() {
  sensors.requestTemperatures();
  temperature = sensors.getTempCByIndex(0);
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print("C ");
  delay(1000);
}

// Controls the air conditioner based on the temperature
void controlAC() {
  if (temperature > 25) {
    digitalWrite(LED_PIN, HIGH); // Turn on LED (AC on)
    lcd.setCursor(0, 1);
    lcd.print("AC ON COLD");
  } else if (temperature < 16) {
    digitalWrite(LED_PIN, HIGH); // Turn on LED (AC on)
    lcd.setCursor(0, 1);
    lcd.print("AC ON HEAT");
  } else {
    digitalWrite(LED_PIN, LOW); // Turn off LED
    lcd.setCursor(0, 1);
    lcd.print("AC OFF");
  }
}