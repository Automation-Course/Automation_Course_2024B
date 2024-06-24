#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Pin definitions
#define buttonPin 2  // Button pin
#define ledPin 13    // LED pin
#define buzzerPin 12 // Buzzer pin
#define servoPin 9   // Servo pin

// Initialize LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);
// Initialize Servo
Servo servo;

// Notes for "Twinkle Twinkle Little Star"
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494

// Melody and note durations
int melody[] = { NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4,
                 NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4 };

int noteDurations[] = { 4, 4, 4, 4, 4, 4, 2,   // "Twinkle"
                        4, 4, 4, 4, 4, 4, 2 }; // "Twinkle"

// Variables for button state management
bool isLightsOn = false;  // Flag to track if lights and LCD are on
bool lastButtonState = LOW;

void setup() {
  lcd.init();           // Initialize LCD
  lcd.backlight();      // Turn on LCD backlight
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  servo.attach(servoPin);
  Serial.begin(9600);
}

void loop() {
  bool currentButtonState = digitalRead(buttonPin);

  if (currentButtonState != lastButtonState) {
    if (currentButtonState == HIGH) {
      if (!isLightsOn) {  // Lights and LCD are currently off
        isLightsOn = true;
        Serial.println("push to start");
        digitalWrite(ledPin, HIGH); // Turn on LED
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Welcome to the");
        lcd.setCursor(0, 1);
        lcd.print("room Ms Sheetrit");

        playTheme();  // Play "Twinkle Twinkle Little Star"
        spinServo();  // Activate servo
      } else {  // Lights and LCD are currently on
        isLightsOn = false;
        Serial.println("push to end");
        digitalWrite(ledPin, LOW);  // Turn off LED
        servo.write(0);             // Reset servo position
        lcd.clear();
      }
    }
    lastButtonState = currentButtonState;
  }
}

void playTheme() {
  for (int thisNote = 0; thisNote < 14; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(buzzerPin, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(buzzerPin);
  }
}

void spinServo() {
  servo.write(180);  // Rotate servo to 180 degrees
  delay(1000);      // Delay for 1 seconds with servo at 180 degrees
  servo.write(0);    // Return to 0 degrees
}
