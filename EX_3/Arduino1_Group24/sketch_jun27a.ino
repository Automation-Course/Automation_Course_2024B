>include <Wire.h#
>include <LiquidCrystal_I2C.h#
>include <Servo.h#
 עובד לא אם x3F0-ל לשנות נסה //; LiquidCrystal_I2C lcd(0x27, 16, 2)
define led4 4 // port number of the green led#
define led7 7 // port number of the red led#
int Piezo = 8; // port number of the piezo
 ;Servo servo_12
int servo = 12; // port number of the servo
{ )(void setup
 (servo(attach12._servo ;// חיבור הסרוו לפין 12
;pinMode(Piezo, OUTPUT) 
 ;pinMode(led4, OUTPUT) 
 ;pinMode(led7, OUTPUT) 
;pinMode(2, INPUT) 
 ;)9600 (Serial.begin 
;)(lcd.init 
 ;)(lcd.backlight 
 ;)0 ,0(lcd.setCursor 
;lcd.print("Start Operation") 
delay(2000); // wait for 2 seconds to show the initial message 
}
{ )(void loop
8
 ;)2(int pir = digitalRead 
if (pir == HIGH) { // motion detected 
 ;Serial.println("Motion detected!") 
servo_12.write(0); // makes the servo stop moving 
digitalWrite(led4, LOW); // makes the green led turn off 
digitalWrite(led7, HIGH); // makes the red led turn on 
"!lcd_emergency(); // function that makes the lcd write "Movement detected near your room 
tone(Piezo, 1000); // start making noise 
 ;)10000(delay 
else { // no motion detected } 
;Serial.println("Area Clean") 
"!lcd_normal(); // function that makes the lcd write "Welcome to our hotel 
servo_move(); // make the servo start rotating 
 ;digitalWrite(led7, LOW) 
 ;digitalWrite(led4, HIGH) 
noTone(Piezo); // stop making noise 
} 
}
void lcd_normal() { // make the lcd screen write "Welcome to our hotel!" when area clean
;)(lcd.clear 
 ;)0 ,0(lcd.setCursor 
;lcd.print("Welcome to our hotel") 
}
void lcd_emergency() { // make the lcd screen write "Movement detected near your room!" when motion 
detected
;)(lcd.clear 
 ;)0 ,0(lcd.setCursor 
;lcd.print("Movement detected") 
9
 
}
void servo_move() { // make the servo start rotating
;Serial.println("Servo start moving") 
 ;)90(servo_12.write 
 ;)15(delay 
}