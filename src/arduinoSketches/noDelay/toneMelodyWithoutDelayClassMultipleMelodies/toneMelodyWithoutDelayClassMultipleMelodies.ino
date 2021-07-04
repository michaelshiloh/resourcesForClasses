/*

  Play a melody without using delay()
  Melody player is in a class
  Melody player can play different tunes

  circuit:
  - speaker (piezo or voice coil) on digital pin 3

  by Michael Shiloh
  Motivated by students in Introduction to Interactive Media, Fall 2018
  New York University Abu Dhabi

  Revision log:
  04 Jul 2021 testing of passing array by reference

  Based on
    Melody by Tom Igoe
    Blink Without Delay by David A. Mellis
    toneMelodyWithoutDelay by Michael Shiloh

  This example code is in the public domain.

  https://github.com/michaelshiloh/toneMelodyAndBlinkWithoutDelay

*/

#include "pitches.h"

const int SPKRPIN = 9;
// In some future version, perhaps the notes and durations could be provided in the constructor
// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

int melody2[] = {
  NOTE_C4, NOTE_C4, NOTE_C4, NOTE_A3, NOTE_G3, 0, NOTE_G3, NOTE_C4
};

// note values: 4 = quarter note, 8 = eighth note, etc.:
int noteValues[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

class MelodyPlayer
{
    int thisNote, spkrPin, timeToNextNote;
    boolean melodyIsPlaying;
    unsigned long thisNoteStartedAt;
    int* melody;

  public:

    // Constructor
    MelodyPlayer() {
      thisNoteStartedAt = 0;
      melodyIsPlaying = false;
    }

    void setSpkrPin(int _spkrPin) {
      spkrPin = _spkrPin;
    }

    void setMelody(int *_melody) {
      melody = _melody;
    }

    void startPlaying() {
      if (melodyIsPlaying) return;
      Serial.println("startPlaying");
      thisNote = 0; // Alternately, we could provide a different starting point
      melodyIsPlaying = true;
    }

    void stopPlaying() {
      Serial.println("stopPlaying");
      melodyIsPlaying = false;
      noTone(spkrPin);
    }

    boolean isPlaying() {
      return (melodyIsPlaying);
    }

    void update() {

      // First deal with reasons not to play

      // if we're not play, don't do anything
      if (!melodyIsPlaying) {
        //        Serial.print("melodyIsPlaying is ");
        //        Serial.println(melodyIsPlaying);
        return;
      }

      // If we've reached the end of the tune, don't do anything
      if ( thisNote >= 8 ) {
        melodyIsPlaying = false;
        thisNote = 0; // in case we want to play again
        return;
      }

      // Apparently we're playing, so check whether it's time to progress
      // to the next note

      unsigned long now = millis();
      if (now - thisNoteStartedAt >= timeToNextNote) {

        Serial.print("playing note ");
        Serial.println(thisNote);

        // Calculate note duration from the
        int ThisNoteDuration = 1000 / noteValues[thisNote];
        tone(spkrPin, melody[thisNote], ThisNoteDuration);

        timeToNextNote = ThisNoteDuration * 1.30;
        thisNote++;
        thisNoteStartedAt = now;
      }
    }
};

MelodyPlayer myTune;
const int STARTPIN = 2;
const int STOPPIN = 7;

void loop() {

  if (digitalRead(STARTPIN)) {
    myTune.startPlaying();
  }

  if (digitalRead(STOPPIN)) {
    myTune.stopPlaying();
    myTune.setMelody(melody2);
  }

  myTune.update();

}

void setup() {
  Serial.begin(9600);
  myTune.setSpkrPin(SPKRPIN);
  myTune.setMelody(melody);

}
