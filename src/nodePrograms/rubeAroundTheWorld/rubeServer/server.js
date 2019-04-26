/*
	Server to trigger a local Rube Goldberg machine, when it receives a
	signal from the remote site that is its predecessor:

	- receiver waits for an HTTP request, and sends back an HTTP response.
	- receiver can either start the local machine immediately, or start a 
		countdown until it starts. 
		The countdown means you can run it in your own primetime.
  - if the receiver gets another request during the countdown, 
		it just responds with the remaining time.
  - at the end of the countdown, the receiver starts the machine.
  
	Context: node.js

	Based on:
	- Blink example at 
		https://www.w3schools.com/nodejs/nodejs_raspberrypi_blinking_led.asp
	- Time comparison at
		https://stackoverflow.com/questions/39522958/node-js-dates-comparison

	Created 25 April 2019
	by Michael Shiloh
*/

/* HTTP server talks to browser */
// const http = require('http')
const express = require('express'); // web server application
const app = express();        // instantiate express server
const HTTP_SERVER_PORT = 8000; 

var Gpio = require('onoff').Gpio; //include onoff to interact with the GPIO
var LED = new Gpio(4, 'out'); //use GPIO pin 4, and specify that it is output

// Express creates the simple web page
// The argument says where to find pages and scripts

var moment = require('moment');

/* HTTP callback functions */

app.listen(HTTP_SERVER_PORT, () => {
  console.log('httpServer: Listening ');
  LED.writeSync(0); // Turn LED off
});

app.get('/', (req, resp) => {
  console.log("httpServer: received a request")

  var now = moment();
  var runAt = moment({date: 26, hour: 16, minute: 00});  

  console.log("now = " + now.format("dddd, MMMM Do YYYY, h:mm:ss a"));
  console.log("runAt = " + runAt.format("dddd, MMMM Do YYYY, h:mm:ss a"));

  if( now.isAfter (runAt) ) { // if now > runAt
  	console.log("time to run!");
    LED.writeSync(1); //set pin state to 1 (turn LED on)
		resp.send("we are running!");
  }
  else {
	  var duration = moment.duration(runAt.diff(now));
				console.log(
					"Rube Around the World will run in NYU Abu Dhabi in " + 
					duration.get('hours') + 
					" hours and " + 
					duration.get('minutes') + 
					" minutes");
	  resp.send(
					"Rube Around the World will run in NYU Abu Dhabi in " + 
					duration.get('hours') + 
					" hours and " + 
					duration.get('minutes') + 
					" minutes");
  }
});
