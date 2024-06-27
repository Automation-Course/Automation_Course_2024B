#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 4  // Data wire connected to Arduino digital pin 4

OneWire oneWire(ONE_WIRE_BUS);  // Setup a oneWire instance to communicate with any OneWire devices
DallasTemperature sensors(&oneWire);  // Pass oneWire reference to Dallas Temperature sensor

LiquidCrystal_I2C lcd(0x27, 16, 2); // Initialize LCD object with I2C address 0x20 (32 decimal), 16 columns, 2 rows
Servo servo;             // Create a servo object

int ledPin = 13; // Pin connected to the LED
int servoPin = 9;    // Pin connected to the servo motor
int buttonPin = 12;  // Pin connected to the push button

bool servoActive = false;    // Flag to track servo state
bool buttonPressed = false; // Flag to track button press

void setup() {
  Serial.begin(115200);
  lcd.init(); // Initialize the LCD
  lcd.backlight(); // Turn on the backlight
  pinMode(ledPin, OUTPUT); // Set the LED pin as an output
  pinMode(buttonPin, INPUT_PULLUP);// Set the button pin as an input with pull-up resistor
  servo.attach(servoPin);  // Attach the servo to its pin
  sensors.begin();  // Initialize the Dallas Temperature sensor
  lcd.setCursor(0, 0);
  lcd.print("Welcome To The");
  lcd.setCursor(0, 1);
  lcd.print("Jacuzzi");
  delay(1000);
  lcd.clear(); // Clear the LCD screen
}

void loop() {

  // Request temperatures from Dallas Temperature sensor
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);  // Get temperature in degrees Celsius

  // Display temperature on LCD
  lcd.setCursor(0, 0);
  lcd.print("Temperature");
  lcd.setCursor(0, 1);
  lcd.print(temperatureC, 1); // Display temperature with one decimal place
  lcd.print(" C");
  
  // Check if button is pressed
  if (digitalRead(buttonPin) == LOW && !buttonPressed) {
    buttonPressed = true;  // Set button pressed flag
    servoActive = !servoActive;  // Toggle servo state
  } else if (digitalRead(buttonPin) == HIGH) {
    buttonPressed = false; // Reset button pressed flag
  }

  // Control Servo based on temperature
  if (temperatureC > 31.0) {
    servoActive = false; // Stop servo if temperature exceeds 40°C
    
  }

  if (servoActive) {
  servo.write(350);  
} else {
    servo.write(0);   // Move servo to 0 degrees position
}

  
 // Control LED based on temperature
   if (temperatureC > 30.0) {
     digitalWrite(ledPin, HIGH); // Turn on LED if temperature exceeds 36°C
   } else {
     digitalWrite(ledPin, LOW); // Turn off LED otherwise
   }
  delay(10); // Delay for one second before taking another reading
}