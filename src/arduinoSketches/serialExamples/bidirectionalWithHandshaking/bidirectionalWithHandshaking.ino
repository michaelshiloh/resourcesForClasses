/* bidirectional communication, with handshaking, between Arduino and p5.js
 * 
 * Use with this webserial library:
 * https://github.com/gohai/p5.webserial/
 *
 * Based on Mang's bidirectional example, which in turn was based on Aaron's
 *
 * 18 Nov 2026 - MS - initial entry
 */


/*
 * p5.js code
 * works in Chrome; not so sure about others
 *
 */
/*
let port;
let connectBtn;

let rVal = 0;
let alpha = 255;
let left = 0; // True (1) if mouse is being clicked on left side of screen
let right = 0; // True (1) if mouse is being clicked on right side of screen

function setup() {
  createCanvas(640, 480);
  textSize(18);

  port = createSerial();
  connectBtn = createButton("Connect to Arduino");
  connectBtn.mousePressed(connectBtnClick);

  // in setup, we can open ports we have used previously
  // without user interaction
  let usedPorts = usedSerialPorts();
  if (usedPorts.length > 0) {
    port.open(usedPorts[0], 57600);
    connectBtn.html("Disconnect");
    //connectBtn.hide();
  }
}

function draw() {
  background(map(rVal, 0, 1023, 0, 255), 255, 255);

  // the other value controls the text's transparency value
  fill(255, 0, 255, map(alpha, 0, 1023, 0, 255));

  // Print the current values
  text("rVal = " + rVal, 20, 50);
  text("alpha = " + alpha, 20, 70);

  // get new values from Arduino
  let str = port.readUntil("\n");
  if (str != null) {
    // make sure there is actually a message
    // split the message
    let fromArduino = split(trim(str), ",");
    // if the right length, then proceed
    if (fromArduino.length == 2) {
      // only store values here
      // do everything with those values in the main draw loop

      // We take the string we get from Arduino and explicitly
      // convert it to a number by using int()
      // e.g. "103" becomes 103
      rVal = int(fromArduino[0]);
      alpha = int(fromArduino[1]);
    }
    //////////////////////////////////
    //SEND TO ARDUINO HERE (handshake)
    //////////////////////////////////
    // click on one side of the screen, one LED will light up
    // click on the other side, the other LED will light up
    if (mouseIsPressed) {
      if (mouseX <= width / 2) {
        left = 1;
      } else {
        right = 1;
      }
    } else { // no buttons are pressed
      left = right = 0;
    }
    let sendToArduino = left + "," + right + "\n";
    console.log("sent to Arduino " + sendToArduino);
    port.println(sendToArduino);
  }
}

function connectBtnClick() {
  if (connectBtn.html() != "Disconnect") {
    port.open("Arduino", 57600);
    connectBtn.html("Disconnect");
    //connectBtn.hide();
  } else {
    port.close();
    connectBtn.html("Connect to Arduino");
  }
}
*/

/*
 * Arduino code
 * 
 */
/*

// Inputs:
// - A0 - sensor connected as voltage divider (e.g. potentiometer or light sensor)
// - A1 - sensor connected as voltage divider
//
// Outputs:
// - 2 - LED
// - 5 - LED

int leftLedPin = 2;
int rightLedPin = 5;

void setup() {
  // Start serial communication so we can send data
  // over the USB connection to our p5js sketch
  Serial.begin(57600);

  // We'll use the builtin LED as a status output.
  // We can't use the serial monitor since the serial connection is
  // used to communicate to p5js and only one application on the computer
  // can use a serial port at once.
  pinMode(LED_BUILTIN, OUTPUT);

  // Outputs on these pins
  pinMode(leftLedPin, OUTPUT);
  pinMode(rightLedPin, OUTPUT);

  // Blink them so we can check the wiring
  digitalWrite(leftLedPin, HIGH);
  digitalWrite(rightLedPin, HIGH);
  delay(200);
  digitalWrite(leftLedPin, LOW);
  digitalWrite(rightLedPin, LOW);



  // start the handshake
  while (Serial.available() <= 0) {
    digitalWrite(LED_BUILTIN, HIGH); // on/blink while waiting for serial data
    Serial.println("0,0"); // send a starting message
    delay(300);            // wait 1/3 second
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
  }
}

void loop() {
  // wait for data from p5 before doing something
  while (Serial.available()) {
    digitalWrite(LED_BUILTIN, HIGH); // led on while receiving data

    int left = Serial.parseInt();
    int right = Serial.parseInt();
    if (Serial.read() == '\n') {
      digitalWrite(leftLedPin, left);
      digitalWrite(rightLedPin, right);
      int sensor = analogRead(A0);
      delay(5);
      int sensor2 = analogRead(A1);
      delay(5);
      Serial.print(sensor);
      Serial.print(',');
      Serial.println(sensor2);
    }
  }
  digitalWrite(LED_BUILTIN, LOW);
}

*/

