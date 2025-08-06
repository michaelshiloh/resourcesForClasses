### nRF_Servo_Mega

![](documentation/nRF_servo_Mega_schematic.jpg)
[PDF schematic](documentation/nRF_servo_Mega_schematic.pdf)

This shield 
is mean to sit on a Mega (which means using the SPI pins on the ICSP header)
with the Adafruit Music Maker Shield.

Pin usage:

SPI on Mega (used by both Music Maker Shield and nRF radio)
| Arduino Pin |
| --- |
| 51 |
| 52 |
| 53 |

Music Maker Shield

| SPI Signal Name | Description | Arduino Pin |
| --- | --- | --- |
| MCS | VS1053 chip select pin | 7 |
| DCS | VS1053 data select pin | 6 |
| CCS | SD Card chip select pin | 4 |
| DREQ | VS1053 data request interrupt pin | 3 |

#### Revisions

Rev 0.1
- Replace motor numbers with pin numbers
- Improve marking of servo pin assignments
- Extend board past the 36 pin connector
- Add voltage and polarity to screw terminals
