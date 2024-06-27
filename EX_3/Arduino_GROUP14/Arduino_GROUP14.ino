
#include <LiquidCrystal_I2C.h>  // Library for LCD
#include <NewPing.h>
#include <Servo.h>

// Pin and variables definitions
#define TRIGGER_PIN 9
#define ECHO_PIN 10
#define MAX_DISTANCE 200
#define Servo_PWM 6
#define LDR_PIN A0
#define PERSON_DISTANCE 30
#define LDR_LIGHT 60
#define LDR_DARK 200
#define LED_PIN 2

Servo MG995_Servo;
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Initialize the LCD with I2C address 0x27, 16 columns, and 2 rows
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // Initialize ultrasonic sensor

// Function to display welcome message on the LCD
void lcd_print_welcome() {
  lcd.clear();
  lcd.setCursor(0, 0); //set the writing location
  lcd.print("Welcome to      ");
  lcd.setCursor(0, 1);
  lcd.print("Your room :)    ");
}

// Function to clear the LCD display
void clean_ldc() {
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 1);
   lcd.print("                ");
  delay(2000); // Delay for 2 seconds
}

// Function to initialize pins
void init_pins() {
  pinMode(TRIGGER_PIN, OUTPUT);
}

// Function to initialize serial communication
void init_serial() {
  Serial.begin(9600);
}

// Function to read distance from the ultrasonic sensor
int read_distance() {
  unsigned int uS = sonar.ping(); // Send a ping and get the echo time in microseconds
  pinMode(ECHO_PIN, OUTPUT); 
  digitalWrite(ECHO_PIN, LOW);
  pinMode(ECHO_PIN, INPUT);
  Serial.print("Distance is : "); 
  Serial.print(uS / US_ROUNDTRIP_CM);  // Convert the echo time to distance in centimeters
  Serial.println(" CM");
  return uS / US_ROUNDTRIP_CM; 
}

// Function to read the value from the LDR sensor
int read_LDR_value() {
  int analog_val;
  Serial.print("LDR value : ");
  analog_val = analogRead(LDR_PIN);
  Serial.println(analog_val);
  return analog_val;
}

// Function to move the servo motor
void move_motor() {
  MG995_Servo.attach(Servo_PWM);
  MG995_Servo.write(180);
}

// Function to stop the servo motor
void stop_servo() {
  MG995_Servo.detach();
}

// Setup function, runs once at the start
void setup() {
  init_serial();
  lcd.init();  
  lcd.backlight();
  lcd.clear();
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}


void loop() {
  int distance;
  int ldr_value;
  distance = read_distance();
    // if person entered
  if ((distance < PERSON_DISTANCE) && (distance != 0)) {
    move_motor();
    lcd_print_welcome();
    ldr_value = read_LDR_value();
    if (ldr_value > LDR_DARK) {
      // There is no light outside
      digitalWrite(LED_PIN, HIGH);
    } else {
      digitalWrite(LED_PIN, LOW);
    }
  } else {
    stop_servo();
    clean_ldc();
    digitalWrite(LED_PIN, LOW);
  }

  delay(1000);// Delay for 1 second
}
