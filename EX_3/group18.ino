#include <LiquidCrystal_I2C.h>
#include <Servo.h>

int seconds = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);

int pir_sensor = 0;
int pir_sensor_map = 0;
unsigned long previousMillis = -1000000000000;
const long interval = 5000;
bool pirState = false;

// Gas sensor & Buzzer
#define gasSensorPin A1
const int smoke_allowed = 100; // threshold
int current_smoke;
#define buzzer 4 // Pin where the buzzer is connected

// Servo motor
Servo circulation;
#define servoPin 9 // Define the pin for the servo sprayer motors

// fade led
#define redled 5
#define yellowled 3
int counter = 0;
bool light = true;
bool redLight = true;


void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.backlight();  // Turn on the backlight
  Serial.println("LCD initialized");
  displayMessage("Dance if you", "wanna enter!"); // default
  // Initialize the servo motor:
  circulation.attach(servoPin);
  circulation.write(0); // Start position
  // Initialize the leds:
  pinMode(redled, OUTPUT);
  pinMode(yellowled, OUTPUT);
}

void loop() {
  print_on_lcd(); // Check for motion and display message
  smoke_alarm_check(); // Check for smoke and trigger alarm if needed
  activate_circulation(); // Turn on the circulation
  lights();
}

void activate_circulation() {
      circulation.write(45);
      delay(500); // Wait 1 second (adjust as needed)
}


void print_on_lcd() {
  pirState = movement_pir();
  if (pirState == true || (millis() - previousMillis) < interval) {
    displayMessage("Welcome!", "relax & enjoy");
    if (pirState == true) {
      previousMillis = millis(); // Store the time when motion was detected
    }
  } else {
    displayMessage("Dance if you", "wanna enter!");
  }
}

void displayMessage(String line1, String line2) {
  lcd.setBacklight(1);
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
  delay(1000);
  lcd.clear();
}



bool movement_pir() {
  pir_sensor = analogRead(A2);
  Serial.print("Mapped PIR Sensor Value: ");
  Serial.println(pir_sensor_map);
  pir_sensor_map = map(pir_sensor, 0, 1023, 0, 255);
  if (pir_sensor_map > 85) {
    Serial.println("Motion Detected!");
    delay(100);
    return true;
  }
  return false;
}


void lights() {
  counter= counter+25;
  if (counter == 250){
    counter = 0;
    light = !light;
  }
  if (light) {
    analogWrite(redled, counter); // turn LED on
    analogWrite(yellowled, 0); // turn LED on
    delay(10);
  } else {
    analogWrite(yellowled, counter); // turn LED on
    analogWrite(redled, 0); // turn LED on
    delay(10);
  }
}


void smoke_alarm_check() {
  current_smoke = analogRead(gasSensorPin);
  Serial.print("Current Amount of Gas: ");
  Serial.println(current_smoke);

  if (current_smoke < smoke_allowed) {
    Serial.println("ALL GOOD");
    noTone(buzzer); // No smoke detected

  } else {
    Serial.println("SMOKE! SOS!");
    tone(buzzer, 180); // Smoke detected, activate buzzer
  }
}
