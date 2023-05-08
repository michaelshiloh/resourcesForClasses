/*
   Bidirectional communication using the nRF24L01 radio module 
   
   These sketches require the RF24 library by TMRh20
   Documentation here: https://nrf24.github.io/RF24/index.html

   change log

   08 May 2023 - ms - initial entry based on rf24PerformingRobotsTemplate/
*/

// nRF24L01 uses SPI which is fixed on pins 11, 12, and 13.
// It also requires two other signals
// (CE = Chip Enable, CSN = Chip Select Not)
// Which can be any pins. We use pins 9 and 10 as follows:

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

// needed for radio.printPrettyDetails();
//#include <printf.h>

// See note in rf24Handshaking about address selection
// Basically, there are some bit patterns to be avoided
// below are some examples that seem to work well.
// Note that 'addr' is just a variable that is then
// merged into the full address
// Note also that there are two separate addresses
// One for transmitting and one for receiving

// Channel and address allocation:
// addr = 0x76
// addr = 0x73
// addr = 0x7C
// addr = 0xC6
// addr = 0xC3
// addr = 0xCC
// addr = 0x33
const byte addr = 0x76;             // change as per the above assignment
const int RF24_CHANNEL_NUMBER = 0;  // change as per the above assignment

// Do not make changes here
const byte xmtrAddress[] = { addr, addr, 0xC7, 0xE6, 0xCC };
const byte rcvrAddress[] = { addr, addr, 0xC7, 0xE6, 0x66 };

const int RF24_POWER_LEVEL = RF24_PA_LOW;

// global variables
uint8_t pipeNum;
unsigned int totalTransmitFailures = 0;

struct DataStruct {
  uint8_t firstByte;
  uint8_t secondByte;
};
DataStruct data;

void setupRF24Common() {

  // RF24 setup
  if (!radio.begin()) {
    Serial.println(F("radio  initialization failed"));
    while (1)
      ;
  } else {
    Serial.println(F("radio successfully initialized"));
  }

  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(RF24_CHANNEL_NUMBER);
  radio.setPALevel(RF24_POWER_LEVEL);
}

void rf24SendData() {

  // The write() function will block
  // until the message is successfully acknowledged by the receiver
  // or the timeout/retransmit maxima are reached.
  int retval = radio.write(&data, sizeof(data));

  // For debugging; display data in whatever
  // format is most useful for you
  Serial.print(F("first byte = "));
  Serial.print(data.firstByte, BIN);
  Serial.print(F(" second byte = "));
  Serial.print(data.secondByte, BIN);

  Serial.print(F(" ... "));
  if (retval) {
    Serial.println(F("success"));
  } else {
    totalTransmitFailures++;
    Serial.print(F("failure, total failures = "));
    Serial.println(totalTransmitFailures);
  }
}

void setup() {
  Serial.begin(9600);

  // needed for radio.printPrettyDetails();
  // printf_begin();

  setupRF24Common();
}

void beATransmitter() {
  radio.openWritingPipe(xmtrAddress);
  radio.openReadingPipe(1, rcvrAddress);
  radio.stopListening();

  // radio.printPrettyDetails();
  Serial.println(F("I am a transmitter"));
}

void beAReceiver() {
  radio.openWritingPipe(rcvrAddress);
  radio.openReadingPipe(1, xmtrAddress);
  radio.startListening();

  // radio.printPrettyDetails();
  Serial.println(F("I am a receiver"));
}

void loop() {

  // Check for incoming data,
  // and if there is data, read it,

  beAReceiver();
  if (radio.available(&pipeNum)) {
    radio.read(&data, sizeof(data));
    Serial.print(F("message received Data = "));
    Serial.print(F("firstByte = "));
    Serial.print(data.firstByte, BIN);
    Serial.print(F(" secondByte = "));
    Serial.print(data.secondByte, BIN);
  }

  // Send some data, but not too often

  if (!(millis() % random(10) * 1000)) {
    Serial.println("time to transmit");
    data.firstByte = random(256);
    data.secondByte = (uint8_t) millis();
    beATransmitter();
    rf24SendData();
  }
}
