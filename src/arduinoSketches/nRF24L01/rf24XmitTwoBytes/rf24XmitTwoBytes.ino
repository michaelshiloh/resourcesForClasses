/*
   Example using the nRF24L01 radio module to communicate
   between two Arduinos,
   the transmitter is connected to some pushbuttons
   the receiver is connected to a motor driver

   Based on rf24Xmit, this example sends two bytes
   The first byte contains the status of up to 8 switches
   and could be used e.g. to control motors
   The second byte could be used e.g. to tell which
   pattern to display on the NeoPixel matrix
*/

// Pin usage
// nRF24L01 uses SPI which is fixed on pins 11, 12, and 13.
// It also requires two other signals
// (CE = Chip Enable, CSN = Chip Select Not)
// Which can be any pins:

const int CEPIN = 9;
const int CSNPIN = 10;

// In summary,
// nRF 24L01 pin    Arduino pin   name
//          1                     GND
//          2                     3.3V
//          3             9       CE
//          4             10      CSN
//          5             13      SCLK
//          6             11      MOSI/COPI
//          7             12      MISO/CIPO

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(CEPIN, CSNPIN);                // CE, CSN

// Byte of array representing the address.
// This is the address where we will send the data.
// This should be same on the receiving side.
const byte address[6] = "00001";

// Pins for the pushbuttons
const int leftPin = 2;
const int rightPin = 4;
const int fwdPin = 8;

// Code for different expressions on the NeoPixel matrix
const int neoPixelSmile = 0b00000100;
const int neoPixelFrown = 0b00000110;

void setup() {
  Serial.begin(115200);

  boolean retval = radio.begin();   //Starting the Wireless communication
  Serial.println(retval);
  radio.openWritingPipe(address);  //destination addres
  radio.setPALevel(RF24_PA_MIN);   // min or max
  radio.stopListening();           //This sets the module as transmitter
}

void loop() {

  int left = digitalRead(leftPin) << 2;
  int fwd = digitalRead(fwdPin) << 1;
  int right = digitalRead(rightPin) << 0;

  // Now create the NeoPixel code
  // NeoPixel data is the upper byte so it must be shifted into position
  // Smile or frown is determined by whether we're turning left or right
  int npData = 0;
  if (right) {
    npData = neoPixelSmile << 8;
  }
  if (left) {
    npData = neoPixelFrown << 8;
  }

  // Combine all the switch data and the NeoPixel data
  int data = left | fwd | right | npData;
  if (data) {
    Serial.print( "sending data = " );
    Serial.println(data, BIN);
    radio.write(&data, sizeof(data)) ;
  }
}
