/*
   Minimal decoding of multiple RC channels using pin change interrupts

   Does not check for reasonable values or timeouts

   Based on https://ryanboland.com/blog/reading-rc-receiver-values
   Based on https://github.com/michaelshiloh/resourcesForClasses/blob/master/src/arduinoSketches/hobbyRC/minimalMoreChannels

  change log

  15 Nov 2025 - ms - initial entry
                      Uses pin numbers for "Arduino Shield Hobby RC and Motor Control" 
                      Adding gradual deceleration to avoid robots tipping over when stopping

*/



// install this library from the library manager
// by Mike "GreyGnome" Schwager
#include <EnableInterrupt.h>

#define SERIAL_PORT_SPEED 9600
#define RC_NUM_CHANNELS 5

// DO NOT CHANGE THESE NUMBERS - THEY ARE
// INDEXES INTO THE ARRAY
#define RC_CH1 0
#define RC_CH2 1
#define RC_CH3 2
#define RC_CH4 3
#define RC_CH5 4

// CHANGE THESE NUMBERS TO CORRESPOND TO THE PINS THAT
// YOUR SHIELD HAS CONNECTED TO THE RADIO CHANNELS
#define RC_CH1_PIN 2
#define RC_CH2_PIN 3
#define RC_CH3_PIN 4
#define RC_CH4_PIN 5
#define RC_CH5_PIN 6

uint16_t rc_values[RC_NUM_CHANNELS];
uint32_t rc_start[RC_NUM_CHANNELS];
volatile uint16_t rc_shared[RC_NUM_CHANNELS];

const int LEFT_MOTOR_EN = 9;
const int LEFT_MOTOR_INA = 8;
const int LEFT_MOTOR_INB = 7;

const int RIGHT_MOTOR_EN = 11;
const int RIGHT_MOTOR_INA = 10;
const int RIGHT_MOTOR_INB = 12;

int currentSpeedLeftMotor = 0;
int currentSpeedRightMotor = 0;
int desiredSpeedLeftMotor = 0;
int desiredSpeedRightMotor = 0;
int stepSize;

// Helper functions for reading the hobby RC radio signals
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


void setup() {
  Serial.begin(SERIAL_PORT_SPEED);

  // For the hobby RC radio
  pinMode(RC_CH1_PIN, INPUT);
  pinMode(RC_CH2_PIN, INPUT);
  pinMode(RC_CH3_PIN, INPUT);
  pinMode(RC_CH4_PIN, INPUT);
  pinMode(RC_CH5_PIN, INPUT);

  enableInterrupt(RC_CH1_PIN, calc_ch1, CHANGE);
  enableInterrupt(RC_CH2_PIN, calc_ch2, CHANGE);
  enableInterrupt(RC_CH3_PIN, calc_ch3, CHANGE);
  enableInterrupt(RC_CH4_PIN, calc_ch4, CHANGE);
  enableInterrupt(RC_CH5_PIN, calc_ch5, CHANGE);

  // for the left and right motors

  pinMode(LEFT_MOTOR_EN, OUTPUT);
  pinMode(LEFT_MOTOR_INA, OUTPUT);
  pinMode(LEFT_MOTOR_INB, OUTPUT);

  pinMode(RIGHT_MOTOR_EN, OUTPUT);
  pinMode(RIGHT_MOTOR_INA, OUTPUT);
  pinMode(RIGHT_MOTOR_INB, OUTPUT);

  // turn all motors off
  analogWrite(LEFT_MOTOR_EN, 0);
  analogWrite(RIGHT_MOTOR_EN, 0);
}

void loop() {
  rc_read_values();

  // Serial.print("CH1:");
  // Serial.print(rc_values[RC_CH1]);
  // Serial.print("\t");
  // Serial.print("CH2:");
  // Serial.print(rc_values[RC_CH2]);
  // Serial.print("\t");
  // Serial.print("CH3:");
  // Serial.print(rc_values[RC_CH3]);
  // Serial.print("\t");
  // Serial.print("CH4:");
  // Serial.print(rc_values[RC_CH4]);
  // Serial.print("\t");
  // Serial.print("CH5:");
  // Serial.print(rc_values[RC_CH5]);
  // Serial.print("\t");
  // Serial.print("CH6:");
  // Serial.print(rc_values[RC_CH6]);
  Serial.println();

  if (rc_values[RC_CH4] > 1450 && rc_values[RC_CH4] < 1550) {
    stop();
  }

  else if (rc_values[RC_CH4] < 1450 && rc_values[RC_CH4] > 950) {
    // always do a constrain before a map
    int value = constrain(rc_values[RC_CH4], 1000, 1450);
    forward(map(value, 1450, 1000, 0, 255));
  }

  // need to add reverse and turning
}

void forward(int mySpeed) {
  Serial.print("\tforward speed = ");
  Serial.print(mySpeed);
  Serial.println();
  stepSize = 20;
  leftMotorForward(mySpeed);
  rightMotorForward(mySpeed);
}

void leftMotorForward(int mySpeed) {
  digitalWrite(LEFT_MOTOR_INA, LOW);
  digitalWrite(LEFT_MOTOR_INB, HIGH);

  desiredSpeedLeftMotor = mySpeed;
  //currentSpeedLeftMotor = mySpeed; // this would cause immediate change
  // Serial.print("\tdesiredSpeedLeftMotor = ");
  // Serial.print(desiredSpeedLeftMotor);
  // Serial.println();
  updateLeftMotor();
}

void rightMotorForward(int mySpeed) {
  digitalWrite(RIGHT_MOTOR_INA, LOW);
  digitalWrite(RIGHT_MOTOR_INB, HIGH);
  desiredSpeedRightMotor = mySpeed;
  // currentSpeedRightMotor = mySpeed; // this would cause immediate change
  updateRightMotor();
}

void stop() {

  if (currentSpeedLeftMotor == 0 && currentSpeedRightMotor == 0) {
    return;
  }

  stepSize = 5;

  desiredSpeedLeftMotor = 0;
  desiredSpeedRightMotor = 0;
  updateLeftMotor();
  updateRightMotor();
}

void updateLeftMotor() {
  if (desiredSpeedLeftMotor > currentSpeedLeftMotor) {
    currentSpeedLeftMotor += stepSize;

  } else if (desiredSpeedLeftMotor < currentSpeedLeftMotor) {
    currentSpeedLeftMotor -= stepSize;
  }

  currentSpeedLeftMotor = constrain(currentSpeedLeftMotor, 0, 255);

  Serial.print("currentSpeedLeftMotor = ");
  Serial.print(currentSpeedLeftMotor);

  Serial.print("\tdesiredSpeedLeftMotor = ");
  Serial.print(desiredSpeedLeftMotor);
  // Serial.println("");
  analogWrite(LEFT_MOTOR_EN, currentSpeedLeftMotor);
}

void updateRightMotor() {
  if (desiredSpeedRightMotor > currentSpeedRightMotor) {
    currentSpeedRightMotor += stepSize;

  } else if (desiredSpeedRightMotor < currentSpeedRightMotor) {
    currentSpeedRightMotor -= stepSize;
  }

  currentSpeedRightMotor = constrain(currentSpeedRightMotor, 0, 255);

  Serial.print("\tcurrentSpeedRightMotor = ");
  Serial.print(currentSpeedRightMotor);
  Serial.print("\tdesiredSpeedRightMotor = ");
  Serial.print(desiredSpeedRightMotor);
  Serial.println("");

  analogWrite(RIGHT_MOTOR_EN, currentSpeedRightMotor);
}
