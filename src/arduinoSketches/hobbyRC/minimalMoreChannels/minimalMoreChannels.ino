/*
   Minimal decoding of multiple RC channels using pin change interrupts

   Does not check for reasonable values or timeouts

   Based on https://ryanboland.com/blog/reading-rc-receiver-values

  change log

  02 may 2022 - ms - initial entry
  24 may 2022 - ms - changed RC_CHx_PIN names
  15 sep 2022 - ms - changed pin numbers to new assignments

*/



// install this library from the library manager
// by Mike "GreyGnome" Schwager
#include <EnableInterrupt.h>

#define SERIAL_PORT_SPEED 9600
#define RC_NUM_CHANNELS  5

// DO NOT CHANGE THESE NUMBERS - THEY ARE 
// INDEXES INTO THE ARRAY
#define RC_CH1  0
#define RC_CH2  1
#define RC_CH3  2
#define RC_CH4  3
#define RC_CH5  4
#define RC_CH6  5

// CHANGE THESE NUMBERS TO CORRESPOND TO THE PINS THAT
// YOUR SHIELD HAS CONNECTED TO THE RADIO CHANNELS
#define RC_CH1_PIN  16
#define RC_CH2_PIN  17
#define RC_CH3_PIN  18
#define RC_CH4_PIN  19
#define RC_CH5_PIN  20
#define RC_CH6_PIN  21

uint16_t rc_values[RC_NUM_CHANNELS];
uint32_t rc_start[RC_NUM_CHANNELS];
volatile uint16_t rc_shared[RC_NUM_CHANNELS];

void rc_read_values() {
  noInterrupts();
  memcpy(rc_values, (const void *)rc_shared, sizeof(rc_shared));
  interrupts();
}

void calc_input(uint8_t channel, uint8_t input_pin) {
  if (digitalRead(input_pin) == HIGH) {
    rc_start[channel] = micros();
  } else {
    uint16_t rc_compare = (uint16_t)(micros() - rc_start[channel]);
    rc_shared[channel] = rc_compare;
  }
}

void calc_ch1() {
  calc_input(RC_CH1, RC_CH1_PIN);
}
void calc_ch2() {
  calc_input(RC_CH2, RC_CH2_PIN);
}
void calc_ch3() {
  calc_input(RC_CH3, RC_CH3_PIN);
}
void calc_ch4() {
  calc_input(RC_CH4, RC_CH4_PIN);
}
void calc_ch5() {
  calc_input(RC_CH5, RC_CH5_PIN);
}
void calc_ch6() {
  calc_input(RC_CH6, RC_CH6_PIN);
}

void setup() {
  Serial.begin(SERIAL_PORT_SPEED);

  pinMode(RC_CH1_PIN, INPUT);
  pinMode(RC_CH2_PIN, INPUT);
  pinMode(RC_CH3_PIN, INPUT);
  pinMode(RC_CH4_PIN, INPUT);
  pinMode(RC_CH5_PIN, INPUT);
  pinMode(RC_CH6_PIN, INPUT);

  enableInterrupt(RC_CH1_PIN, calc_ch1, CHANGE);
  enableInterrupt(RC_CH2_PIN, calc_ch2, CHANGE);
  enableInterrupt(RC_CH3_PIN, calc_ch3, CHANGE);
  enableInterrupt(RC_CH4_PIN, calc_ch4, CHANGE);
  enableInterrupt(RC_CH5_PIN, calc_ch5, CHANGE);
  enableInterrupt(RC_CH6_PIN, calc_ch6, CHANGE);
}

void loop() {
  rc_read_values();

  Serial.print("CH1:"); Serial.print(rc_values[RC_CH1]); Serial.print("\t");
  Serial.print("CH2:"); Serial.print(rc_values[RC_CH2]); Serial.print("\t");
  Serial.print("CH3:"); Serial.print(rc_values[RC_CH3]); Serial.print("\t");
  Serial.print("CH4:"); Serial.print(rc_values[RC_CH4]); Serial.print("\t");
  Serial.print("CH5:"); Serial.print(rc_values[RC_CH5]); Serial.print("\t");
  Serial.print("CH6:"); Serial.println(rc_values[RC_CH6]);

  delay(200);
}
