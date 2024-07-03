
Instructions for the operator ReadMe
Activating and initializing the controller
1. The controller must be turned on
2. Connection destination -> Connection1 -> Serial USB -> USB -> OK -> OK
3. Compile -> Rebuild All
4. Online -> Remote Operation(s)
5. STOP -> yes -> ok
6. Online -> Write to PLC
7. Press on Parameters + Program
8. Press -> Execute
9. Online -> Remote Operation(s)
10. RUN -> yes -> ok

The Gummigam production process
Enter raw material inventory values ??into Watch1.
The input variables: petel_begin, limon_begin, meyatzev_begin, gummybear_begin
Press the X7 button to start the factory working day. Once pressed, light Y7 will light up and remain lit throughout the workday as an indication that the workday is taking place, as long as there is enough raw material and the emergency button X5 is not pressed. If there is a lack of raw material or the emergency button is pressed, the Y7 light will turn off and all variables will be reset.
Select the value using the analog input (Analog Input-1) ranging from 0 to 10. In order to select a standard Gummigam case, an input between 0 and 5 must be entered. In order to choose a Gummigam-pinuk case, enter an input between 6 and 10.
Lift the X1 switch to perform the ice cream flavor preparation operation. After pressing this switch, the Y0 light will illuminate for 5 seconds.
Lift the X2 switch to perform the ice cream cooling operation. After pressing this switch, lamp Y2 will light up for 8 seconds or until temperature sensor X3 indicates a temperature of 10 degrees or less (switch X3 will be raised).
Immediately after the end of cooling the ice cream (light Y2 off), the mixing of the ingredients will take place according to the appropriate times for each type of ice cream (3 seconds for regular ice cream, 5 seconds for treat ice cream). At this point you will notice the Y5 and Y6 lights which every half a second will flash alternately.
Lift the X4 switch to start the packing process of a case that includes 7 Gummigam.
In order to pack a single cone you must pick up the X0 switch. In order to pack a complete package, the switch must be lifted 7 times in a row. When the X0 switch is raised, the Y4 light turns on and remains lit throughout the entire packaging process from the end of the first cup packaging to the end of the entire case.
In order to start manufacturing another Gumigam, you must first set off all the switches in the controller (X0, X1, X2, X4). If X3 and/or X5 are raised you must also lower them. After that, one iteration will end, all the counters will be reset (1CC, 2CC) and you will have to do all the steps from the beginning.
At the end of the working day, you will be able to notice the analog output showing the number of gummygum cases that were produced in decimal form. For example: one package will appear as follows - 0.1.
At any stage you can press the emergency button X5 if you want to stop the working day.


