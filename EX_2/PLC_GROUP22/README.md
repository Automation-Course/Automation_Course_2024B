# PLC Ice Cream Project

This project models an ice cream making process for a day, with operations until the end of the day or until the materials are exhausted. The system handles two types of ice cream: Pinuk and Regular.

## Requirements
Integrated Development Environment (IDE) capable of programming and running PLC programs, such as GX Works2.

## Usage
* Load the PLC program file into your IDE.
* **Start the Process**: Turn on `X007` (START_DAY) and ensure `X005` (EMERGENCY) is not engaged.
* **Load Materials**: Input quantities for Petel, Limon, Meyatzev, and Gumi into `D2000`, `D2100`, `D2200`, and `D2300`.
* **Make Ice Cream**: Press `X1` (START_MAKING), select the ice cream type (`M11` for Regular, `M12` for Pinuk) based on `Analog Input 1`.
* **Verify Materials**: Ensure sufficient materials are available. If not, the process will halt.
* **Cooling Process**: Press `X2` to start cooling. Cooling is indicated by `Y2`.
* **Mixing Process**: Ice cream is mixed (`Y5` and `Y6` alternate) after cooling.
* **Packing Process**: Press `X4` to start packing. The unit counter increments with each unit packed.
* **End of Day**: The process stops at the end of the day or if materials run out. `M27` indicates the end of the day.

## Variables
A detailed table of variables used in the PLC program is provided, including descriptions of each variable's purpose. Please refer to the attached file for more information.

## Exceptions
### General Exceptions
* Ensure all sensors and actuators are properly connected and calibrated.
* Follow the assumptions detailed in the attached file.

### Specific to Ice Cream Making Process
* Input measurements for materials (Petel, Limon, Meyatzev, Gumi) must be entered by the user.
* Ensure sufficient material is available for the selected ice cream type, if not it will stop.

## Authors
* Carolina Fain
* Ohad Snir
* Hagar Shifman
* Yonatan Seleznev
