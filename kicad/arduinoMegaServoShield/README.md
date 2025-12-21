### nRF_Servo_Mega

![](documentation/arduinoMegaServoShield.jpg
[PDF schematic](documentation/arduinoMegaServoShield.pdf)

Simple Arduino Mega shield which provides as many connections to servo motors
or other 3-pin devices (such as NeoPixels) with an independent +V supply

Be aware of pins which might be used for other purposes

Music Maker Shield

(why is the first column labled SPI?)
| SPI Signal Name | Description | Arduino Mega Pin |
| --- | --- | --- |
| MCS | VS1053 chip select pin | 7 |
| DCS | VS1053 data select pin | 6 |
| CCS | SD Card chip select pin | 4 |
| DREQ | VS1053 data request interrupt pin | 3 |

SPI

| SPI Signal Name | Arduino Mega Pin |
| --- | --- |
| CIPO | 50 |
| COPI | 51 |
| SCK | 52 |
| CS | 53 |

I2C (also known as Wire or 2Wire)

| I2C Signal Name | Arduino Mega Pin |
| --- | --- |
| SDA | 20 |
| SCL | 21 |

Serial 

| Serial Signal Name | Arduino Mega Pin |
| --- | --- |
| RX | 0 |
| TX | 1 |

#### Revisions

#### Assembly instructions
##### Assembly order
1. servo pins
1. Stacking headers
1. Screw terminal
1. ICSP header
1. 470 uFD caps

(Note that the order of the instructions and video below are slightly
different - I don't think it makes much of a difference.)

##### Assembly instructions
nRF Servo Mega Shield [video](https://youtu.be/EMkqwKK7xOQ)

1. Prepare many sets of header pins, each with 3 positions. 
    <img src="documentation/nRF_servo_Mega_assembly_cuttingPins.jpg" width="400">
    <img src="documentation/nRF_servo_Mega_assembly_headerPins.jpg" width="400">
    Insert into positions
   D16-D21.
   Solder one pin, straighten, and
   then solder the rest of the pins. You may find it easier to do one header
   at a time instead of trying to do all 6 at once like I did.
    <img src="documentation/nRF_servo_Mega_assembly_headerPinsInstalled.jpg" width="400">
1. From the bag of feed-through headers, remove six 5 position headers and one
   10 position header. Return the rest to the bag.
    Solder one pin, straighten, then solder the rest. It is very important to
    get these to line up properly so don't solder the rest of the pins until
    the header is straight.
1. Install the feed through header that is two rows of 3 pins. **Note that
   this goes in the opposite direction i.e. the pins face up and the socket
   faces down**. Solder and straighten.
1. Install the 470 uFD electrolytic capacitor. 
    Note that this component **is polarized** so you have to install it in
    the right direction. The grey stripe must go into the hole with the white
    semicircle.
   Cut the excess leads right down to the solder. Discard the cut of portion
   so that it doesn't cause a short circuit
1. Install the screw terminal. Make sure that the openings face the edge of
   the board. Solder. These pins are quite thick and the hole is quite big, so
   keep feeding solder until the hole fills up.
