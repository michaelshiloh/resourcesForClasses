/*
  Play a melody and blink an LED without using delay()

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

const int ledPin = LED_BUILTIN;
const int spkrPin = 3;

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};


/* Global variables to track progress through the melody */

// When was the current note started
unsigned long currentNoteStartedAt = 0;

// which note is being played
int thisNote = 0;

// Note play time plus the pause between notes
int millisToNextNote = 0;


/* Global variables to track blinking the LED */

int currentLedState = LOW;
unsigned long currentLedStateStartedAt = 0;
long ledDelay = 100;

void loop() {

  // What time is it currently?
  unsigned long currentMillis = millis();

  // Is it time to play the next note in the melody?
  if (currentMillis - currentNoteStartedAt >= millisToNextNote) {

    // Yes it is. Calculate the note duration
    int noteDuration = 1000 / noteDurations[thisNote];

    // Start the note playing
    tone(3, melody[thisNote], noteDuration);

    // Calculate the time we should wait before we start the next note
    // which is the note duration plus a short pause between notes
    millisToNextNote = noteDuration * 1.30;

    // Note the time we started playing this note
    currentNoteStartedAt = currentMillis;

    // Advance to the next note for next time
    thisNote++;

    // If we reach the end of the melody start over again
    if ( thisNote >= 8 ) {
      thisNote = 0;
    }
  }

  // Is it time to change the state of the LED?
  if (currentMillis - currentLedStateStartedAt >= ledDelay) {

    // Yes it is.
    // If the LED is off change the state to on and vice-versa
    if (currentLedState == LOW) {
      currentLedState = HIGH;
    } else {
      currentLedState = LOW;
    }

    // set the LED to match the updated current state
    digitalWrite(ledPin, currentLedState);

    // Record the time at which we started the current state
    currentLedStateStartedAt = currentMillis;
  }


  /* 
   *  Here you can put other activities and they will not be delayed
   *  because there is no use of delay!
   */
  
}

void setup() {
}
