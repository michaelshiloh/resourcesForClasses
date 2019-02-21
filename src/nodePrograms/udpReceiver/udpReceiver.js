/*
	UDP receiver
	Context: node.js

	Listen for UDP packets. When one is received, print it

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
}

udpServer.bind(MY_PORT);
udpServer.on('listening', serverIsListening);
udpServer.on('message', serverReceivedMessage);


