/*

  Read three buttons and transmit via UDP
  Receive packet and control three LEDs
  bidirectional, so no need to distinguish between
  transmitter and receiver: In fact this is a 
  transceiver

  based on threeButtonsToThreeLEDSUDP/basic

  created 15 February 2019
  by Michael Shiloh

  Questions to ponder:
  1. Can you justify all the global variables?
  2. The LED code in activateLEDs() and handleLEDStateChange() is almost identical
     except for the variables and byte number.
     Can you move this information into an array and rewrite activateLEDs() to access this
     information in a loop?
  3. Can you generalize this so that it works with any number of LEDs?
  4. Currently, there is no check to see if the packet we received is from the same device
     that we will control. Is this a bug or a feature? How would you change this?
*/

#include <SPI.h>
#include <WiFi101.h>
#include <WiFiUdp.h>

int status = WL_IDLE_STATUS;
#include "arduino_secrets.h"
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

/*
   My IP information
*/
// My IP address will be assigned to me by the WiFi router
const unsigned int localPort = 1000;   // This will be my port for listening


/*
   IP information of the other device (receiver)
*/

// IP address of the other device (receiver)
// Change this to IP address and port of the device you want to talk to
IPAddress receivingDeviceAddress(192, 168, 1, 22);
const unsigned int receivingDevicePort = 8967; // can be the same as my port, but doesn't need to be

WiFiUDP Udp;

const int BLUE_BUTTON_PIN = 7;
const int GREEN_BUTTON_PIN = 8;
const int YELLOW_BUTTON_PIN = 9;

const int BLUE_LED_PIN = 10;
const int GREEN_LED_PIN = 11;
const int YELLOW_LED_PIN = 12;

// remember the button state so we only send
// when the state changes
boolean currentBlueButtonState;
boolean lastBlueButtonState = LOW; // arbitrary
boolean currentGreenButtonState;
boolean lastGreenButtonState = LOW; // arbitrary
boolean currentYellowButtonState;
boolean lastYellowButtonState = LOW; // arbitrary

// LED state stuff
int blueLEDActive = LOW;
int blueLEDState = LOW;
unsigned long blueLEDChangedAt = 0;
const unsigned long blueLEDPeriod = 100;

int greenLEDActive = LOW;
int greenLEDState = LOW;
unsigned long greenLEDChangedAt = 0;
const unsigned long greenLEDPeriod = 234;

int yellowLEDActive = LOW;
int yellowLEDState = LOW;
unsigned long yellowLEDChangedAt = 0;
const unsigned long yellowLEDPeriod = 749;


void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);

  // remove this if you don't intend to use a serial monitor
  //  while (!Serial) {
  //    ; // wait for serial port to connect. Needed for native USB port only
  //  }

  // Used to indicate WiFi status
  pinMode( LED_BUILTIN, OUTPUT );

  // My LEDs
  pinMode(BLUE_LED_PIN, OUTPUT );
  pinMode(GREEN_LED_PIN, OUTPUT );
  pinMode( YELLOW_LED_PIN, OUTPUT );

  // check for the presence of the WiFi module:
  // Historically, WiFi was a shield, so for backgwards compatibility
  // compare to WL_NO_SHIELD.
  // In fact, WiFiNINA defines WL_NO_MODULE,
  // but it is equal to WL_NO_SHIELD
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi module not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to WiFi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // Flash the LED briefly to indicate we are trying
    digitalWrite(LED_BUILTIN, HIGH);
    delay(300);
    digitalWrite(LED_BUILTIN, LOW);

    // wait 10 seconds for connection:
    delay(10000);
  }

  Serial.println("Connected to wifi");
  printWiFiStatus();

  // In case there is no serial monitor,
  // indicate that we are connected by turning on the LED
  digitalWrite(LED_BUILTIN, HIGH);

  Serial.print("Initializing WiFiUDP library and listening on port ");
  Serial.println(localPort);
  Udp.begin(localPort);
}

void loop() {

  char packetBuffer[255]; //buffer to hold incoming packet

  /*
      It's always important to listen more than you speak,
      so first see if anyone has sent us anything
  */

  // If someone sent us something, parsePacket() will
  // return the size of the packet (in bytes)
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    // Read the packet into our local buffer
    int response = readIncomingPacket(packetSize, packetBuffer);

    // If readIncomingPacket() succeeded, then activate the LEDs
    if ( !response ) {
      activateLEDs(packetSize, packetBuffer);
    }
  }

  // Now that we've listened it's our turn to talk.
  // Check our switches and send a message to the other

  if (anySwitchChangedState()) {
    sendSwitchStatus();
  }

  // Finally, handle any LED blinking state
  handleLEDStateChange();
}

void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("My IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

/*
   Read an incoming packet into our local buffer.

   Takes:
     the size of the packet
     an array in which to put the packet

   Returns:
     -1 if an error occurred
     0 if everything is OK
*/

int readIncomingPacket(int numBytes, char byteArray[]) {

  // Defensive programming: This function should
  // only be called if there was something to process,
  // but let's double check that the number of bytes
  // expected is non-zero (we can't call parsePacket() again)
  if (!numBytes) {
    Serial.println ("ERROR in handleIncomingPacket: Called with an empty packet");
    return (-1);
  }

  // Packet size is non-zero, so we can proceed.
  // First report the size and source of the packet
  Serial.print("Received packet of size ");
  Serial.println(numBytes);
  Serial.print("From ");
  IPAddress remoteIp = Udp.remoteIP();
  Serial.print(remoteIp);
  Serial.print(", port ");
  Serial.println(Udp.remotePort());

  // read the packet into packetBufffer
  int len = Udp.read(byteArray, 255);
  if (len > 0) byteArray[len] = 0;
  Serial.print("Contents: ");
  for (int i = 0; i<len; i++) {
    Serial.print(0x30 + byteArray[i]);
  }
  Serial.println();

  // More defensive programming:
  // The number of bytes read should be the same as the
  // number of bytes that we were told we received
  if ( len != numBytes ) {
    Serial.print ("ERROR in handleIncomingPacket: I was told to read ");
    Serial.print (numBytes);
    Serial.print (" but Udp.read() only gave me ");
    Serial.print (len);
    Serial.print (" bytes");
    Serial.println();
    return (-1);
  }

  // Otherwise, everything seems OK
  return (0);

}

/*
   activate the LEDs according to the bytes in the packet.
   In this case assume that the first byte controls the blue LED,
   the second the green LED, and the third the yellow LED.

   Takes:
     the size of the packet
     the packet

   Returns:
     -1 if an error occurred
     0 if everything is OK
*/
int activateLEDs(int numBytes, char byteArray[]) {

  // We have three LEDs so we expect the packet to have 3 bytes.
  // If not, it's an error
  if ( 3 != numBytes ) {
    Serial.print ("ERROR in activateLEDs: I have 3 LEDs but received only ");
    Serial.print (numBytes);
    Serial.print (" bytes");
    Serial.println();
    return (-1);
  }

  // Is the blue switch pressed?
  blueLEDActive = byteArray[0];

  // If the LED was active, and now it isn't, and
  // it happened to be in the "ON" state, we need to
  // turn it off. If it's already off there is no harm
  // in turning it off again
  if ( !blueLEDActive ) {
    blueLEDState = LOW;
    digitalWrite(BLUE_LED_PIN, blueLEDState);
  }

  // Is the green switch pressed?
  greenLEDActive = byteArray[1];

  // If the LED was active, and now it isn't, and
  // it happened to be in the "ON" state, we need to
  // turn it off. If it's already off there is no harm
  // in turning it off again
  if ( !greenLEDActive ) {
    greenLEDState = LOW;
    digitalWrite(GREEN_LED_PIN, greenLEDState);
  }

  // Is the yellow switch pressed?
  yellowLEDActive = byteArray[2];

  // If the LED was active, and now it isn't, and
  // it happened to be in the "ON" state, we need to
  // turn it off. If it's already off there is no harm
  // in turning it off again
  if ( !yellowLEDActive ) {
    yellowLEDState = LOW;
    digitalWrite(YELLOW_LED_PIN, yellowLEDState);
  }
}

/*
   Check to see if any switches have changed state.

   Takes:
     No parameters are needed since all this information is
   global

   Returns:
     true if any switch has changed state
     false if no switch has changed state
*/
boolean anySwitchChangedState() {

  // start by reading the switch pins
  currentBlueButtonState = digitalRead(BLUE_BUTTON_PIN);
  currentGreenButtonState = digitalRead(GREEN_BUTTON_PIN);
  currentYellowButtonState = digitalRead(YELLOW_BUTTON_PIN);

  if ( (currentBlueButtonState == lastBlueButtonState) &&
       (currentGreenButtonState == lastGreenButtonState) &&
       (currentYellowButtonState == lastYellowButtonState) ) {

    // No switch has changed state; return false and we're done
    return ( false );
  }

  // Otherwise, at least one button has changed state,
  // so report it and return true

  //Serial.println("At least one button state has changed");

  Serial.print("blue = ");
  Serial.print(currentBlueButtonState);
  Serial.print("\tgreen = ");
  Serial.print(currentGreenButtonState);
  Serial.print("\tyellow = ");
  Serial.print(currentYellowButtonState);
  Serial.println();

  // Record the current state so we can check next time to
  // see if anything has changed
  lastBlueButtonState = currentBlueButtonState;
  lastGreenButtonState = currentGreenButtonState;
  lastYellowButtonState = currentYellowButtonState;

  return ( true );
}

/*
   Send the current switch states to the other device

   Takes:
     No parameters are needed since all this information is
   global

   Returns:
     nothing
*/
void sendSwitchStatus() {

  Serial.print("Sending switch status to ");
  Serial.print(receivingDeviceAddress);
  Serial.print(" at port ");
  Serial.println(receivingDevicePort);

  Udp.beginPacket(receivingDeviceAddress, receivingDevicePort);
  Udp.write(currentBlueButtonState);
  Udp.write(currentGreenButtonState);
  Udp.write(currentYellowButtonState);
  Udp.endPacket();
}

void handleLEDStateChange() {
  unsigned long currentTime = millis();

  if (blueLEDActive == HIGH) {
    // but is it time?
    if (currentTime - blueLEDChangedAt > blueLEDPeriod) {
      Serial.println("change blue LED state");
      blueLEDState = ! blueLEDState; // change the state
      digitalWrite(BLUE_LED_PIN, blueLEDState); //actually do it
      blueLEDChangedAt = currentTime; // record the time
    }
  }

  if (greenLEDActive == HIGH) {
    // but is it time?
    if (currentTime - greenLEDChangedAt > greenLEDPeriod) {
      Serial.println("change green LED state");
      greenLEDState = ! greenLEDState; // change the state
      digitalWrite(GREEN_LED_PIN, greenLEDState); //actually do it
      greenLEDChangedAt = currentTime; // record the time
    }
  }

  if (yellowLEDActive == HIGH) {
    // but is it time?
    if (currentTime - yellowLEDChangedAt > yellowLEDPeriod) {
      Serial.println("change yellow LED state");
      yellowLEDState = ! yellowLEDState; // change the state
      digitalWrite(YELLOW_LED_PIN, yellowLEDState); //actually do it
      yellowLEDChangedAt = currentTime; // record the time
    }
  }
}
