A control panel using an nRF24L01 radio. 
Designed for the class [Performing
Robots](https://github.com/michaelshiloh/PerformingRobots)
but could be used in many wireless remote control applications

The board is intentionally larger than necessary to make it somewhat
ergonomic, and to provide a place for a battery pack. If you use a portable
charger (as I do) you may need to get one specifically designed for very low
power drain, otherwise they shut off when too little current is being drawn.
A key phrase is "Trickle Charging Mode" e.g.
[this](https://www.amazon.com/dp/B08LH26PFT/ref=redir_mobile_desktop?th=1).
Holes are provided for zip ties to hold the battery pack

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
  headers](https://www.adafruit.com/product/85) for all my shields
  for maximum flexibility. alternately you can uses pins only
    - 1x 10-pin header
    - 2x 8-pin headers
    - 1x 6-pin headers
    - 1x 2x3 header
