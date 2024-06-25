#include <Servo.h>
#include <IRremote.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define RED_LED 13
#define GREEN_LED 12
#define IR_RECEIVE_PIN 3
#define DOOR_OPEN 1
#define DOOR_CLOSED 0
#define servoPin 9

const int trig = 6;
const int echo = 7;
long totaltime;
int distance;
bool door_state = DOOR_CLOSED;

Servo servo;
LiquidCrystal_I2C lcd_1(0x27, 16, 2);
IRrecv irrecv(IR_RECEIVE_PIN);
decode_results results;

void setup() {
    lcd_1.init();
    pinMode(IR_RECEIVE_PIN, INPUT);
    servo.attach(servoPin);
    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
    servo.write(90);
    digitalWrite(RED_LED, HIGH);
    irrecv.enableIRIn();  // Start the IR receiver
    Serial.begin(9600);
}

void loop() {
    if (Distance_cm() < 5) {
        printOnScreen("Opening");
        open();
        delay(500);
        printOnScreen("Select storage");
        delay(500);
    }

    if (irrecv.decode(&results)) {
        Serial.print("IR Code: "); // Print prefix
        Serial.println(results.value); // Print the received IR code

        switch(results.value) {
            case 2253889879:  // Replace with your remote's Button 1 code
                printOnScreen("storage 1");
                // Add actions specific to Button 1 press
                break;
                
            case 400013135:  // Replace with your remote's Button 2 code
                printOnScreen("storage 2");
                // Add actions specific to Button 2 press
                break;
                
            case 2836179711:  // Replace with your remote's Button 3 code
                printOnScreen("storage 3");
                // Add actions specific to Button 3 press
                break;
                
            default:
                printOnScreen("Unknown button.");
                break;
        }
        
        irrecv.resume(); // Receive the next value
        delay(500); // debounce delay
    }
}

void printOnScreen(String print) {
    lcd_1.clear(); // Clear the LCD screen
    lcd_1.setCursor(0, 1);
    lcd_1.print(print);
    lcd_1.setBacklight(1);
    delay(500); // Wait for 500 milliseconds
}

void open() {
    Serial.println("Opening");
    servo.write(180); // Servo right-open
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    door_state = DOOR_OPEN;
    delay(1500);

    servo.write(90); // Leave the door open to allow entry or exit.
    delay(1000);
    close();
}

double Distance_cm() {
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    totaltime = pulseIn(echo, HIGH);
    distance = totaltime * 0.034 / 2;
    return distance;
}

void close() {
    servo.write(0); // Servo left-close
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    delay(1500);
    door_state = DOOR_CLOSED;
    servo.write(90);
}


