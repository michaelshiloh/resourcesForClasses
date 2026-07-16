# Arduino_Shield_RC_Controller_v3

Version 3 of the Arduino shield that is used to control the robots in
Performing Robots. It uses the nRF24L01+ radio as an interface, and pairs with
either
* mega_nRF_feedthrough
* nRF_servo_Mega

## Basic idea:
- Read from switches
- Display label on LCD
- When the transmit button is pressed, send the index of the selected item
- Report success or failure (based on ack from receiver)

## Circuit

### Image of device

### Schematic

### PCB layout

PCB designed with Kicad 10

## Assembly

The design is intended for assembly by JLCPCBA. I used -- plugin to generate
the BOM and placement file, but I had to hand tweak certain things:

# Notes

# Bugs and things to do
- For some reason the footprint of the 10K pot comes out upside down, so I
  left this off the JLCPCBA BOM. It would be nice to get to the bottom of this
- The tantalum capacitor shows up backwards on the initial drawing generated
  by JLCPCB, but then it shows up with the correct orientation in the
  engineering drawings (if you select that you want to verify the
  manufacturing steps before they proceed) and is assembled correctly. It
  would be nice to get to the bottom of this.
- Have JLCPCBA install:
    - Arduino header pins and socket (board side: bottom)
    - nRF24L01+ socket (board side: top)
    - LCD socket (don't have them install the LCD - I have  ton of them) (board side: top)
- Decide whether I need the large cap, and if so have JLCPCBA install it  (board side: top)
