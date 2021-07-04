/*

 Play a melody without using delay()

  circuit:
  - speaker (piezo or voice coil) on digital pin 3

  by Michael Shiloh
  Motivated by students in Introduction to Interactive Media, Fall 2018
  New York University Abu Dhabi

  Revision log:
  10 October 2018 created

  Based on
    Melody by Tom Igoe
    Blink Without Delay by David A. Mellis

  This example code is in the public domain.

  https://github.com/michaelshiloh/toneMelodyAndBlinkWithoutDelay

*/

#include "pitches.h"

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

unsigned long previousMillis = 0;
int thisNote = 0;
int pauseBetweenNotes;

void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= pauseBetweenNotes) {
    previousMillis = currentMillis;

    int noteDuration = 1000 / noteDurations[thisNote];
    tone(3, melody[thisNote], noteDuration);

    pauseBetweenNotes = noteDuration * 1.30;

    thisNote++;
    if ( thisNote >= 8 ) {
      thisNote = 0;
    }
  }
}

void setup() {
}
