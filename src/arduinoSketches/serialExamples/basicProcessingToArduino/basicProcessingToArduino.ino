/*
   Flash an LED when we receive a message from Processing.
   Because Processing is so much faster, we use handshaking
   to avoid overwhelming the Arduino

   Based on
   https://github.com/aaronsherwood/introduction_interactive_media/blob/master/arduinoExamples/serialExamples/buildOffThisOne/buildOffThisOne.ino
   by Aaron Sherwood
*/

const int LEDPIN = 3;

const int flashDuration = 100; // milliseconds
unsigned long turnedLEDOnAt = 0;

void setup() {
  Serial.begin(9600);

  // Since both sides wait for each other before they send anything,
  // someone needs to start the conversation
  Serial.println("0");

  pinMode(LEDPIN, OUTPUT);
}

void loop() {
  
  while (Serial.available()) {
    int valueFromProcessing = Serial.parseInt();

    // Only proceed if we have the end of line
    if (Serial.read() == '\n') {

      if (valueFromProcessing == 1) {
        //  turn on LED
        digitalWrite(LEDPIN, HIGH);
        // and note the time
        turnedLEDOnAt = millis();
      }

      // Tell Processing we're ready for another
      Serial.println(0); // the value doesn't matter
    }
  }

  if (millis() - turnedLEDOnAt >= flashDuration) {
    // turn off LED
    digitalWrite(LEDPIN, LOW);
  }
}

/*



// Bounce a ball, and each time the ball hits the floor
// flash an LED on Arduino. Demonstration of adding serial
// communication to an existing project.

// Based on
// https://github.com/aaronsherwood/introduction_interactive_media/blob/master/processingExamples/gravityExamples/gravityWind/gravityWind.pde
// by Aaron Sherwood

PVector velocity;
PVector gravity;
PVector position;
PVector acceleration;
float drag = 0.99;
float mass = 50;
float hDampening;

import processing.serial.*;
Serial myPort;
boolean arduinoIsReady = false;

void setup() {
  size(640, 360);
  noFill();

  position = new PVector(width/2, 0);
  velocity = new PVector(0, 0);
  acceleration = new PVector(0, 0);
  gravity = new PVector(0, 0.5*mass);

  printArray(Serial.list());
  // replace the index with the index of Arduino's serial port
  String portname=Serial.list()[0];

  myPort = new Serial(this, portname, 9600);
  myPort.clear();
  myPort.bufferUntil('\n');
}

void draw() {
  background(255);

  applyForce(gravity);
  velocity.add(acceleration);
  velocity.mult(drag);
  position.add(velocity);
  acceleration.mult(0);

  // Note that the mass is also the radius
  ellipse(position.x, position.y, mass, mass);

  // Did we hit the floor?
  if (position.y > height-mass/2) {

    // change direction to bounce, also loose some energy
    // (dampning) so we the bounce is a little less each time
    velocity.y *= -0.9;

    // prevent sinking beneath the floor
    position.y = height-mass/2;

    // Send message to Arduio
    if (arduinoIsReady && velocity.mag() > 1) {
      myPort.write(1 + "\n"); // could be any value
      arduinoIsReady = false;
    }
  }
}

void applyForce(PVector force) {
  // Newton's 2nd law: F = M * A
  // or A = F / M
  PVector f = PVector.div(force, mass);
  acceleration.add(f);
}



void serialEvent(Serial myPort) {
  String s=myPort.readStringUntil('\n');
  arduinoIsReady = true;
}

*/
