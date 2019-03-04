/* 
first find your IP address with

	ifconfig

then run this server with

	node server.js

connect using a browser to

	http://192.168.1.22:8080

*/

	
const http = require('http')
const express = require('express'); // web server application
const app = express();        // instantiate express server
const webServer = http.Server(app);  // connects http library to server

const HTTP_PORT=7000;
const ARDUINO_PORT=8000;

app.use(express.static('public'));  // find pages in public directory

webServer.listen(HTTP_PORT, () => {
  console.log('webServer: Listening on', webServer.address());
});

webServer.on('connection', (socket) => {
  console.log("webServer: A client has connected")
});


///--------------------

const { createServer } = require('net');

const arduinoServer = createServer();

let counter = 0;
const sockets = {}

arduinoServer.on('connection', (socket) => {
  socket.id = counter++
  sockets[socket.id] = socket;
  // socket.write("A client has connected\n")
  console.log("arduinoServer: A client has connected")

  socket.on('data', data => {
    Object.entries(sockets).forEach(([key, cs]) => {
      if(sockets.id != key) {
        cs.write(data);
      }
    });
  })
});

arduinoServer.listen(ARDUINO_PORT, () => {
  console.log('arduinoServer: Listening on port: ' + ARDUINO_PORT )
  console.log('arduinoServer: Listening at address: ' + arduinoServer.address() )
})
