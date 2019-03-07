/*
	UDP And HTTP Server
	Context: node.js

	Serve a web page to a browser with a control panel
	Read control panel and send results to Arduino via UDP

	Use webSockets between http client and server

	created 7 March 2019
	by Michael Shiloh
*/

/* UDP server talks to Arduino */
var dgram = require('dgram');
var udpServer = dgram.createSocket('udp4')
var ARDUINO_UDP_PORT = 7000;

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
const io = require('socket.io')(httpServer);  

/* UDP server callback functions */

function UDPServerIsListening() {
	console.log('UDP Server is listening');
}

function UDPServerReceivedMessage(message, sender) {

	// print the message
	console.log(
		'Received message from: ' +
		sender.address + 
		':' + 
		sender.port);
	console.log(
		'Message length: ' +
		message.length + 
		' Message contents: ' +
		message);

	udpServer.send(message, 0, message.length, sender.port, sender.address);
}

/* Register the UDP callback functions */
udpServer.bind(ARDUINO_UDP_PORT );
udpServer.on('listening', UDPServerIsListening);
udpServer.on('message', UDPServerReceivedMessage);

/* HTTP callback functions */

httpServer.listen(HTTP_SERVER_PORT, () => {
	console.log('httpServer: Listening at', httpServer.address());
});

httpServer.on('connection', (socket) => {
  console.log("httpServer: An HTTP client has connected")
});


/* and here is the websocket event handler */

io.on('connect', function (socket) {
    console.log('a user connected');

    // if you get the 'ledON' message
    socket.on('ledON', function () {
      console.log('Web server socket: received ledON message from web client');
      // this is where we would send the message to Arduino
    });

    // if you get the 'ledOFF' message
    socket.on('ledOFF', function () {
       console.log('Web server socket: received ledOFF message from web client');
      // this is where we would send the message to Arduino
    });

    // if you get the 'disconnect' message, say the user disconnected
    socket.on('disconnect', function () {
      console.log('Web server socket: user disconnected');
  });
});
