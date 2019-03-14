/*
	slider: 
	displaying a slider on the web page and sending the value to the server
	Context: node.js

	Use webSockets between http client and server

	created 14 March 2019
	by Michael Shiloh
*/

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

/* HTTP callback functions */

httpServer.listen(HTTP_SERVER_PORT, () => {
	console.log('httpServer: Listening at', httpServer.address());
});

httpServer.on('connection', () => {
  console.log("httpServer: An HTTP client has connected")
});


/* Websocket event handler */

webSocket.on('connect', (socket) => {
    console.log('Web server socket: Client connected');

    // if you get the 'slider value' message
    socket.on('slider', (data) => {
       console.log('Web server socket: received slider value : ' + data);
    });

    socket.on('date', (data) => {
       console.log('Web server socket: received date value : ' + data);
    });

    // if you get the 'disconnect' message, say the user disconnected
    socket.on('disconnect', () => {
      console.log('Web server socket: user disconnected');
  });
});



























