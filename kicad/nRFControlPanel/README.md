A control panel using an nRF24L01 radio. 
Designed for the class [Performing
Robots](https://github.com/michaelshiloh/PerformingRobots)
but could be used in many wireless remote control applications

Bill of Materials
- 2x8 socket for nRF24L01 radio (I think I'm using the plus version but it
  might work with others)
- 1x16 socket for 16x2 LCD panel. This is a very common component used with
  Arduino e.g. from [Adafruit](https://www.adafruit.com/product/181). It uses
  a 4 bit parallel bus along with two control lines (RS and EN). It has a
  backlight (requires current limiting resistor) and a contrast control
  (requires potentiometer)
- 1K ohm 1/4 watt resistor
- 10K potentiometer
- Header pins to fit Arduino. I like using [feedthrough
  headers](https://www.adafruit.com/product/85) in all cases alternately you
  can uses pins only
    - 1x 10-pin header
    - 2x 8-pin headers
    - 1x 6-pin headers
    - 1x 2x3 header
