# arduino-weather-station
An Arduino based weather station project, still in development. Project name and license terms are subject to change in the future.

## Components
At the moment, this is the list of physical components used in building this circuit.
- (1) Arduino UNO
- (1) Protoboard
- (1) DHT11 temperature and humidity sensor
- (1) LCD 1602A (or any other 16-pin interface LCD based on the Hitachi HD44780 driver)
- (1) 10 kΩ potentiometer
- (1) 10 kΩ resistor
- (1) 220Ω resistor or an equivalent combination of parellel resistors
- Optional: male-to-female jumper wires
- Optional: male-to-male jumper wires
- Optional: 2.54mm single-row male pin headers
- Optional: soldering iron
- Optional: solder

## Dependencies
This project uses the following dependencies. For convenience, install these libraries from your Arduino IDE, and allow the installation of transitive dependencies:
- LiquidCrystal by Arduino, Adafruit: https://github.com/arduino-libraries/LiquidCrystal
- DHT sensor library by Adafruit: https://github.com/adafruit/DHT-sensor-library

## Running
Once the circuit is fully assembled, verify and upload the sketch to the Arduino UNO from the Arduino IDE. The display should then display a "Loading..." message for a few seconds, then the label "Weather Station" will show up, along with the last temperature reading. To verify that the DHT11 sensor is functioning, you may open the Serial Monitor in the Arduino IDE to confirm that it is working properly.
Turn the potentiometer knob to control the LCD contrast.

## Wiring
- Unless you already have a soldered LCD, or an alternative module to plug its pins into the protoboard, **you may have to solder a strip of pin headers to the LCD connector slots** using solder and a soldering iron.
- The diagram shows an upside down DHT sensor: the DHT sensor color might vary according to your model. Also, carefully review the diagram to make sure you wire each sensor pin correctly (tip: in Fritzing, scroll over each pin to see where it should go).

![Wiring diagram of the circuit](/assets/fritzing-view.png)
