/*
	UDP And HTTP Server
	Context: node.js

	Serve a web page to a browser with a control panel
	Read control panel and send results to Arduino 

	Web server provided by modules "http" and "express"

	Communication with Arduino is via a UDP socket
	provided by module "dgram"

	Communication with the web client (web browser) 
	is via a UDP socket provided by webSockets.
	Websockets creates a socket on top of the HTTP protocol
	The webSockets module is "socket.io"

	created 7 March 2019
	by Michael Shiloh

	Change log:

	14 Mar 2019 - ms - better comments and cleaned up code
										 send bytes instead of buffers to Arduino
										 receive button events from Arduino and send to web page
*/

/* UDP server talks to Arduino */
var dgram = require('dgram');
var arduinoUDPServer = dgram.createSocket('udp4')
var MY_PORT_FOR_ARDUINO = 7000;
var ARDUINO_PORT_FOR_ME= 5000;
var ARDUINO_IP_ADDRESS = '192.168.1.4';

/* HTTP server talks to browser */
const http = require('http')
const express = require('express'); // web server application
const app = express();        // instantiate express server
const httpServer = http.Server(app);  // connects http library to server
const HTTP_SERVER_PORT = 8000; 

// Express creates the simple web page
// The argument says where to find pages and scripts
app.use(express.static('public'));  

// websockets so that webpage can talk back to server
const webSocket = require('socket.io')(httpServer);  

/* Arduino UDP server callback functions */

function ArduinoUDPServerIsListening() {
	console.log('Arduino UDP Server is listening');
}

function ArduinoUDPServerReceivedMessage(message, sender) {

	// If the message is a byte we need to read a byte
	if (message.readUInt8(0) == 0 ) {
		console.log( "received a 0");
		// Now send a message to the web browser to change color
		webSocket.emit('buttonReleased', 99);
	}

	if (message.readUInt8(0) == 1 ) {
		console.log( "received a 1");
		webSocket.emit('buttonPressed', 19);
	}
}

/* Register the UDP callback functions */
arduinoUDPServer.bind( MY_PORT_FOR_ARDUINO );
arduinoUDPServer.on( 'listening', ArduinoUDPServerIsListening);
arduinoUDPServer.on( 'message', ArduinoUDPServerReceivedMessage);

/* HTTP callback functions */

httpServer.listen(HTTP_SERVER_PORT, () => {
	console.log('web server: Listening at', httpServer.address());
});

httpServer.on('connection', () => {
  console.log("web server: An HTTP client has connected")
});


// Websocket event handler 
// for UDP messages coming from the browser

webSocket.on('connect', (socket) => {
	// array for the message
	// newLEDState[0] = LED number 
	// newLEDState[1] = LED state 
	const SIZEOF_LED_DATA = 2;
	var newLEDState = new Uint8Array(SIZEOF_LED_DATA ); 
  
	console.log('Web server socket: Client connected');

  socket.on('redLEDOn', () => {
		console.log('red LED on');
		newLEDState[0] = 0;  // Red is LED number 0
		newLEDState[1] = 1; // turn on the LED
    // Send the message to Arduino
    arduinoUDPServer.send(
			newLEDState,
			0, // offset to the message start in the buffer
			SIZEOF_LED_DATA,
			ARDUINO_PORT_FOR_ME, 
			ARDUINO_IP_ADDRESS);
  });

  socket.on('redLEDOff', () => {
		console.log('red LED off');
		newLEDState[0] = 0;  // Red is LED number 0
		newLEDState[1] = 0; // turn off the LED
    // Send the message to Arduino
    arduinoUDPServer.send(
			newLEDState,
			0, // offset to the message start in the buffer
			SIZEOF_LED_DATA,
			ARDUINO_PORT_FOR_ME, 
			ARDUINO_IP_ADDRESS);
  });

  socket.on('greenLEDOn', () => {
		console.log('green LED on');
		newLEDState[0] = 1;  // green is LED number 1
		newLEDState[1] = 1; // turn on the LED
    // Send the message to Arduino
    arduinoUDPServer.send(
			newLEDState,
			0, // offset to the message start in the buffer
			SIZEOF_LED_DATA,
			ARDUINO_PORT_FOR_ME, 
			ARDUINO_IP_ADDRESS);
  });

  socket.on('greenLEDOff', () => {
		console.log('green LED off');
		newLEDState[0] = 1;  // green is LED number 1
		newLEDState[1] = 0; // turn off the LED
    // Send the message to Arduino
    arduinoUDPServer.send(
			newLEDState,
			0, // offset to the message start in the buffer
			SIZEOF_LED_DATA,
			ARDUINO_PORT_FOR_ME, 
			ARDUINO_IP_ADDRESS);
  });

  socket.on('blueLEDOn', () => {
		console.log('blue LED on');
		newLEDState[0] = 2;  // blue is LED number 2
		newLEDState[1] = 1; // turn on the LED
    // Send the message to Arduino
    arduinoUDPServer.send(
			newLEDState,
			0, // offset to the message start in the buffer
			SIZEOF_LED_DATA,
			ARDUINO_PORT_FOR_ME, 
			ARDUINO_IP_ADDRESS);
  });

  socket.on('blueLEDOff', () => {
		console.log('blue LED off');
		newLEDState[0] = 2;  // blue is LED number 2
		newLEDState[1] = 0; // turn off the LED
    // Send the message to Arduino
    arduinoUDPServer.send(
			newLEDState,
			0, // offset to the message start in the buffer
			SIZEOF_LED_DATA,
			ARDUINO_PORT_FOR_ME, 
			ARDUINO_IP_ADDRESS);
  });

  // if you get the 'disconnect' message, say the user disconnected
  socket.on('disconnect', () => {
    console.log('Web server socket: user disconnected');
  });
});
