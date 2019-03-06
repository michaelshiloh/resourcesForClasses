/* 
first find your IP address with

	ifconfig

then run this server with

	node server.js

connect using a browser to

	http://192.168.1.22:8080

references
	https://www.codementor.io/murphyisiwele/demystifying-nodejs-part-1-tcp-sockets-bf6bbskwz
	https://gist.github.com/tedmiston/5935757

*/

	
// For the HTTP server
const http = require('http')
const express = require('express'); // web server application
const app = express();        // instantiate express server
const webServer = http.Server(app);  // connects http library to server
const HTTP_PORT=7000;

// For the TCP server
const ARDUINO_PORT=8000;


/*
	The HTTP server
*/
app.use(express.static('public'));  // find pages in public directory

webServer.listen(HTTP_PORT, () => {
  console.log('webServer: Listening at', webServer.address());
});

webServer.on('connection', (socket) => {
  console.log("webServer: An HTTP client has connected")
});


/*
	The TCP server
*/

// import the net module
const { createServer } = require('net');

// create and return a net.Server object
const arduinoServer = createServer();

arduinoServer.on('connection', (socket) => {
  console.log("arduinoServer: A client has connected")

  socket.on('data',function(data){
    var numBytesRead = socket.bytesRead;
    console.log('Bytes read : ' + numBytesRead);
  
    // When we have received 5 bytes, read the message
    if (numBytesRead >=5) {
      var messageStart = data.readUInt8();
      var sensor1 = data.readUInt8();
      var sensor2 = data.readUInt8();
      var sensor3 = data.readUInt8();
      var messageEnd = data.readUInt8();
      console.log('read 5 bytes, values = ' + 
        messageStart + ' ' +
        sensor1 + ' ' +
        sensor2 + ' ' +
        sensor3 + ' ' +
        messageEnd);  
/*
      console.log('read 5 bytes, values = ' + 
        data[0] + ' ' +
        data[1] + ' ' +
        data[2] + ' ' +
        data[3] + ' ' +
        data[4]);  
*/
   }; // end of reading message
  }); // end of socket.on'data'

  socket.on('end', data => {
    console.log("arduinoServer: client has disconnected");
  });
}); // end of socket.on('connection')

arduinoServer.listen(ARDUINO_PORT, () => {

  var arduinoServerInfo = arduinoServer.address();

  var arduinoServerInfoJson = JSON.stringify(arduinoServerInfo);

  console.log('arduinoServer: Listening at : ' + arduinoServerInfoJson );

  arduinoServer.on('error', function (error) {
    console.error(JSON.stringify(error));
 });
});
