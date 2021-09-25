/*
   Example using the nRF24L01 radio module to communicate 
   between two Arduinos,
   the transmitter is connected to some pushbuttons
   the receiver is connected to a motor driver
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
const int fwdPin = 3;

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
int data = left | fwd | right;
    if (data) {
      Serial.print( "sending data = " );
      Serial.println(data);
      radio.write(&data, sizeof(data)) ;
    }
}
