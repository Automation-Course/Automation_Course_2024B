

README
# Group 5 
# A smart hotel room based on Ultrasonic and Photoresistor sensors. The system control over the light intensity and the fan at the room. The fan will start working once recognizing object that located 30 cm or less. The light will start working at night (while the room is dark). 
# User manual - setting up your Arduino for programming
Install Arduino drivers from the Arduino website if your system doesn't recognize the Arduino automatically. This is often needed for Windows.
Connect the Arduino Uno to your computer using a USB cable.
Launch the Arduino IDE on your computer.
Navigate to 'Tools > Board' and select 'Arduino Uno'.
Go to 'Tools > Port' and choose the port labeled 'Arduino Uno'.
To use the system, open your customized code and press the 'Upload' button to compile and transfer it to the Arduino controller.
If you encounter errors, open 'Sketch > Include Library > Manage Libraries...' in the IDE, search for the needed library, and click 'Install'.
The Potentiometer (rotation button) is now on the leftmost position. Turn it to the right all the way to get a value of your choice that if the measured light intensity in the room is below it, the red LED light will shine at a high intensity.
If the room is dark regarding the value you set, the Led light will start lighting in HIGH mode. Otherwise, the Led light remains off ("LOW" mode). 
If there is someone in the room, located 30 cm or less than the FAN, the FAN System will start working. Otherwise, the Fan remains off. 
At every moment, if there is someone inside the room, The distance between him and the fan shown on the LCD screen in centimeters. 


