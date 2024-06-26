
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // pyshical package (lcd)
//#include <Adafruit_LiquidCrystal.h> // simulator packageג

#define servoPin  9
#define ledPinGreen 2 
#define ledPinYellow  5  
#define ledPinRed 11
#define PhotoresistorPin  A0 // the cell and 10K pulldown are connected to a0

// Servo
Servo servo;
int speed =90;
bool DirectionLeftToClosed=true;
bool DirectionAgainst90=true;

// LCD
//Adafruit_LiquidCrystal lcd(0); // simulator package
LiquidCrystal_I2C lcd(0X27,16,2);// pyshical package (lcd)

// Button
int pushButton = 4; //Variable for storing Push Button Pin Configuration
int switchStatus = 0; //Initializing variable value of switchStatus to 0

//photoresistor
int PhotoresistorValue=0; // the analog reading from the sensor divider

bool moveCurtain = false;
bool curtainClosed = false;



void setup() 
{
	Serial.begin(9600); 	
	servo.attach(servoPin);

/////// simulator package //////	
//lcd.begin(16, 2);
//lcd.setBacklight(1);

	lcd.init();// initialize the LCD

	// Turn on the blacklight and print a message.
	lcd.backlight();
	lcd.print("Hello Guest :)");

	delay(900);
	
	//Setting leds as output
	pinMode(ledPinRed, OUTPUT); 
	pinMode(ledPinGreen, OUTPUT); 
	pinMode(ledPinYellow ,OUTPUT);
	
	//Setting inputs
	pinMode(pushButton , INPUT); 
	pinMode(PhotoresistorPin,INPUT);

}
void loop() 
{
	lcd.clear(); 
	PhotoresistorValue = analogRead(PhotoresistorPin); // reads the light and translate it to number
  // 
	if ((PhotoresistorValue > 870)and(speed == 90)and(!curtainClosed)) // the curtains are open and need to be close
	{
		blinkingRed();
		lcd.print("TurnOn nightmode");
      	delay(100);
	}
	
	if ((PhotoresistorValue < 870) and (speed == 90)and (curtainClosed)) //the curtains are closed and need to be open
	{
		blinkingYellow();
		lcd.print("Morning time");
      	delay(100);
	}
	
	getButton();

	if(moveCurtain)
		moveServo();

	// prints the speed and photoresistor value to serial
	Serial.print("LDR reading = ");
	Serial.println(PhotoresistorValue);    
  Serial.print("servo speed = ");
	Serial.println(speed);
}

// blinking lights red
void blinkingRed()
{
	digitalWrite(ledPinRed,HIGH);
	delay(100);
	digitalWrite(ledPinRed,LOW);
	delay(100);
	
}

// blinking lights yellow 
void blinkingYellow()
{
	digitalWrite(ledPinYellow,HIGH);
	delay(100);
	digitalWrite(ledPinYellow,LOW);
	delay(100);
	
}

void moveServo()
{
  //increase the speed
	if (DirectionAgainst90){ // increase the speed when need close the curtians
      if(DirectionLeftToClosed){
        if(speed<120) {
		        speed +=1;
        }
      	else{
        	DirectionAgainst90=false;
       	}
      }
      // increase the speed when need open the curtians
      else{
        if(speed>60){
          speed -=1;
        }
        else{
        	DirectionAgainst90=false;
       	}
      }
    }
  //lower the speed
  else 
  {// lower the speed when need close the curtians
      if(DirectionLeftToClosed){
        if(speed>90){
          speed -=1;
        }
       	else{
        	DirectionAgainst90=true;
       	}
      }
      //lower the speed when need open the curtians
      else{
         if(speed<90){
          speed +=1;
         }
         else{
        	DirectionAgainst90=true;
       	}
      }
  }
      	
	// curtians are closed 
	if((speed==90)and (DirectionLeftToClosed))
	{
		DirectionLeftToClosed = false;
    DirectionAgainst90=true; 	
		if(!curtainClosed){
			moveCurtain=false; 
			curtainClosed = true;
      lcd.print("Curtain closed");
      delay(500);
		}
	}
  // curtians are open
	else if((speed==90)and (!DirectionLeftToClosed))
	{
		DirectionLeftToClosed = true;
    DirectionAgainst90=true;   	
		if(curtainClosed){
			curtainClosed = false;
      moveCurtain =false;
      lcd.print("Curtain opened");
      delay(500);
		}
	}
  servo.write(speed);
}

// define what happens after we press the button
void getButton()
{// when button is pressed action will occur only when change is needed  
  if(((PhotoresistorValue > 870)and(speed == 90)and(!curtainClosed)) or
    ((PhotoresistorValue < 870) and (speed == 90)and (curtainClosed))) {
  //gets the reading from the button and updates the variable
  switchStatus = digitalRead(pushButton); 
    if(switchStatus == LOW) {//If the button is not pressed, the LED will not light up
      digitalWrite(ledPinGreen, LOW);
    }
    else{
    digitalWrite(ledPinGreen, HIGH); // if the the button is pressed, the light is on
	  moveCurtain = true; 
    }
  }
}


