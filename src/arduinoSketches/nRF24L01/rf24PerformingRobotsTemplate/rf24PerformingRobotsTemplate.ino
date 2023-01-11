void setup() {
  Serial.begin(9600); // initialize serial communications
  while (!Serial.available()) { // until the server responds,
    Serial.println("Hello");    // send a hello message
    delay(500);                 // every half second
  }
}
 
void loop() {
  // if there are incoming bytes:
  if (Serial.available()) {
    // read incoming byte:
    int input = Serial.read();
    // read the input on analog pin 0:
    int sensorValue = analogRead(A0);
    // print out the value you read:
    Serial.println(sensorValue);
    delay(1); // delay in between reads for stability
  }
}