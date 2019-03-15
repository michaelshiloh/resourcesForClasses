/*

  WiFi UDP device responding to buttons on a web page 
  sent from a web page to node.js client to node.js server
  and finally to here

  code is at:
  https://github.com/michaelshiloh/resourcesForClasses/tree/master/src/nodePrograms/udpAndHttpServer

  created 3 February 2019
  by Michael Shiloh

  Change log:
  14 Mar 2019 - ms -  better comments and cleaned up code
                      Send binary data between Arduino and server

*/

#include <WiFiNINA.h>
#include <WiFiUdp.h>

int status = WL_IDLE_STATUS;
#include "arduino_secrets.h"
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

unsigned int myPort = 5000;      // local port to listen on
unsigned int remoteServerPort = 7000;  // remote port to talk to
IPAddress remoteServerAddress(192, 168, 1, 5);

char packetBuffer[255]; //buffer to hold incoming packet

WiFiUDP Udp;

// Sensors
const int BUTTON_PIN = 0;


// Actuators
const int NUMBER_OF_ACTUATORS = 3;
int actuators[NUMBER_OF_ACTUATORS] = {
  3, // pin numbers
  4,
  5
};

String LED_ON_MESSAGE = "ledON";
String LED_OFF_MESSAGE = "ledOFF";

// remember the button state so we only send
// when the state changes
boolean buttonState;
boolean lastButtonState = LOW; // arbitrary

void setup() {

  // Set all actuator pins as outputs
  for (int i = 0; i < NUMBER_OF_ACTUATORS; i++ ) {
    pinMode(actuators[i], OUTPUT);
  }
  
  //Initialize serial
  Serial.begin(9600);
  // wait for serial port to connect. Needed for native USB port only
  // Remove this if running without a serial monitor
  while (!Serial) {
    ; 
  }

  // attempt to connect to WiFi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to wifi");
  printWiFiStatus();

  Serial.print("Initializing WiFiUDP library and listening on port ");
  Serial.println(myPort);
  Udp.begin(myPort);
}

void loop() {

  // It's polite to listen first
  // Did the server send us anything?
  int packetSize = Udp.parsePacket(); 
  if (packetSize)
  {
    Serial.print("Received packet of size ");
    Serial.print(packetSize);
    Serial.print(" from address ");
    IPAddress remoteIp = Udp.remoteIP();
    Serial.print(remoteIp);
    Serial.print(", port ");
    Serial.println(Udp.remotePort());

    // read the packet into packetBufffer
    int len = Udp.read(packetBuffer, 255);

    // Activate the actuators as requested
    digitalWrite( 
      actuators[(int)packetBuffer[0]],  // first byte is actuator number
      (int)packetBuffer[1]);            // second byte is value
  }

  buttonState = digitalRead(BUTTON_PIN);

  if (buttonState != lastButtonState) {

    Serial.println("button state changed; sending new state");
    Udp.beginPacket(remoteServerAddress, remoteServerPort);
    Udp.write(buttonState);
    Udp.endPacket();

    lastButtonState = buttonState;
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
