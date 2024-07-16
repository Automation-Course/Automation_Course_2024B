#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Define pin numbers for the ultrasonic sensor
const int trigPin = 6;
const int echoPin = 5;

// LCD I2C configuration
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define pin numbers for the LED, button, servo, and piezo buzzer
#define led  11         // LED connected to digital pin 11
#define inPin 9         // Button connected to digital pin 9
#define servoPin 10     // Servo connected to digital pin 10
#define servoButtonPin 7// Button connected to digital pin 8 for servo control


Servo myServo;  // Create servo object to control a servo

int buttonState = 0;          // Variable to store the current state of the LED button
int lastButtonState = 0;      // Variable to store the previous state of the LED button
int ledState = LOW;           // Variable to store the state of the LED (LOW means off)

int servoButtonState = 0;     // Variable to store the current state of the servo button
int lastServoButtonState = 0; // Variable to store the previous state of the servo button
int servoState = 0;           // Variable to store the state of the servo (0 = right, 1 = left)

unsigned long previousMillis = 0;
const long interval = 500;    // Interval for checking distance
String lastStatus = "";       // Variable to store the last status displayed on the LCD

// Function to get distance from ultrasonic sensor
long getDistance() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1; // Convert duration to distance in cm
  return distance;
}

void setup() {
  // Initialize the serial monitor for debugging
  Serial.begin(9600);
  
  // Initialize LCD I2C
  lcd.begin(16, 2);
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();

  // Set up the ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Set up the button, LED
  pinMode(inPin, INPUT_PULLUP); // Set LED button pin as input with internal pull-up resistor
  pinMode(servoButtonPin, INPUT_PULLUP); // Set servo button pin as input with internal pull-up resistor
  pinMode(led, OUTPUT);         // Set LED pin as output
  
  digitalWrite(led, ledState);  // Initialize the LED state


  // Attach the servo to the servo pin
  myServo.attach(servoPin);
  myServo.write(90); // Initialize the servo to 90 degrees (middle position)
}

void loop() {
  // Button and LED logic
  buttonState = digitalRead(inPin); // Read the state of the LED button value

  // Check if the LED button state has changed
  if (buttonState != lastButtonState) {
    // If the LED button state has changed to LOW, toggle the LED
    if (buttonState == LOW) {
      ledState = !ledState; // Toggle the LED state
      digitalWrite(led, ledState); // Update the LED with the new state
    }
    delay(50); // Debounce delay
  }

  // Save the current LED button state as the last state for the next loop
  lastButtonState = buttonState;

  // Servo button logic
  servoButtonState = digitalRead(servoButtonPin); // Read the state of the servo button value

  // Check if the servo button state has changed
  if (servoButtonState != lastServoButtonState) {
    // If the servo button state has changed to LOW, toggle the servo position and piezo buzzer
    if (servoButtonState == LOW) {
      if (servoState == 0) {
        myServo.write(180); // Move the servo to 180 degrees (left)
        delay(3000); // Wait for 500 milliseconds
        myServo.write(90); 
        servoState = 1;
      } else {
        myServo.write(0); // Move the servo to 0 degrees (right)
        delay(3000); // Wait for 500 milliseconds
        myServo.write(90); 
        servoState = 0;
      }
    }
    delay(50); // Debounce delay
  }

  // Save the current servo button state as the last state for the next loop
  lastServoButtonState = servoButtonState;

  // Measure the distance using the ultrasonic sensor
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    long distance = getDistance();
    String status;

    // Determine the status based on the distance
    if (distance > 10) {
      status = "Room Empty";
    } else {
      status = "Room Occupied";
    }

    // Update the LCD only if the status has changed
    if (status != lastStatus) {
      lastStatus = status;
      lcd.clear();
      lcd.print(status);
    }
  }
}