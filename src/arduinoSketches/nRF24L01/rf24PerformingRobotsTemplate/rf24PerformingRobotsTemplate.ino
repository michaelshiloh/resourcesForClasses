/*
   Using the nRF24L01 radio module to communicate
   between two Arduinos with much increased reliability following
   various tutorials, conversations, and studying the nRF24L01 datasheet
   and the library reference.

   This file contains code for both transmitter and receiver. 
   Transmitter at the top, receiver at the bottom. 
   One of them is commented out.

   These sketches require the RF24 library by TMRh20
   Documentation here: https://nrf24.github.io/RF24/index.html

   change log

   02 Dec 2022 - ms - initial entry based on rf24ControlPanelPerformingRobotsNoHandshaking
*/

// Common code

// Common pin usage
// Note there are additional pins unique to transmitter or receiver
//

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

#include <printf.h>  // for debugging

// See note in rf24Handshaking about address selection
//

// Channel and address allocation:
// Eadin and Dania: Channel 30, addr = 0x76
// Fatima and Shamsa: Channel 40, addr = 0x73
// Oliver and Hessa:  Channel 50, addr = 0x7C
// Louis and Alpha: Channel 60, addr = 0xC6
// Yoki and Yupu:  Channel 70, addr = 0xC3
// Omar and Mudi: Channel 80, addr = 0xCC
// Dhabia and Joseph: Channel 90, addr = 0x33

const byte addr = 0x76;
const byte xmtrAddress[] = { addr, addr, 0xC7, 0xE6, 0xCC };
const byte rcvrAddress[] = { addr, addr, 0xC7, 0xE6, 0x66 };

//  Legitimate channels are 0-125
const int RF24_CHANNEL_NUMBER = 0;

const int RF24_POWER_LEVEL = RF24_PA_LOW;

// global variables
uint8_t pipeNum;
unsigned int totalTransmitFailures = 0;

struct DataStruct {
  uint8_t selectorBits;
};
DataStruct data;

void setupRF24Common() {

  // RF24 setup
  if (!radio.begin()) {
    Serial.println("radio  initialization failed");
    while (1)
      ;
  } else {
    Serial.println("radio successfully initialized");
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

  Serial.print("Sending data = ");
  Serial.print(data.selectorBits);
  Serial.print(" ... ");
  if (retval) {
    Serial.println("success");

  } else {
    totalTransmitFailures++;
    Serial.print("failure, total failures = ");
    Serial.println(totalTransmitFailures);
  }
}


// Transmitter code

// Additional pin usage for transmitter
// Example of selector switches line 1
const int SELECTOR0PIN = 6;
const int SELECTOR1PIN = 5;
const int SELECTOR2PIN = 4;
const int SELECTOR3PIN = 3;
const int XMIT1PIN = 2;

// Hypothetical second row of selector switches
const int SELECTOR4PIN = A0;
const int SELECTOR5PIN = A1;
const int SELECTOR6PIN = A2;
const int SELECTOR7PIN = A3;
const int XMIT2PIN = 7;

// Hypothetical audio control switches
const int PLAYNEXTCLIPPIN = A4;
const int PLAYPREVIOUSCLIPPIN = A5;
const int SPAREPIN = 8;

void setup() {
  Serial.begin(9600);
  printf_begin();

  // All switches use internal pullup resistor
  pinMode(SELECTOR0PIN, INPUT_PULLUP);
  pinMode(SELECTOR1PIN, INPUT_PULLUP);
  pinMode(SELECTOR2PIN, INPUT_PULLUP);
  pinMode(SELECTOR3PIN, INPUT_PULLUP);
  pinMode(SELECTOR4PIN, INPUT_PULLUP);
  pinMode(SELECTOR5PIN, INPUT_PULLUP);
  pinMode(SELECTOR6PIN, INPUT_PULLUP);
  pinMode(SELECTOR7PIN, INPUT_PULLUP);

  pinMode(XMIT1PIN, INPUT_PULLUP);
  pinMode(XMIT2PIN, INPUT_PULLUP);

  pinMode(PLAYNEXTCLIPPIN , INPUT_PULLUP);
  pinMode(PLAYPREVIOUSCLIPPIN , INPUT_PULLUP);
  pinMode(SPAREPIN , INPUT_PULLUP);

  setupRF24();
}

void setupRF24() {

  setupRF24Common();

  // Set us as a transmitter
  radio.openWritingPipe(xmtrAddress);
  radio.openReadingPipe(1, rcvrAddress);

  radio.printPrettyDetails();
  Serial.println("I am a transmitter");
}

void loop() {

  // If the transmit button is pressed, read the switches
  // and send the bits

  if (digitalRead(XMIT1PIN) == LOW) {  // remember switches are active LOW
    data.selectorBits = (digitalRead(SELECTOR0PIN) << 0 
    | digitalRead(SELECTOR1PIN) << 1 
    | digitalRead(SELECTOR2PIN) << 2
    | digitalRead(SELECTOR3PIN) << 3 );

    Serial.print("XMTR: sending data = ");
    Serial.println(data.selectorBits);

    
    radio.stopListening();
    rf24SendData();

    delay(100);  // if the button is still pressed don't do this too often
  }
}  // end of loop()

// End of transmitter code

/*
// Receiver Code

// Additional libraries for receiver
#include <Adafruit_VS1053.h>
#include <SD.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>

// Additional pin usage for receiver

// Adafruit music maker shield
#define SHIELD_RESET -1  // VS1053 reset pin (unused!)
#define SHIELD_CS 7      // VS1053 chip select pin (output)
#define SHIELD_DCS 6     // VS1053 Data/command select pin (output)
#define CARDCS 4         // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 3  // VS1053 Data request, ideally an Interrupt pin
Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

// Servo motors
const int SERVO0PIN = A1;
const int SERVO1PIN = A2;
const int SERVO2PIN = A3;
const int SERVO3PIN = A4;

// Neopixel
#define NEOPIXELPIN A5
#define NUMPIXELS 64  // change to fit
Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXELPIN, NEO_GRB + NEO_KHZ800);

Servo servo0;  // change names to describe what's moving
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

// change as per your robot
const int SERVO0NEUTRALPOSITION = 45;
const int SERVO1NEUTRALPOSITION = 90;
const int SERVO2NEUTRALPOSITION = 0;
const int SERVO3NEUTRALPOSITION = 180;
const int SERVO4NEUTRALPOSITION = 180;

void setup() {
  Serial.begin(9600);
  printf_begin();

  // Set up all the attached hardware
  setupMusicMakerShield();
  setupServoMotors();
  setupNeoPixels();
  setupRF24();

  // Brief flash to show we're done with setup()
  flashNeoPixels();
}

void setupRF24() {
  setupRF24Common();

  // Set us as a receiver
  radio.openWritingPipe(rcvrAddress);
  radio.openReadingPipe(1, xmtrAddress);

  radio.printPrettyDetails();
  Serial.println("I am a receiver");
}

void setupMusicMakerShield() {
  if (!musicPlayer.begin()) {  // initialise the music player
    Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
    while (1)
      ;
  }
  Serial.println(F("VS1053 found"));

  if (!SD.begin(CARDCS)) {
    Serial.println(F("SD card failed or not present"));
    while (1)
      ;  // don't do anything more
  }

  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(20, 20);

  // Timer interrupts are not suggested, better to use DREQ interrupt!
  //musicPlayer.useInterrupt(VS1053_FILEPLAYER_TIMER0_INT); // timer int

  // If DREQ is on an interrupt pin (on uno, #2 or #3) we can do background
  // audio playing
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int
}

void setupServoMotors() {
  servo0.attach(SERVO0PIN);
  servo1.attach(SERVO1PIN);
  servo2.attach(SERVO2PIN);
  servo3.attach(SERVO3PIN);

  servo0.write(SERVO0NEUTRALPOSITION);
  servo1.write(SERVO1NEUTRALPOSITION);
  servo2.write(SERVO2NEUTRALPOSITION);
  servo3.write(SERVO3NEUTRALPOSITION);
}

void setupNeoPixels() {
  pixels.begin();
  pixels.clear();
  pixels.show();
}

void flashNeoPixels() {

  // all on
  for (int i = 0; i < NUMPIXELS; i++) {  // For each pixel...
    pixels.setPixelColor(i, pixels.Color(0, 100, 0));
  }
  pixels.show();
  delay(500);
  
  // all off
  for (int i = 0; i < NUMPIXELS; i++) {  // For each pixel...
    pixels.setPixelColor(i, pixels.Color(0, 100, 0));
  }
  pixels.show();
}

void loop() {
  // If there is data, read it,
  // and do the needfull
  // Become a receiver
  radio.startListening();
  if (radio.available(&pipeNum)) {
    radio.read(&data, sizeof(data));
    Serial.print("message received Data = ");
    Serial.println(data.selectorBits);

    switch (data.selectorBits) {
      case 0b00000000:
        break;
      case 0b00000001:
        // Don't play if it's already playing
        if (musicPlayer.stopped()) {
          // Non-blocking
          Serial.println(F("Playing track 001"));
          musicPlayer.startPlayingFile("/track001.mp3");
        } else {
          Serial.println(F("Playing in progress, ignoring"));
        }
        break;
      case 0b00000010:
        // Don't play if it's already playing
        if (musicPlayer.stopped()) {
          // Non-blocking
          Serial.println(F("Playing track 002"));
          musicPlayer.startPlayingFile("/track002.mp3");
        } else {
          Serial.println(F("Playing in progress, ignoring"));
        }
        break;
      case 0b00000011:
        servo0.write(0);
        servo1.write(0);
        servo2.write(0);
        servo3.write(0);
        break;
      case 0b00000100:
        servo0.write(90);
        servo1.write(90);
        servo2.write(90);
        servo3.write(90);
        break;
      case 0b00000101:
        break;
      case 0b00000110:
        break;
      case 0b00000111:
        break;
      case 0b00001000:
        break;
      case 0b00001001:
        break;
      case 0b00001010:
        break;
      case 0b00001011:
        break;
      case 0b00001100:
        break;
      case 0b00001101:
        break;
      case 0b00001110:
        break;
      case 0b00001111:
        break;
      default:
        Serial.println("Invalid option");
    }
  }
}  // end of loop()

// end of receiver code

*/
