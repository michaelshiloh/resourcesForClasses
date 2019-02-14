/*

  Read three buttons and transmit via UDP 
  Based on WiFiUdpSendByteOnButtonPress

  created 12 February 2019
  by Michael Shiloh
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

// My IP information
// My IP address will be assigned to me by the WiFi router
const unsigned int localPort = 1000;   // This will be my port for listening

// IP information of the other device (receiver)
// IP address of the other device (receiver)
// Note that you probably need to change at least the IP address
IPAddress receivingDeviceAddress(192, 168, 1, 19);
const unsigned int receivingDevicePort = 2000;

char packetBuffer[255]; //buffer to hold incoming packet

WiFiUDP Udp;

const int BLUE_BUTTON_PIN = 3;
const int GREEN_BUTTON_PIN = 4;
const int YELLOW_BUTTON_PIN = 5;

// remember the button state so we only send
// when the state changes
boolean currentBlueButtonState;
boolean lastBlueButtonState = LOW; // arbitrary
boolean currentGreenButtonState;
boolean lastGreenButtonState = LOW; // arbitrary
boolean currentYellowButtonState;
boolean lastYellowButtonState = LOW; // arbitrary

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);

// remove this if you don't intend to use a serial monitor
//  while (!Serial) {
//    ; // wait for serial port to connect. Needed for native USB port only
//  }

  // Used to indicate WiFi status
  pinMode(LED_BUILTIN, OUTPUT);

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
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
    delay(200);
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


  currentBlueButtonState = digitalRead(BLUE_BUTTON_PIN);
  currentGreenButtonState = digitalRead(GREEN_BUTTON_PIN);
  currentYellowButtonState = digitalRead(YELLOW_BUTTON_PIN);

  // If any button has changed state, send all three
  if ( (currentBlueButtonState != lastBlueButtonState) ||
       (currentGreenButtonState != lastGreenButtonState) ||
       (currentYellowButtonState != lastYellowButtonState) ) {

    //Serial.println("button state changed; sending new state");

    Serial.print("blue = ");
    Serial.print(currentBlueButtonState);
    Serial.print("\tgreen = ");
    Serial.print(currentGreenButtonState);
    Serial.print("\tyellow = ");
    Serial.print(currentYellowButtonState);
    Serial.println();
    
    Udp.beginPacket(receivingDeviceAddress, receivingDevicePort);
    Udp.write(currentBlueButtonState);
    Udp.write(currentGreenButtonState);
    Udp.write(currentYellowButtonState);
    Udp.endPacket();

    lastBlueButtonState = currentBlueButtonState;
    lastGreenButtonState = currentGreenButtonState;
    lastYellowButtonState = currentYellowButtonState;
  }

  // once we send a packet to the server, it might
  // respond, so read it

  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remoteIp = Udp.remoteIP();
    Serial.print(remoteIp);
    Serial.print(", port ");
    Serial.println(Udp.remotePort());

    // read the packet into packetBufffer
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) packetBuffer[len] = 0;
    Serial.println("Contents:");
    Serial.println(packetBuffer);


  }
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
