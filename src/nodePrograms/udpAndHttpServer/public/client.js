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
	displayTheImage();
});

socket.on('buttonReleased', (data) => {
	console.log('received button released from webserver: ' + data);
	hideTheImage();
});

function displayTheImage () {
	var placeholder = document.getElementById("placeholder");

	placeholder.src = "randomImage.jpeg"; // put images in public folder

	placeholder.style.opacity = 100;
}

function hideTheImage () {
	var placeholder = document.getElementById("placeholder");

	placeholder.style.opacity = 0;
}

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
