/*

  Blink using UDP Echo Server

  The usual blink, but instead of activating the LED,
  send a message to the UDP echo server, which will send it back to us.
  When the message is received, activate the LED

	The node.js code is at the end of this sketch

  based on threeButtonsToThreeLEDSUDP/basic
  as well as blinkWithoutDelay

  created 21 February 2019
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

const int LED_PIN = 10;

// LED state stuff
int LEDState = LOW;
unsigned long sentMessageAt = 0;
const unsigned long LEDPeriod = 1000;

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
  pinMode(LED_PIN, OUTPUT );

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
      digitalWrite(LED_PIN, packetBuffer[0]);
    }
  }

  // Is it time to send a message?
  unsigned long currentTime = millis();


  if (currentTime - sentMessageAt > LEDPeriod) {
    Serial.println("time to send a message to flip the LED");
    LEDState = !LEDState;

    Serial.print("Sending LED status to ");
    Serial.print(receivingDeviceAddress);
    Serial.print(" at port ");
    Serial.println(receivingDevicePort);

    Udp.beginPacket(receivingDeviceAddress, receivingDevicePort);
    Udp.write(LEDState);
    Udp.endPacket();

    sentMessageAt = currentTime; // record the time
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
  for (int i = 0; i < len; i++) {
    Serial.print(byteArray[i]);
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

/***********************************************************************
node.js code

copy this code to a .js file and invoke using:

	node <filename>

Careful when copying to remove these comments

//	UDP Echo Server
//	Context: node.js
//
//	Listen for UDP packets. 
//	When a message is received, send it back
//
//	created 19 February 2019
//	by Michael Shiloh

var dgram = require('dgram');
var MY_PORT = 8967;
var udpServer = dgram.createSocket('udp4')

function serverIsListening() {
	console.log('UDP Echo Server is listening');
}

function serverReceivedMessage(message, sender) {

	// print the message
	console.log(
		'Received message from' +
		sender.address + 
		':' + 
		sender.port);
	console.log(
		'Message length: ' +
		message.length + 
		' Message contents: ' +
		message);

	// Send the message back
	udpServer.send(message, 0, message.length, sender.port, sender.address);
}

udpServer.bind(MY_PORT);
udpServer.on('listening', serverIsListening);
udpServer.on('message', serverReceivedMessage);

*********************************************************************/
