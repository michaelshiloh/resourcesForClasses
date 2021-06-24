/*
   Basic example of sending data from Processing to Arduino
   because Processing is so much faster, we use handshaking
   to avoid overwhelming the Arduino

   Based on
   https://github.com/aaronsherwood/introduction_interactive_media/blob/master/arduinoExamples/serialExamples/buildOffThisOne/buildOffThisOne.ino
   by Aaron Sherwood
*/

int valueFromProcessing = 0;
const int LEDPIN = 3;

void setup() {
  Serial.begin(9600);
  Serial.println("0");
}

void loop() {
  while (Serial.available()) {
    valueFromProcessing = Serial.parseInt();
    
    // Only proceed if we have the end of line
    if (Serial.read() == '\n') {
      
      valueFromProcessing = map(valueFromProcessing, 0, 600, 0, 255);
      analogWrite(LEDPIN, valueFromProcessing);

      // Tell Processing we're ready for another
      Serial.println(0); // the value doesn't matter
    }
  }
}

/*
// Basic example of sending data from Processing to Arduino
// because Processing is so much faster, we use handshaking
// to avoid overwhelming the Arduino

// Based on 
// https://github.com/aaronsherwood/introduction_interactive_media/blob/master/arduinoExamples/serialExamples/buildOffThisOne/buildOffThisOne.ino
// by Aaron Sherwood


import processing.serial.*;
Serial myPort;

void setup() {
  size(600, 100);

  printArray(Serial.list());
  // replace the index with the index of Arduino's serial port
  String portname=Serial.list()[0];

  myPort = new Serial(this, portname, 9600);
  myPort.clear();
  myPort.bufferUntil('\n');
}

void draw() {
  background(200);
  line(mouseX, 0, mouseX, height);
}

void serialEvent(Serial myPort) {
  String s=myPort.readStringUntil('\n');
  myPort.write(mouseX+"\n");
  println("sent " + mouseX);

*/
