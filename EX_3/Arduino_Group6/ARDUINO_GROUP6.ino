
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#define led13 13 // port number of the yellow led
#define led7 7 // port number of the red led
int Piezo = 8; // port number of the piezo
Servo servo_12;
int servo = 12; // port number of the servo
const int pingPin = 2;
const int echoPin = 3;
long duration, cm = 0;

void setup()
{
  pinMode(servo, INPUT);
  servo_12.attach(12);
  pinMode(Piezo, OUTPUT);
  pinMode(led13, OUTPUT);
  pinMode(led7, OUTPUT);
  Serial.begin(9600); 
  lcd.begin();
  lcd.setBacklight(1); 
  Serial.println("Start Operation") ;
  pinMode(pingPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

void loop()
{
  // duration = pulseIn(echoPin, HIGH);
  ultraSonic();
  printCmDistance(cm);
  if (cm < 30) 
  { // which means that motion is detected 
    Serial.println("Motion detected!");
    servo_12.write(0); // makes the servo stop moving 
    digitalWrite(led13, LOW); // makes the yellow led turn off 
    digitalWrite(led7, HIGH); // makes the red led turn on 
    lcd_emergency(); // function that makes the lcd write "Warning!!!"
    tone(Piezo,1000); // start making noise 
    delay(1000);
    noTone(Piezo);
  }
  else { // which means no motion is detected
    Serial.println("Area Clean") ;
    lcd_normal(); // function that makes the lcd write "Gumigam Refrigerator"
    servo_move(); 
    digitalWrite(led13, HIGH);
    digitalWrite(led7, LOW);
    noTone(Piezo); // stop making noise  
  }
}

void lcd_normal(){ // make the lcd screen write "Gumigam Refrigerator" when area clean
  lcd.setCursor(0,0);
  lcd.print("Gumigam "); 
  lcd.setCursor(4,1); 
  lcd.print("Refrigerator"); 
}

void lcd_emergency(){ // make the lcd screen write "Warning!!!" when motion detected
  lcd.setCursor(0,0);
  lcd.print("Warning!!!");
  lcd.setCursor(4,1); 
  lcd.print ("                           ");
}

void servo_move(){ // make the servo start rotating
  Serial.println("Servo start moving"); 
  servo_12.write(90);
  delay(15);
}

long microsecondsToCm(long microseconds){
  return (microseconds)/29/2;
}

void printCmDistance(long cm){
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
}

long ultraSonic(){
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCm(duration);
  return cm;
}