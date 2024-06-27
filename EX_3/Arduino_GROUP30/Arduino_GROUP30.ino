#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <IRremote.hpp>

// Define pins
#define RECV_PIN 11
#define SERVO_PIN 9
#define LED_PIN 2
#define BUTTON_PIN 7

// Define IR remote button codes
#define BUTTON_SPEED1 0x45 // Code for button 1
#define BUTTON_SPEED2 0x46 // Code for button 2
#define BUTTON_SPEED3 0x47 // Code for button 3

// Initialize components
Servo servo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

int angle = 0; // Variable to store the servo motor angle
bool increasing = true; // Variable to track the direction of servo movement
int delayTime = 15; // Initial delay time for servo movement
bool ledState = false; // Variable to track LED state
bool buttonPressed = false; // Variable to track the button state
int mode =1; // Variable to track the mode

void setup() {
    pinMode(LED_PIN, OUTPUT); // Set the LED pin as output
    pinMode(BUTTON_PIN, INPUT_PULLUP); // Set the button pin as input with internal pull-up resistor
    digitalWrite(LED_PIN, ledState ? HIGH : LOW); // Initialize LED state

    servo.attach(SERVO_PIN); // Attach the servo motor to the specified pin

    lcd.init(); // Initialize the LCD
    lcd.backlight(); // Turn on the LCD backlight
    lcd.print("Servo Control"); // Print an initial message to the LCD

    Serial.begin(9600); // Initialize serial communication speed at 9600 bps
    IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK); // Start the IR receiver

    Serial.println(F("IR Receiver is ready"));
}

void loop() {
    // Handle IR remote input
    if (IrReceiver.decode()) {
        
        // Check which button was pressed and adjust delayTime accordingly
        switch (IrReceiver.decodedIRData.command) {
            case BUTTON_SPEED1:
                delayTime = 15; // Set speed 1
                mode =1;
                Serial.println(F("MODE 1"));

                break;
            case BUTTON_SPEED2:
                delayTime = 10; // Set speed 2
                mode =2;
                Serial.println(F("MODE 2"));
                break;
            case BUTTON_SPEED3:
                delayTime = 5; // Set speed 3
                mode =3;
                Serial.println(F("MODE 3"));
                break;
        }
        IrReceiver.resume(); // Receive the next value
    }

    // Handle push button input
    if (digitalRead(BUTTON_PIN) == LOW) { // Check if the button is pressed
    
        if (!buttonPressed) { // Check if the button was not already pressed
            Serial.println(F("Button Pressed"));
            ledState = !ledState; // Toggle LED state
            digitalWrite(LED_PIN, ledState ? HIGH : LOW); // Update LED state
            buttonPressed = true; // Set buttonPressed to true to indicate the button press has been handled
            delay(50); // Debounce delay
        }
    } else {
        buttonPressed = false; // Reset buttonPressed when the button is released
    }

    // Move the servo back and forth between 0 and 90 degrees
    if (increasing) {
        angle += 10; // Increase angle by 10 degrees per iteration for faster movement
        if (angle >= 90) {
            increasing = false;
        }
    } else {
        angle -= 10; // Decrease angle by 10 degrees per iteration for faster movement
        if (angle <= 0) {
            increasing = true;
        }
    }
    servo.write(angle); // Set the servo to the current angle

    printScreen("mode: " + String(mode)); // Display current speed on the LCD
    delay(delayTime); // Use the adjustable delay time for servo updates
}

void printScreen(String print) {
    lcd.clear(); // Clear the LCD screen
    lcd.setCursor(0, 0); // Set the cursor to the beginning of the first row
    lcd.print(print); // Print the specified string on the LCD
    lcd.setBacklight(1); // Turn on the LCD backlight
}
