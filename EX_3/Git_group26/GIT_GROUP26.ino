#include <Wire.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
// Define pins for ultrasonic sensor
#define TRIG_PIN 5
#define ECHO_PIN 6

// Create servo object
Servo servo;
// Define pin for servo motor
#define SERVO_PIN 3
bool Direction = true;
int angle = 0;
int speed = 90;
long duration=0;
long distance=0;
bool guestPresent = false;

// Define pin for LED
#define LED_PIN 2



// song

#define REST 0
#define NOTE_C4  261
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

// Define the melody (only the chorus)
int melody[] = {
  REST, REST, REST, NOTE_DS4, 
  NOTE_E4, REST, NOTE_FS4, NOTE_G4, REST, NOTE_DS4,
  NOTE_E4, NOTE_FS4,  NOTE_G4, NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_B4,   
  NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_E4, NOTE_D4, 
  NOTE_E4, REST, REST, NOTE_DS4,
  
  NOTE_E4, REST, NOTE_FS4, NOTE_G4, REST, NOTE_DS4,
  NOTE_E4, NOTE_FS4,  NOTE_G4, NOTE_C5, NOTE_B4, NOTE_G4, NOTE_B4, NOTE_E5,
  NOTE_DS5   
};

// Define the duration of each note
int noteDurations[] = {
  2, 4, 8, 8, 
  4, 8, 8, 4, 8, 8,
  8, 8,  8, 8, 8, 8, 8, 8,   
  2, 16, 16, 16, 16, 
  2, 4, 8, 4,
  
  4, 8, 8, 4, 8, 8,
  8, 8,  8, 8, 8, 8, 8, 8,
  1 
};



// Define pin for BUZZER
#define BUZZER_PIN 9
int currentNote = 0;
bool song= false;



void setup() {
   servo.attach(SERVO_PIN);
  // pinMode(TRIG_PIN, OUTPUT);
 pinMode(TRIG_PIN, OUTPUT);
 pinMode(ECHO_PIN, INPUT);
 pinMode(LED_PIN, OUTPUT);
 // Initialize the buzzer pin as an output
  pinMode(BUZZER_PIN, OUTPUT);
 // initialize the LCD
 lcd.init();
 Serial.begin(9600);
}




void loop() {

  // Measure the distance
 digitalWrite(TRIG_PIN, LOW);
 delayMicroseconds(2);
 digitalWrite(TRIG_PIN, HIGH);
 delayMicroseconds(10);
 digitalWrite(TRIG_PIN, LOW);
 duration = pulseIn(ECHO_PIN, HIGH);
 distance = (duration*0.034)/2; // Calculate distance
 Serial.print("The distance IS: ");
 Serial.println(distance);



 if (distance <= 10) {///////////////////// && distance != 0
 Direction = true;
 song= true;
 guestPresent = true;
 Serial.println("There is Guest. open door");
speed = 100;
servo.write(speed); //opening the door
 lcd.setBacklight(1);
 lcd.print("WELCOME!");
 delay(2000); // Keep WELCOME for 2 seconds
 lcd.clear();

 }

 else { //If the sensor does not detect movement
    if (Direction){ // continue opening the door
 angle +=1;
 speed = 100;
 if (angle >= 3){//If the door is fully opened the motor stops moving
 Direction = false;
 speed = 90; // stops moving
 angle = 3;
 servo.write(speed);
 }
 }
 if (angle <= 3) { // Check if the door is not already closed
 if (!Direction && guestPresent ){ //If there is no motion detection and the door is also open
 Serial.println("The guest get in. Closing door.");
 angle -=1;
 speed = 80;
 if (angle <= -3){//If the door is fully closed the motor stops moving
 guestPresent = false;
 speed = 90; // stops moving
 angle = 0;
 }
 }
 servo.write(speed);
 lcd.setBacklight(0);
 }
 }
 if (song){ 
  digitalWrite(LED_PIN, HIGH);
  if (currentNote < sizeof(melody) / sizeof(melody[0])) {
    // Play the current note
    int noteDuration = 1000 / noteDurations[currentNote];
    tone(BUZZER_PIN, melody[currentNote], noteDuration);
    delay(noteDuration * 1.7); // Adjust this multiplier to control tempo
    noTone(BUZZER_PIN); // Stop playing the note

    // Move to the next note
    currentNote++;
    
  }

 else {
    // Reset currentNote to play the song from the beginning
    digitalWrite(LED_PIN, LOW);
    currentNote = 0;
    song= false;
  }
 }



}