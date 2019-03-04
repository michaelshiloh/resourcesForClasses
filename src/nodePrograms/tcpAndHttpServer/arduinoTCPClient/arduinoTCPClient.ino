
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
//#include <SPI.h>
#include <WiFiNINA.h>

#include "arduino_secrets.h" 
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)

int status = WL_IDLE_STATUS;

IPAddress server(192,168,1,22);  // Google

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
    while(true);
  } 
  else {
    Serial.println("Connected to wifi");
    Serial.println("\nStarting connection...");
    // if you get a connection, report back via serial:
    if (tcpSocket.connect(server, serverPort)) {
      Serial.println("connected");
      // Make a HTTP request:
      tcpSocket.println("GET /search?q=arduino HTTP/1.0");
      tcpSocket.println();
    }
  }
}

void loop() {

}
