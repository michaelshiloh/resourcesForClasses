/* 
This is the websocket library which will allow us to send messages
back to the web server 
*/
var socket = io();


function ledON() {
  console.log ("sending a message to the web server to turn on the LED");
  // this is how we send a message back to the web server
  socket.emit('ledON'); 
}

function ledOFF() {
  console.log ("sending a message to the web server to turn off the LED");
  socket.emit('ledOFF');
}
