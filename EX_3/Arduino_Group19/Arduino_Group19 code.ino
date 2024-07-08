#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Create servo object
Servo myServo;

// Create LCD object
LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16 chars and 2 line display

// Define pin numbers and variables
const int servoPin = 3;
const int ledRed = 2;
const int soundWaveOutPin = 10;
const int soundWaveInPin = 9;
long distance, duration;
const int buzzer = 8;
long startTime;


// Notes definitions
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

// Melody for "The Lion Sleeps Tonight"
int tempo = 250;
int melody[] = {
  NOTE_F4, 4, NOTE_G4, 4, NOTE_A4, 8, NOTE_G4, 4, NOTE_A4, 8,
  NOTE_AS4, 4, NOTE_A4, 4, NOTE_G4, 8, NOTE_F4, 4, NOTE_G4, 8,
  NOTE_A4, 4, NOTE_C4, 8, NOTE_C4, 4, NOTE_C4, 8, NOTE_C4, 4,
  NOTE_C4, 1, //1st ending
  NOTE_F4, 4, NOTE_G4, 4, NOTE_A4, 8, NOTE_G4, 4, NOTE_A4, 8, //repeats from 1
  NOTE_AS4, 4, NOTE_A4, 4, NOTE_G4, 8, NOTE_F4, 4, NOTE_G4, 8,
  NOTE_A4, 4, NOTE_C4, 8, NOTE_C4, 4, NOTE_C4, 8, NOTE_C4, 4,
  NOTE_C4, -2,  REST, -8, NOTE_A4, 16, //2nd ending
  NOTE_A4, -8, NOTE_A4, 16, NOTE_A4, -8, NOTE_A4, 16, NOTE_A4, -8, NOTE_A4, 16, NOTE_A4, -8, NOTE_A4, 16,
  NOTE_AS4, -8, NOTE_AS4, 16, NOTE_AS4, -8, NOTE_AS4, 16, NOTE_AS4, -8, NOTE_AS4, 16, NOTE_AS4, -8, NOTE_AS4, 16,
  NOTE_A4, -8, NOTE_A4, 16, NOTE_A4, -8, NOTE_A4, 16, NOTE_A4, -8, NOTE_A4, 16, NOTE_A4, -8, NOTE_A4, 16,
  NOTE_G4, -8, NOTE_G4, 16, NOTE_G4, -8, NOTE_G4, 16, NOTE_G4, -8, NOTE_G4, 16, NOTE_G4, -8, NOTE_G4, 16,
  NOTE_A4, -8, NOTE_A4, 16, NOTE_A4, -8, NOTE_A4, 16, NOTE_A4, -8, NOTE_A4, 16, NOTE_A4, -8, NOTE_A4, 16,
  NOTE_AS4, -8, NOTE_AS4, 16, NOTE_AS4, -8, NOTE_AS4, 16, NOTE_AS4, -8, NOTE_AS4, 16, NOTE_AS4, -8, NOTE_AS4, 16,
  NOTE_A4, -8, NOTE_A4, 16, NOTE_A4, -8, NOTE_A4, 16, NOTE_A4, -8, NOTE_A4, 16, NOTE_A4, -8, NOTE_A4, 16,
  NOTE_G4, -8, NOTE_G4, 16, NOTE_G4, -8, NOTE_G4, 16, NOTE_G4, -8, NOTE_G4, 16, NOTE_G4, -8, NOTE_G4, 16,
  NOTE_F4, 4, NOTE_G4, 4, NOTE_A4, 8, NOTE_G4, 4, NOTE_A4, 8,
  NOTE_AS4, 4, NOTE_A4, 4, NOTE_G4, 8, NOTE_F4, 4, NOTE_G4, 8,
  NOTE_A4, 4, NOTE_G4, 4, NOTE_F4, 4, NOTE_A4, 4,
  NOTE_G4, 1,
  NOTE_C5, 4, NOTE_A4, 4, NOTE_G4, 8, NOTE_A4, 4, NOTE_C5, 8,
  NOTE_AS4, 4, NOTE_A4, 4, NOTE_G4, 8, NOTE_F4, 4, NOTE_G4, 8,
  NOTE_A4, 4, NOTE_G4, 4, NOTE_F4, 4, NOTE_A4, 4,
  NOTE_G4, 1,
  NOTE_C5, 1, NOTE_C5, 4, NOTE_AS4, 8, NOTE_C5, 8, NOTE_AS4, 2,
  NOTE_A4, 4, NOTE_C4, 8, NOTE_C4, 4, NOTE_C4, 8, NOTE_C4, 4,
  NOTE_C4, 1,
  REST, 4, NOTE_A4, 8, NOTE_G4, 8, NOTE_F4, 8, NOTE_E4, 8, NOTE_D4, 8, NOTE_C4, 8,
  NOTE_D4, 1,
  REST, 4, NOTE_A4, 8, NOTE_G4, 8, NOTE_F4, 8, NOTE_E4, 8, NOTE_D4, 8, NOTE_C4, 8,
  NOTE_D4, 1,
  NOTE_F4, 4, NOTE_G4, 4, NOTE_A4, 8, NOTE_G4, 4, NOTE_A4, 8,
  NOTE_AS4, 4, NOTE_A4, 4, NOTE_G4, 8, NOTE_F4, 4, NOTE_G4, 8,
  NOTE_A4, 4, NOTE_G4, 4, NOTE_F4, 4, NOTE_A4, 4,
  NOTE_G4, 1,
  NOTE_C5, 4, NOTE_A4, 4, NOTE_G4, 8, NOTE_A4, 4, NOTE_C5, 8,
  NOTE_AS4, 4, NOTE_A4, 4, NOTE_G4, 8, NOTE_F4, 4, NOTE_G4, 8,
  NOTE_A4, 4, NOTE_G4, 4, NOTE_F4, 4, NOTE_A4, 4,
  NOTE_G4, 1
};

// Note durations: 4 = quarter note, 8 = eighth note, etc.
int noteDurations[] = {
  4, 4, 8, 4, 8,
  4, 4, 8, 4, 8,
  4, 4, 8, 4, 8,
  4, 8, 4, 8, 4,
  1, 4, 4, 8, 4,
  8, 4, 4, 8, 4,
  8, 4, 4, 8, 4,
  8, 4, 4, 8, 4,
  1, 4, 4, 8, 4,
  8, 4, 4, 8, 4,
  8, 4, 4, 8, 4,
  8, 4, 4, 8, 4,
  8, 4, 4, 8, 4,
  1, 4, 4, 8, 4,
  8, 4, 4, 8, 4,
  8, 4, 4, 8, 4,
  8, 4, 4, 8, 4,
  8, 4, 4, 8, 4,
  1, 4, 4, 8, 4,
  8, 4, 4, 8, 4,
  8, 4, 4, 8, 4,
  8, 4, 4, 8, 4,
  8, 4, 4, 8, 4,
  1, 4, 4, 8, 4,
  8, 4, 4, 8, 4,
  8, 4, 4, 8, 4,
  8, 4, 4, 8, 4,
  8, 4, 4, 8, 4,
  1, 4, 4, 8, 4,
  8, 4, 4, 8, 4,
  8, 4, 4, 8, 4,
  8, 4, 4, 8, 4,
  8, 4, 4, 8, 4,
  1, 4, 4, 8, 4,
  8, 4, 4, 8, 4,
  8, 4, 4, 8, 4,
  8, 4, 4, 8, 4,
  8, 4, 4, 8, 4,
  1, 4, 4, 8, 4,
  8, 4, 4, 8, 4,
  8, 4, 4, 8, 4,
  8, 4, 4, 8, 4,
  8, 4, 4, 8, 4,
  1
};

void setup() {
  // Initialize the LCD screen
  lcd.init();
  lcd.backlight(); // Turn on the backlight

  // Initialize pins
  pinMode(soundWaveOutPin, OUTPUT);
  pinMode(soundWaveInPin, INPUT);
  pinMode(ledRed, OUTPUT);

  // Attach the servo
  myServo.attach(servoPin);

  // Initialize Serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Update distance measurement
  ultraSonic();
  calcDist();

  // Check distance and switch modes accordingly
  if (distance <200) {
    guestArrive(); // Guest is nearby
  } else {
    noGuest(ledRed); // Return to normal mode
  }
 

  // Delay to avoid excessive updating (adjust as needed)
  delay(500);
}

void ultraSonic() {
  digitalWrite(soundWaveOutPin, LOW);
  delayMicroseconds(2);
  digitalWrite(soundWaveOutPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(soundWaveOutPin, LOW);
}

void calcDist() {
  duration = pulseIn(soundWaveInPin, HIGH);
  distance = duration * 0.034 / 2;
}

void guestArrive() {
  welcomeDisplay();
  lightOn(ledRed);
  turnOnAC();
  startTime=millis();
  playLionSleepsTonight();
  delay(1000);
}

void noGuest(int led) {
  turnOffAC(); // No motion for the servo
  lightOff(ledRed); // Turn off the LED
  welcomeDisplaOff();
}


void welcomeDisplay() {
  if (distance <50) {
    lcd.clear();
    lcd.print("Hello! Enjoy");
    lcd.setCursor(0, 1);
    lcd.print("The Jungle :)");
  }
  else{
    lcd.clear();
  }
  }

void welcomeDisplaOff() {
  lcd.clear();
  }

  
void lightOn(int led) {
  if (distance <50) {
    digitalWrite(led, HIGH); // turn the led on
  }
  else{
      digitalWrite(ledRed, LOW); // Turn off the LED
  }
}

void lightOff(int led) {
  digitalWrite(ledRed, LOW); // Turn off the LED
}

void turnOnAC() {
  myServo.write(180);
}

void turnOffAC() {
  myServo.write(90); // No motion for the servo
}


// Function to play a note
void playNote(int note, int duration) {
  tone(buzzer, note, duration);
  delay(duration*1.3); // Delay for note duration plus 30% for pacing
  noTone(buzzer);
  }
    
// Function to play the melody
void playLionSleepsTonight() {
    for (int thisNote = 0; thisNote < sizeof(melody)/sizeof(melody[0]); thisNote++) {
        ultraSonic();
        calcDist();
        if (distance >50 || millis()-startTime >=7000 ) {
            break;
        }
        int noteDuration = 1000 / noteDurations[thisNote];
        playNote(melody[thisNote], noteDuration/1.5);
    }
}