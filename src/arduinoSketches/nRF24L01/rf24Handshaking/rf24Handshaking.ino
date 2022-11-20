/*
   Example using the nRF24L01 radio module to communicate
   between two Arduinos with much increased reliability following
   various tutorials, conversations, and studying the nRF24L01 datasheet
   and the library reference.

   This code is for both transmitter and receiver. 
   Behavior is determined by a jumper on the receiver.   
   
   The transmitter has two LEDs indicating correct data or errors

   These sketches require the RF24 library by TMRh20
   Documentation here: https://nrf24.github.io/RF24/index.html

   nRF24L01 datasheet here: 
   https://www.sparkfun.com/datasheets/Components/
	 SMD/nRF24L01Pluss_Preliminary_Product_Specification_v1_0.pdf

   Much useful information in
   https://www.youtube.com/watch?v=Z7_Cy66Vnrc

	 Good discussion of selecting good addresses:
	 http://maniacalbits.blogspot.com/2013/04/
	 rf24-addressing-nrf24l01-radios-require.html


   change log

   18 Nov 2022 - ms - initial entry based on rf24TwoSwitchesTwoLEDs
   18 Nov 2022 - ms - slower SPI speed (third parameter in constructor)
                    - separate channels by 10 e.g. 
                      setChannel(86); // default is 76
                    - slower on-air datarate e.g.
                      radio.setDataRate(RF24_250KBPS); 
                    - low (but not minimum) power level e.g.
                      radio.setPALevel(RF24_PA_LOW); 
                    - changed address to avoid bad bit patterns                                        
   
*/

// Pin usage
//
const int JUMPERPIN = 2;  // connect to ground for receiver
const int REDLEDPIN = 3;
const int GREENLEDPIN = 4;  // successful handshake
const int REDSWITCHPIN = 5;
const int GREENSWITCHPIN = 6;

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
//RF24 radio(CEPIN, CSNPIN, 125000L);  // CE, CSN
RF24 radio(CEPIN, CSNPIN);  // CE, CSN


#include <printf.h>  // for debugging


// Byte of array representing the address.
// This is the address where we will send the data.
// This should be same on the receiving side.
//
// Avoid addresses where all bits are the same
// (e.g. 00000 or FFFFF, because it looks like noise)
// or alternate (e.g. 01010101 or 1010101, because it looks like the preamble)
//
// Good addresses need alternating short (2-4) sequences of the same
// bit value e.g.  110001110011
// or in hex the nibbles 0x3, 0x6, 0x7, 0xC, 0xE
// (these are only 4 bits so combine)
//
// values that start or end with 1 bit can be combined
// e.g. 0x38 or 0x1C
//
// e.g.
const byte xmitAddress[] = { 0x33, 0x36, 0xC7, 0xE6, 0xCC };
const byte recvAddress[] = { 0x33, 0x36, 0xC7, 0xE6, 0x66 };


// global variables
boolean iAmTransmitter = true;  // jumper makes us the receiver
uint8_t pipeNum;

struct DataStruct {
  uint8_t green;
  uint8_t red;
};
DataStruct data;

void setup() {
  Serial.begin(9600);
  printf_begin();

  pinMode(JUMPERPIN, INPUT_PULLUP);
  iAmTransmitter = digitalRead(JUMPERPIN);  // jumper on receiver sets this to false

  // Receiver has LEDs
  pinMode(REDLEDPIN, OUTPUT);
  pinMode(GREENLEDPIN, OUTPUT);

  // Transmitter has switches
  pinMode(REDSWITCHPIN, INPUT_PULLUP);
  pinMode(GREENSWITCHPIN, INPUT_PULLUP);

  // RF24 setup
  if (!radio.begin()) {
    Serial.println("radio  initialization failed");
    while (1)
      ;
  } else {
    Serial.println("radio successfully initialized");
  }

  // Here's most of the special stuff (apart from constructor above):
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(86);

  radio.setPALevel(RF24_PA_LOW);

  if (iAmTransmitter) {
    radio.openWritingPipe(xmitAddress);
    radio.openReadingPipe(1, recvAddress);
  } else {
    radio.openWritingPipe(recvAddress);
    radio.openReadingPipe(1, xmitAddress);
  }

  radio.printPrettyDetails();

  if (iAmTransmitter) {  // I am transmitter so transmit until receiver responds

    boolean receivedReply = false;
    while (!receivedReply) {

      data.red = digitalRead(REDSWITCHPIN);
      data.green = digitalRead(GREENSWITCHPIN);

      Serial.print("XMTR: in setup(), waiting for receiver, sending red = ");
      Serial.print(data.red);
      Serial.print(" green = ");
      Serial.println(data.green);

      radio.stopListening();  // Become a transmitter
      radio.write(&data, sizeof(data));

      receivedReply = checkForMessage();
      delay(200);  // not too often
    }
  }  // end of I am a transmitter
}  // end of setup

// checks to see whether we have received a message
// returns true if we have received a message and data is valid
//         false otherwise
boolean checkForMessage() {

  //Serial.println("checking for a message");
  radio.startListening();  // Become a receiver

  if (radio.available(&pipeNum)) {
    radio.read(&data, sizeof(data));  //Reading the data
    Serial.print("message received red = ");
    Serial.print(data.red);
    Serial.print(" green = ");
    Serial.println(data.green);
    return true;
  }
  return false;
}

void loop() {

  if (!iAmTransmitter) {  // I am receiver so wait for a message

    radio.startListening();  // Become a receiver
    while (!(radio.available(&pipeNum))) {
      Serial.println("RCVR: waiting for message");
      delay(10);  // check for messgaes pretty often
    }

    radio.read(&data, sizeof(data));  //Reading the data
    Serial.print("RCVR: received red = ");
    Serial.print(data.red);
    Serial.print(" green = ");
    Serial.println(data.green);

    digitalWrite(GREENLEDPIN, data.green);
    digitalWrite(REDLEDPIN, data.red);

    // now simply send it back
    radio.stopListening();
    radio.write(&data, sizeof(data));

  } else {  // We are the transmitter

    data.red = digitalRead(REDSWITCHPIN);
    data.green = digitalRead(GREENSWITCHPIN);
    Serial.print("XMTR: sending red = ");
    Serial.print(data.red);
    Serial.print(" green = ");
    Serial.println(data.green);

    // The write() function will block
    // until the message is successfully acknowledged by the receiver
    // or the timeout/retransmit maxima are reached.
    // In the current (default?) configuration, the max delay here is 60-70ms.
    //
    // Returns
    //   true if the payload was delivered successfully
    //        and an acknowledgement (ACK packet) was received.
    //        If auto-ack is disabled, then any attempt to transmit
    //        will also return true (even if the payload was not received).
    //   false if the payload was sent but was not acknowledged
    //        with an ACK packet.
    //        This condition can only be reported
    //        if the auto-ack feature is on.
    radio.stopListening();
    radio.write(&data, sizeof(data));

    // now wait for a reply and turn on the appropriate LED
    boolean receivedReply = false;
    while (!receivedReply) {
      radio.startListening();  // Become a receiver
      receivedReply = checkForMessage();
      //Serial.print("XMTR: receivedReply = ");
      //Serial.println(receivedReply);
      delay(10);  // can check for messages pretty often
    }
  }  // end of we are the transmitter
}  // end of loop
