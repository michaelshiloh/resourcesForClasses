
/*
   Example using the nRF24L01 radio module to communicate
   between two Arduinos,
   the transmitter is connected to some pushbuttons
   the receiver is connected to a motor driver

   These sketches require the RF24 library by TMRH20
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
RF24 radio(CEPIN, CSNPIN);  // CE, CSN


// Byte of array representing the address.
// This is the address where we will send the data.
// This should be same on the receiving side.
const byte address[6] = "00001";

// Motor controller pins
const int rightDirPin = 4;
const int rightPWMPin = 5;
const int leftDirPin = 7;
const int leftPWMPin = 6;

const int neoPixelSmile = 0b00000100;
const int neoPixelFrown = 0b00000110;


void setup() {

  // Motor controller pins
  pinMode(rightDirPin, OUTPUT);
  pinMode(leftDirPin, OUTPUT);

  Serial.begin(115200);

  // RF24 setup
  if (!radio.begin()) {
    Serial.println("radio  initialization failed");
    while (1)
      ;
  } else {
    Serial.println("radio successfully initialized");
  }
  radio.openReadingPipe(0, address);  // Destination address
  radio.setPALevel(RF24_PA_MIN);      // Min or max
  radio.startListening();             // sets  module as receiver
}
void loop() {
  uint8_t pipeNum;
  if (radio.available(&pipeNum))  //Looking for the data.
  {
    int data;

    //Serial.print("data available on pipe ");
    //Serial.println(pipeNum);

    radio.read(&data, sizeof(data));  //Reading the data
    Serial.print("\ndata = ");
    Serial.println( data, BIN);

    // split data into neoPixelData and switchData
    int switchData = data & 0b0000000011111111;
    int neoPixelData = (data & 0b1111111100000000) >> 8;

    if (neoPixelData) {
      controlNeoPixel(neoPixelData);
    }

    switch (switchData) {
      case 0b00000001:                        // if (data == 0b00000001) {
        Serial.println("turning right");
        digitalWrite(rightDirPin, LOW);
        analogWrite(rightPWMPin, 200);
        break;                               // }
      case 0b00000010:                       // if (data == 0b00000010) {
        Serial.println("forward");
        digitalWrite(rightDirPin, HIGH);
        analogWrite(rightPWMPin, 0);
        digitalWrite(leftDirPin, LOW);
        analogWrite(leftPWMPin, 255);
        break;                               // }
      case 0b00000100:
        Serial.println("turning left");
        digitalWrite(leftDirPin, HIGH);
        analogWrite(leftPWMPin, 50);
        break;
      default:
        Serial.println("invalid code");
        stop();
        digitalWrite(rightDirPin, LOW);
        digitalWrite(rightPWMPin, LOW);
        break;
    }
  } else {
    //Serial.println("stop");
    stop();
  }
  delay(5);
}

void stop() {
  digitalWrite(rightDirPin, LOW);
  analogWrite(rightPWMPin, 0);
  digitalWrite(leftDirPin, LOW);
  analogWrite(leftPWMPin, 0);
}

void controlNeoPixel(int pattern) {
  if (pattern == neoPixelSmile)
  {
    doNeoPixelSmile();
  } else if (pattern == neoPixelFrown)
  {
    doNeoPixelFrown();
  }
}

void doNeoPixelSmile() {
  Serial.println("Smile!");
  // here we would control the LEDs to make a smile
}
void doNeoPixelFrown() {
  Serial.println("Frown!");
  // here we would control the LEDs to make a frown
}
