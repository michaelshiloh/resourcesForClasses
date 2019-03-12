
/* based on example from reference page for

  WiFiNINA : Client class

  WiFiClient
  Description
  Creates a client that can connect to to a specified internet IP address and port as defined in client.connect().

  Syntax
  WiFiClient

  Parameters
  client : the named client to refer to

  Returns
  none

*/
#include <WiFiNINA.h>

#include "arduino_secrets.h"
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)

int status = WL_IDLE_STATUS;

IPAddress server(192, 168, 1, 4); // linux in lab

//IPAddress server(192, 168, 1, 5); // alienware on NETGEAR55

const int serverPort = 8000;


// Initialize the client library
WiFiClient tcpSocket;

void setup() {

  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.begin(9600);
  Serial.println("Attempting to connect to WPA network...");
  Serial.print("SSID: ");
  Serial.println(ssid);

  status = WiFi.begin(ssid, pass);
  if ( status != WL_CONNECTED) {
    Serial.println("trouble with WiFi module");
    // don't do anything else:
    while (true);
  }

  Serial.println("Connected to wifi");
  Serial.println("Opening TCP socket");
  if (tcpSocket.connect(server, serverPort)) {
    Serial.println("TCP socket to server established");
  } else {
    Serial.println("Error opening TCP socket");
    // don't do anything else:
    while (true);
  }

  // if any errors occurred we would be stuck in one
  // of the infinite loops, so if we arrived here we're
  // OK
  Serial.println("Everything seems OK, finished setup");
}

void loop() {

  /*
    Since we are the client, we're in charge, so
    // define the messages here

    Message from Arduino to node server
    // Byte 0: Start of message, value = 0x01
    // Byte 1: Sensor1 value
    // Byte 2: Sensor2 value
    // Byte 3: Sensor3 value
    // Byte 4: End of message, value = 0xFF

    Message from server to Arduino
    // Byte 0: Start of message, value = 0x01
    // Byte 1: Button1 value
    // Byte 2: Button2 value
    // Byte 3: Button3 value
    // Byte 4: End of message, value = 0xFF


  */
  byte message[5];

  message[0] = 0x01;
  message[1] = analogRead(A1);
  message[2] = analogRead(A2);
  message[3] = analogRead(A3);
  message[4] = 0xFF;

  for (int i = 0; i < 5; i++) {
    tcpSocket.write(message[i]);
    Serial.print("sent message byte: ");
    Serial.print(i);
    Serial.print(" value: ");
    Serial.print(message[i], HEX);
    Serial.println();
  }
  delay(1000);

  // could close the socket if we want, 
  // but then we'd have to open it again
  // tcpSocket.stop();
}
