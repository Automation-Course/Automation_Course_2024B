Readme
1.	Ensure that all switches are off and execute the code from the file to the PLC.
2.	Insert the initial amount for raspberry, lemon, stabilizer, and gummy bears to their relevant places in Watch1.
3.	 Select the type of Gummygum you would like to produce:
       •	For regular Gummygum, turn Analog input 1 so that it points to numbers in the range of 0-5.
       •	For premium Gummygum, turn Analog input 1 so that it points to numbers in the range of 6-10.
4.	Turn on switch X7.
5.	After light Y0 (indicating ice cream preparation) turns off, Turn on switch X2 to transfer the raspberry and lemon ice creams to their cooling containers. If the temperature sensor indicates a temperature below 10 degrees, Turn on switch X3 to finish the cooling process.
6.	After light Y2 (indicating ice cream cooling) turns off, and after Y5 and Y6 stop flashing – turn on switch X4 to start the packaging process.
7.	For packaging each Gummygum in a package, Turn on and off switch X0. This means that to create a complete package of 7 Gummygums, the operation must be repeated 7 times.
8.	After light Y4 turns off, if you want to start another iteration of production – turn off all switches and repeat steps 3-8.
9.	At the end of the day, check the output in the Analog Output that displays the number of packages prepared during the day, in decimal units. For example, an output of 0.2 indicates that two packages, each containing seven Gummygums, were produced.
10.	Note: At any moment, the process can be stopped by turning on the emergency switch – X5!
