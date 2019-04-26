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
	- Moment documentation at

	Created 25 April 2019
	by Michael Shiloh
*/

/* HTTP server talks to browser */
const express = require('express'); // web server application
const app = express();        // instantiate express server
const HTTP_SERVER_PORT = 8000; 

// The onoff module provide access to the GPIO pins on the pi
var Gpio = require('onoff').Gpio; 
var LED = new Gpio(4, 'out'); //use GPIO pin 4, and specify that it is output

// to handle time calculations
var moment = require('moment');
var runAt = moment({date: 26, hour: 16, minute: 00});   // when to run
// var runAt = moment({date: 26, hour: 11, minute: 36});   // sooner for testing

// Set a timer to check the time very so often,
// If we are triggered before it is time this will initiate the
// machine at the set time
var checkTimeInterval = setInterval(checkTime, 60000); //run the checkTime function every 1 minute
var triggered = false;
function checkTime() { 

	if (triggered == false) {
    console.log("checkTime: we have not yet been triggered");
    return;
  }

  // since triggered is true, we must check the time
  var now = moment();


  console.log("now = " + now.format("dddd, MMMM Do YYYY, h:mm:ss a"));
  console.log("runAt = " + runAt.format("dddd, MMMM Do YYYY, h:mm:ss a"));

  if ( now.isAfter (runAt) ) { 
	  console.log( "Rube Around the World in NYU Abu Dhabi is RUNNING!");
    LED.writeSync(1); //set pin state to 1 (turn LED on)
  } else {
    var duration = moment.duration(runAt.diff(now));
		console.log(
  				"Rube Around the World has been triggered and will run in NYU Abu Dhabi in " + 
					duration.get('hours') + 
					" hours and " + 
					duration.get('minutes') + 
					" minutes");
  }
}

// when server goes into listening mode
app.listen(HTTP_SERVER_PORT, () => {
  console.log('httpServer: Listening ');
  LED.writeSync(0); // Turn LED off
});

// when server receives a "get" request
app.get('/', (req, resp) => {
  console.log("httpServer: received a request")

  var now = moment();

  console.log("now = " + now.format("dddd, MMMM Do YYYY, h:mm:ss a"));
  console.log("runAt = " + runAt.format("dddd, MMMM Do YYYY, h:mm:ss a"));

  if( now.isAfter (runAt) ) { // if now > runAt
	  resp.send( "Rube Around the World in NYU Abu Dhabi is RUNNING!");
	  console.log( "Rube Around the World in NYU Abu Dhabi is RUNNING!");
    LED.writeSync(1); //set pin state to 1 (turn LED on)
  }
  else {
	  var duration = moment.duration(runAt.diff(now));
				console.log(
					"Rube Around the World has been triggered and will run in NYU Abu Dhabi in " + 
					duration.get('hours') + 
					" hours and " + 
					duration.get('minutes') + 
					" minutes");
	  resp.send(
					"Rube Around the World has been triggered and will run in NYU Abu Dhabi in " + 
					duration.get('hours') + 
					" hours and " + 
					duration.get('minutes') + 
					" minutes");
		triggered = true;
  }
});
