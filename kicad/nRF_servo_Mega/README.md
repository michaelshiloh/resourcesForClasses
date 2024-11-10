### nRF_Servo_Mega

![](documentation/nRF_servo_Mega_schematic.jpg)

This shield 
is mean to sit on a Mega (which means using the SPI pins on the ICSP header)
with the Adafruit Music Maker Shield.

Pin usage:

SPI on Mega (used by both Music Maker Shield and nRF radio)
51
52
53

Music Maker Shield
SPI
MCS - VS1053 chip select pin - Digital #7
DCS - VS1053 data select pin - Digital #6
CCS - SD Card chip select pin - Digital #4
DREQ - VS1053 data request interrupt pin - connected to digital #3
