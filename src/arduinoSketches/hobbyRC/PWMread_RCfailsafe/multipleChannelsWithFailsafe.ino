unsigned long now;                        // timing variables to update data at a regular interval
unsigned long rc_update;
const int channels = 4;                   // specify the number of receiver channels
float RC_in[channels];                    // an array to store the calibrated input from receiver

void setup() {
  setup_pwmRead();
  Serial.begin(9600);
}

void loop() {

  now = millis();

  if (RC_avail() || now - rc_update > 25) { // if RC data is available or 25ms has passed since last update
    // (adjust to be equal or greater than the frame rate of receiver)

    rc_update = now;

    print_RCpwm();                        // uncommment to print raw data from receiver to serial

    for (int i = 0; i < channels; i++) {    // run through each RC channel
      int CH = i + 1;

      RC_in[i] = RC_decode(CH);             // decode receiver channel and apply failsafe

      //print_decimal2percentage(RC_in[i]);   // uncomment to print calibrated receiver input (+-100%) to serial
    }
    //Serial.println();                       // uncomment when printing calibrated receiver input to serial.
  }
}
