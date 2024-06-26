
#include <Servo.h>
#include <OneWire.h>
#include <DallasTemperature.h>
// pins
#define RED_LED 5
#define GREEN_LED 6
#define SERVO 2
#define ONE_WIRE_BUS 3
#define SWITCH_AUTO_CONTROL 4
#define SWITCH_MANUAL 8

#include <LiquidCrystal_I2C.h>       // Library for LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address 0x27, 16 column and 2 rows




#define TEMPERATURE_SWITCH_VALUE 26.0


double temrature = 0;
int auto_state = 1;    // 1 - AUTO , 0 = MANUAL
int manual_state = 1;  //AC on or off. 1 on 0 off

Servo myservo;  

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);

// init serial comunication
void init_serial() {
  Serial.begin(9600);
}

void servo_open() {
  int pos = 0;
  if (myservo.read() != 180) {
    for (pos = 0; pos <= 180; pos += 1) {  // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);
    }
  }
}

void servo_close() {
  int pos = 0;
  if (myservo.read() != 0) {
    for (pos = 180; pos >= 0; pos -= 1) {  // goes from 180 degrees to 0 degrees
      myservo.write(pos);                  // tell servo to go to position in variable 'pos'
    }
  }
}
// turn on AC + servo
void AC_on() {
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, LOW);
  Serial.println("AC ON");
}

// turn off AC + servo
void AC_off() {
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);
  Serial.println("AC OFF");
}




void init_pins() {
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(SWITCH_AUTO_CONTROL, INPUT);
  pinMode(SWITCH_MANUAL, INPUT);

  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);
}


double read_temprature() {
  double temrature;
  sensors.requestTemperatures();
  Serial.print("Celsius temperature: ");
  temrature = sensors.getTempCByIndex(0);
  Serial.print(temrature);
  Serial.println("");

  return temrature;
}
int read_auto_control_switch(int state, int pin_num) {

  if (digitalRead(pin_num) == HIGH) {
    while (digitalRead(pin_num) == HIGH) {
      delay(1);
    }
    if (state == 1) {
      return 0;
    } else {
      return 1;
    }
  } else {
    return state;
  }
}



void lcd_print_welcome() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Welcome to");
  lcd.setCursor(0, 1);
  lcd.print("BGU HOTEL :) ");
  delay(2000);
  lcd.clear();
}

void lcd_print_row0(char string[]) {
  lcd.setCursor(0, 0);
  lcd.print(string);
}
void lcd_print_row1(char string[]) {
  lcd.setCursor(0, 1);
  lcd.print(string);
}
void setup() {
  // put your setup code here, to run once:
  init_serial();
  init_pins();
  sensors.begin();
  myservo.attach(SERVO);
  lcd.init();  // initialize the lcd
  lcd.backlight();
  lcd_print_welcome();
}

void print_state_for_debug(int auto_state) {
  if (auto_state == 1) {
    Serial.println("mode : automatic");
  } else {
    Serial.println("mode : manual");
  }
}



void loop() {
  char row0[16];
  char row1[16];
  row0[0] = 0;
  row1[0] = 0;

  temrature = read_temprature();

  sprintf(row0, "TEMP : %s", String(temrature, 3).c_str());
  lcd_print_row0(row0);

  if (auto_state == 1) {

    sprintf(row1, "MODE : Automatic");
    if (temrature > TEMPERATURE_SWITCH_VALUE) {
      AC_on();
      servo_open();
    } else {
      AC_off();
      servo_close();
    }
  } else {

    if (manual_state == 1) {
      sprintf(row1, "MODE : manual   ");
      AC_on();
      servo_open();

    } else {
      AC_off();
      servo_close();
    }
  }
  lcd_print_row1(row1);
  auto_state = read_auto_control_switch(auto_state, SWITCH_AUTO_CONTROL);
  manual_state = read_auto_control_switch(manual_state, SWITCH_MANUAL);
  print_state_for_debug(auto_state);
  delay(10);
}
