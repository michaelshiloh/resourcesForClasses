/*
  analogReadingAndWriting

  An example of reading an analog input, scaling the value using the map()
  function, and then using that scaled value to control the brightness of an
  LED with analogWrite, and also to control the rate of blinking of the
  built-in LED on pin 13.

  Also illustrates the use of Serial.print() and Serial.println()

  Based on the built-in example analogReadSerial

  Written by Michael Shiloh on 13 February 2020

  This program could be improved by assigning well-named variables for
  the pin names, and using the "const" prefix

  Circuit:

  Put an LED (with resistor) on pin 6

  Put some sort of analog sensor on pin A3. We used a light sensor and
  then a potentiometer in class.
*/

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // Set the inputs and outputs
  pinMode(A3, INPUT);  // pin A3 is one of the analogRead capable pins
  pinMode(6, OUTPUT);  // pin 6 is one of the analogWrite (PWM) capable pins
  pinMode(13, OUTPUT); // built-in LED
}

void loop() {

  // read the input on analog pin 3:
  int sensorValue = analogRead(A3); // 0-1023 as it uses 10 bits

  // smallest number in class was 50
  // biggest number in class was 1006

  // Here we map the value from the sensor to the allowable range of 
  // analogWrite(), which is only 0 to 255. We also use constrain()
  // to make sure it stays within this range, and we print out the value
  // just to see it working properly
  int mappedValue;
  mappedValue = map(sensorValue, 50, 1006, 0, 255);
  mappedValue = constrain(mappedValue, 0, 255);
  Serial.print("raw value = ");
  Serial.print(sensorValue);
  Serial.print(" mapped value = ");
  Serial.println(mappedValue);

  analogWrite(6, mappedValue); // only values from 0 - 255 as it uses 8 bits

  // Do a little blink:
  digitalWrite(13, HIGH);
  delay(mappedValue * 10); // could have used map here again
  digitalWrite(13, LOW);
  delay(mappedValue * 10);

  // the original example has a delay here. This is unnecessary now that
  // we have the delay of the blink, but I'll leave it in just to remind
  // you that it might be necessary when you do many successive calls
  // to analogRead()
  // I have no idea what the world 'stability' refers to
  delay(1);        // delay in between reads for stability
}
