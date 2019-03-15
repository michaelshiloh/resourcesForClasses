/* 
This is the websocket library which will allow us to send messages
back to the web server 
*/
var socket = io();

socket.on('event', (data) => {
	console.log('received data from webserver: ' + data);
});

socket.on('buttonPressed', (data) => {
	console.log('received button pressed event from webserver: ' + data);
});

socket.on('buttonReleased', (data) => {
	console.log('received button released from webserver: ' + data);
});

function redLEDOn() {
  socket.emit('redLEDOn'); 
}

function redLEDOff() {
  socket.emit('redLEDOff');
}

function greenLEDOn() {
  socket.emit('greenLEDOn'); 
}

function greenLEDOff() {
  socket.emit('greenLEDOff');
}

function blueLEDOn() {
  socket.emit('blueLEDOn'); 
}

function blueLEDOff() {
  socket.emit('blueLEDOff');
}
