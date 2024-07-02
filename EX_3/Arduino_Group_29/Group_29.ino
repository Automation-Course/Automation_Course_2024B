// Include necessary libraries
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// LCD setup
LiquidCrystal_I2C lcd_1(0x27, 16, 2); // Adjust I2C address and LCD size for your setup

// Initial variables
int portion = 10;    // Initial portion size set to 10 (adjusted from 100 for testing)
const int trigPin = 12; // Pin for ultrasonic sensor trigger
const int echoPin = 10; // Pin for ultrasonic sensor echo
Servo myservo;        // Servo motor object
int led = 6;          // Pin for LED indicator
const int buttonPin = 2; // Pin for push button

unsigned long lastPour = 0; // Timestamp of last portion served
unsigned long Pours = 0;    // Counter for the number of portions served

void setup() {
    // Set up pins
    pinMode(buttonPin, INPUT); // Push button pin
    pinMode(led, OUTPUT);
    myservo.attach(9); // Attach servo to pin 9
    Serial.begin(9600); // Start serial communication

    // Set up ultrasonic sensor pins
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    // Initialize LCD
    lcd_1.init();
    lcd_1.backlight();
    lcd_1.clear();
}

void loop() {
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    long duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    int distance = duration * 0.034 / 2;
    // Check if push button is pressed or distance sensor detects object within 50cm and 150cm
    if (portion > 0) {
      if ((digitalRead(buttonPin) == HIGH || (distance > 5 && distance < 15))) {
          lcd_1.clear();
          lcd_1.print("Let's Drink Beer");
          delay(2000);

          digitalWrite(led, HIGH); // Turn on LED during portion serving
          myservo.write(180);      // Open servo to pour portion
          lcd_1.clear();
          lcd_1.print("Cup Start, Wait");
          delay(2000); // Wait for portion serving simulation
          myservo.write(90);
          delay(1000);
          myservo.write(0); // Close servo after portion served
          lcd_1.clear();
          // Decrease portion count
          delay(2000);
          myservo.write(90);
          digitalWrite(led, LOW); // Turn off LED after portion served
          lcd_1.print("Cup Filled, Take");
          delay(1000);
          portion--;
          lcd_1.clear();
          lcd_1.print("Thank You!");
          delay(1000);
          // Display portion count on LCD
          lcd_1.clear();
          lcd_1.print("Portions left: ");
          lcd_1.print(portion);

          Serial.print("Portions left: ");
          Serial.println(portion); // Print remaining portions

          Pours++; // Increment Pours counter
          delay(5000); // Delay for stability, simulates the cup being taken
          // Record last portion serving time
          lastPour = millis();
          lcd_1.clear();
      }
    }
    else {
        delay(2000);
        lcd_1.clear();
        lcd_1.print("Beer tank empty."); // Display message for empty beer tank
        Serial.println("Beer tank empty."); // Print message to serial monitor
        delay(2000);
        // You can add additional actions here if needed
    }

    // Ensure LED is off when not pouring
    digitalWrite(led, LOW);
     // Clear LCD at the end of loop
}
