// libraries
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
// for the melody
#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978
#define NOTE_REST 0
#define TempSens A1
#define ldrPin A0
#define ServoPin 10
#define LedRed 2
#define LedGreen 4
#define LedYellow 7
#define Buzzer 9
//setting variables
int Degree = 0;
bool Duration = true;
bool direction = true;
int speed = 90;
int angle = 0;
int Temp = 0;
bool Direction = true;
// LCD Object
LiquidCrystal_I2C lcd_1(0x27,16,2);
// Servo Object
Servo servo;
//in order to convert the Dallas temperature to callcious 
const int oneWireBus = A1;          
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);
//in order to playing the melody
const int melody[] = {
  NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_B4, NOTE_A4,
  NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_REST,
  NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_B4, NOTE_A4,
  NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_REST
};
const int noteDurations[] = {
 8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 4,
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 4
};
//setup
void setup(){
  lcd_1.init();
  lcd_1.backlight();
  pinMode(TempSens, INPUT);
  pinMode(Buzzer, OUTPUT); // Set buzzer as an output
  pinMode(LedRed,OUTPUT);
  pinMode(LedGreen,OUTPUT); 
  pinMode(LedYellow,OUTPUT); 
  Serial.begin(9600);
  sensors.begin();
  servo.attach(ServoPin);  
lcd_1.setCursor(0,0);
  lcd_1.print("WELCOME");
    // Play the song
    for (int thisNote = 0; thisNote < sizeof(melody) / sizeof(int); thisNote++) {
      int noteDuration = 1000 / noteDurations[thisNote];
      tone(Buzzer, melody[thisNote], noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(Buzzer);
    }
 // turning the servo
 if (Direction){ 
   speed = 180;
  }
   servo.write(speed);
} 
//loop
void loop(){
  sensors.requestTemperatures(); 
//convert the degree
  Temp=sensors.getTempCByIndex(0);
  delay(1000);
  delay(200); // Wait before checking the LDR value again
  delay(200); // Delay between LDR readings
Direction = false;
   if (!Direction){ 
   speed = 90;
  }
  servo.write(speed);
//conditions
  if (Temp >= 42 ||Temp < 0){
    delay(500);
    lcd_1.setCursor(0,0);
    lcd_1.print("WARNING!");
    delay(200);
    lcd_1.setCursor(0,1);
    lcd_1.println("DON'T GO OUT!");
    digitalWrite(LedRed, HIGH);
    digitalWrite(LedGreen, LOW);
    digitalWrite(LedYellow, LOW);
  } 

  if (Temp < 42 && Temp > 28){
    delay(500);
    lcd_1.setCursor(0,0);
    lcd_1.print("IT'S HOT OUTSIDE");
    delay(200);
    lcd_1.setCursor(0,1);
    lcd_1.println("PUT SUNSCREEN");
    digitalWrite(LedRed, LOW);
    digitalWrite(LedGreen, LOW);
    digitalWrite(LedYellow, HIGH); 
  }  
    
   if (Temp <= 28 && Temp >= 0){
    lcd_1.setCursor(0,0);
    lcd_1.print("GOOD WEATHER!");
    delay(200);
    lcd_1.setCursor(0,1);
    lcd_1.println("HAVE FUN!");
    digitalWrite(LedRed, LOW);
    digitalWrite(LedGreen, HIGH);
    digitalWrite(LedYellow, LOW);
   } 

}