/*
	UDP Echo Server
	Context: node.js

	Listen for UDP packets. 
	When a message is received, send it back

	created 19 February 2019
	by Michael Shiloh
*/

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


