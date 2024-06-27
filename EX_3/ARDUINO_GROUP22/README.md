### README

# Arduino Project - Smart Hotel Room Control

## Introduction
This project aims to create a smart hotel room control system using Arduino. The system provides a comfortable and private experience for guests by allowing them to control room facilities with the press of a button. The system includes a motorized curtain, an LED light, and a real-time room occupancy display using an ultrasonic sensor and an LCD screen.

## System Components
- **Arduino Uno**
- **Ultrasonic Sensor (HC-SR04)**
- **LCD Screen (I2C)**
- **Servo Motor**
- **LED Light**
- **Push Buttons**
- **Breadboard and Jumper Wires**

## Usage
1. **Power the Arduino**: Connect the Arduino to a power source.
2. **Observe the LCD screen**: The screen will display "Room Empty" after initialization.
3. **Control the curtain**: Use the button connected to pin 7 to open and close the curtain (3 second for opening or closing the curtain).
4. **Control the LED**: Use the button connected to pin 9 to toggle the LED on and off.
5. **Check room occupancy**: The LCD screen will display "Room Occupied" or "Room Empty" based on the readings from the ultrasonic sensor.

## Requirements
- **Arduino IDE**
- **LiquidCrystal_I2C library**
- **Servo library**
- **Power source for Arduino**
- **Basic electronic components** (breadboard, jumper wires, resistors)

## Authors
* Carolina Fain
* Ohad Snir
* Hagar Shifman
* Yonatan Seleznev
