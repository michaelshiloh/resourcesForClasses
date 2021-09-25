
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


void setup() {

  // Motor controller pins
  pinMode(rightDirPin, OUTPUT);
  pinMode(leftDirPin, OUTPUT);

  Serial.begin(115200);

  // RF24 setup
  bool retval = radio.begin();
  // Serial.println(retval);
  radio.openReadingPipe(0, address);  // Destination address 
  radio.setPALevel(RF24_PA_MIN);      // Min or max
  radio.startListening();             // sets  module as receiver
}
void loop() {
  if (radio.available())  //Looking for the data.
  {
    int data;

    radio.read(&data, sizeof(data));  //Reading the data
    //Serial.println(data);

    switch (data) {
        break;
      case 0x01:
        Serial.println("turning right");
        digitalWrite(rightDirPin, LOW);
        analogWrite(rightPWMPin, 200);
        break;
      case 0x02:
        Serial.println("forward");
        digitalWrite(rightDirPin, HIGH);
        analogWrite(rightPWMPin, 0);
        digitalWrite(leftDirPin, LOW);
        analogWrite(leftPWMPin, 255);
        break;
      case 0x04:
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
    Serial.println("stop");
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
