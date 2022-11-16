/*
   Example using the nRF24L01 radio module to communicate
   between two Arduinos,
   the transmitter is connected to two momentary switches
   the receiver is connected to two LEDs

   Both sketches are present in this file; first the transmitter
   The receiver is included as a comment below

   These sketches require the RF24 library by TMRh20
*/


// Transmitter

// Pin usage
//
// The switches are on pins 2 and 4:
const int SWITCH1PIN = 2;
const int SWITCH2PIN = 4;

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
RF24 radio(CEPIN, CSNPIN);  // CE, CSN

#include <printf.h>


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
const byte address[6] = { 0x33, 0x36, 0xC7, 0xE6, 0xCC, 0xE3 };
// const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  printf_begin();


  pinMode(SWITCH1PIN, INPUT);
  pinMode(SWITCH2PIN, INPUT);

  // RF24 setup
  if (!radio.begin()) {
    Serial.println("radio  initialization failed");
    while (1)
      ;
  } else {
    Serial.println("radio successfully initialized");
  }
  radio.openWritingPipe(address);  //destination address
  radio.setPALevel(RF24_PA_MIN);   // min or max
  radio.stopListening();           //This sets the module as transmitter


  radio.printPrettyDetails();
  while (1)
    ;
}
void loop() {

  int left = B00000000;
  if (digitalRead(SWITCH1PIN) == HIGH) {
    left = B00000001;
  }
  int right = B00000000;
  if (digitalRead(SWITCH2PIN) == HIGH) {
    right = B00000010;
  }


  int data = left | right;
  if (data) {
    Serial.print("sending data = ");
    Serial.println(data);

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
    radio.write(&data, sizeof(data));
  }
}


/* Receiver

  // Pin usage
  //
  // The LEDs are on pins 2 and 4:
  const int LED1PIN = 2;
  const int LED2PIN = 4;

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

  void setup() {
  Serial.begin(9600);

  pinMode(LED1PIN, OUTPUT);
  pinMode(LED2PIN, OUTPUT);

  // RF24 setup
  if (!radio.begin()) {
    Serial.println("radio  initialization failed");
    while (1)
      ;
  } else {
    Serial.println("radio successfully initialized");
  }
  radio.openReadingPipe(0,address);  //destination address
  radio.setPALevel(RF24_PA_MIN);   // min or max
  radio.startListening();           //This sets the module as transmitter
  }
  void loop() {
  uint8_t pipeNum;
  if (radio.available(&pipeNum))  //Looking for the data.
  {
    int data;

    Serial.print("data available on pipe ");
    Serial.println(pipeNum);

    radio.read(&data, sizeof(data));  //Reading the data
    Serial.print("data = ");
    Serial.println( data);

    switch (data) {
      case 0:
        digitalWrite(LED1PIN, LOW);
        digitalWrite(LED2PIN, LOW);
        break;
      case 1:
        digitalWrite(LED1PIN, HIGH);
        break;

      case 2:
        digitalWrite(LED2PIN, HIGH);
        break;

      case 3:
        digitalWrite(LED1PIN, HIGH);
        digitalWrite(LED2PIN, HIGH);
        break;
    }
    delay(5);
  }
  }
*/