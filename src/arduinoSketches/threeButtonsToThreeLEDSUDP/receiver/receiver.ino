
/*
  Receive 3 bytes via UDP and indicate on appropriate LEDs
  Based on WiFiUdpRecvBytetoLED

  created 12 February 2019
  by Michael Shiloh

*/


#include <SPI.h>
#include <WiFiNINA.h>
#include <WiFiUdp.h>

int status = WL_IDLE_STATUS;
#include "arduino_secrets.h"
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

unsigned int localPort = 2390;      // local port to listen on

char packetBuffer[255]; //buffer to hold incoming packet

WiFiUDP Udp;

const int BLUE_LED_PIN = 3;
const int GREEN_LED_PIN = 4;
const int YELLOW_LED_PIN = 5;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);

  // remove this if you don't intend to use a serial monitor
  //  while (!Serial) {
  //    ; // wait for serial port to connect. Needed for native USB port only
  //  }

  // Used to indicate WiFi status
  pinMode(LED_BUILTIN, OUTPUT);

  // My three LEDs
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < "1.0.0") {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
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
  printWifiStatus();

  // In case there is no serial monitor,
  // indicate that we are connected by turning on the LED
  digitalWrite(LED_BUILTIN, HIGH);

  Serial.print("Initializing WiFiUDP library and listening on port ");
  Serial.println(localPort);
  Udp.begin(localPort);

}

void loop() {

  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();

  // if nobody sent us anything, packetSize
  // would be zero, so a non-zero packetSize
  // means we have something to work on
  if (packetSize) {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remoteIp = Udp.remoteIP();
    Serial.print(remoteIp);
    Serial.print(", port ");
    Serial.println(Udp.remotePort());

    if (packetSize != 3) {
      Serial.println("expected packet size of 3, something is wrong");
      return;
    }

    // read the packet into packetBufffer
    int len = Udp.read(packetBuffer, 255);

    digitalWrite(BLUE_LED_PIN, packetBuffer[0]);
    digitalWrite(GREEN_LED_PIN, packetBuffer[1]);
    digitalWrite(YELLOW_LED_PIN, packetBuffer[2]);

    // if we wanted to send anything back e.g. to
    // acknowledge the packet
    // this would be the place

  }
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("My IP Address: ");
  Serial.println(ip);
}
