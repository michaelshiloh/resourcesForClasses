/*
  Send a value to Processing.

  Based on
  https://github.com/aaronsherwood/introduction_interactive_media/blob/master/processingExamples/gravityExamples/gravityWind/gravityWind.pde
  by Aaron Sherwood
*/

const int AINPIN = A2;

void setup() {
  // initialize the serial communication:
  Serial.begin(9600);

  // Since both sides wait for each other before they send anything,
  // someone needs to start the conversation
  Serial.println("0");
}

void loop() {
  while (Serial.available()) {
    Serial.parseInt(); // no need to store the value since we don't need it

    // Only proceed if we have the end of line
    if (Serial.read() == '\n') {

      // send the value of analog input 0:
      Serial.println(analogRead(AINPIN));
    }
  }
}

/* Processing code for this example

  // Simple movement of ellipse based on values from Arduino
  // Based on Graphing example by Tom Igoe

  import processing.serial.*;

  Serial myPort;        // The serial port
  float inByte = 0;

  void setup () {
  size(400, 300);

  // List all the available serial ports
  printArray(Serial.list());

  // I know that the first port in the serial list on my Linux
  // computer is always my Arduino, so I open Serial.list()[0].
  // Open whatever port is the one you're using.
  myPort = new Serial(this, Serial.list()[0], 9600);

  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');
  }

  void draw () {
  background(200);

  circle(inByte, height/2, 30);
  }

  void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');

  // Always check to make sure the string isn't empty
  if (inString != null) {
    // trim off any whitespace:
    inString = trim(inString);
    // convert to a float
    inByte = float(inString);
    // map to the width of the screen
    inByte = map(inByte, 0, 1023, 0, width);
    println(inByte);

    // Tell Arduino we're ready for another
    myPort.write(1 + "\n"); // could be any value
  }
}
*/
