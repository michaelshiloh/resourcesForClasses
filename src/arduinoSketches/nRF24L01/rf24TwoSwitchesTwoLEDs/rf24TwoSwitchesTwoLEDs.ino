/*
   Example using the nRF24L01 radio module to communicate
   between two Arduinos,
   the transmitter is connected to two momentary switches
   the receiver is connected to two LEDs

   Both sketches are present in this file; first the transmitter
   The receiver is included as a comment below

   These sketches require the RF24 library by TMRH20
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
RF24 radio(CEPIN, CSNPIN);                // CE, CSN

// Byte of array representing the address.
// This is the address where we will send the data.
// This should be same on the receiving side.
const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);

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
}
void loop() {

  int left = B00000000;
  if (digitalRead(SWITCH1PIN) == HIGH) {
    left = B00000001;
  }
  int right = B00000000;
  if (digitalRead(SWITCH1PIN) == HIGH) {
    right = B00000010;
  }


  int data = left | right;
  if (data) {
    Serial.print( "sending data = " );
    Serial.println(data);
    radio.write(&data, sizeof(data)) ;
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
  radio.openWritingPipe(address);  //destination addres
  radio.setPALevel(RF24_PA_MIN);   // min or max
  radio.stopListening();           //This sets the module as transmitter
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
      case B00000000:
        digitalWrite(LED1PIN, LOW);
        digitalWrite(LED2PIN, LOW);
        break;
      case B00000001:
        digitalWrite(LED1PIN, HIGH);
        break;

      case B00000010:
        digitalWrite(LED2PIN, HIGH);
        break;

      case B00000011:
        digitalWrite(LED1PIN, HIGH);
        digitalWrite(LED2PIN, HIGH);
        break;
    }
    delay(5);
  }
  }
*/
