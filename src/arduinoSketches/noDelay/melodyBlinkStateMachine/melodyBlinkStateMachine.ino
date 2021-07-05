/*

  Example of a state machine which blinks LEDs and plays a melody

  circuit:
  See the section labeled "Circuit" below

  Behavior:
  See the section labeled "States" below

  by Michael Shiloh
  Motivated by students in Introduction to Interactive Media, Fall 2018
  New York University Abu Dhabi

  Revision log:
  04 Jul 2021 - ms - created

  Based on
    Melody by Tom Igoe
    Blink Without Delay by David A. Mellis
    toneMelodyWithoutDelay by Michael Shiloh
    Multi-tasking the Arduino By Bill Earl (on the Adafruit website)

  This example code is in the public domain.

*/

// Circuit:
const int SPKRPIN = 2;
const int BLUESWITCHPIN = 4;
const int GREENSWITCHPIN = 7;
const int BLUELEDPIN = 8;


#include "pitches.h"

// In some future version, perhaps the notes and durations could be provided in the constructor

const int MELODYLENGTH = 8;
// notes in the melody:
int melody[MELODYLENGTH] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
// note values: 4 = quarter note, 8 = eighth note, etc.:
int noteValues[MELODYLENGTH] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

class MelodyPlayer
{
    int thisNote, spkrPin, timeToNextNote;
    boolean melodyIsPlaying;
    unsigned long thisNoteStartedAt;
  public:

    // Constructor
    MelodyPlayer(int _spkrPin) {
      spkrPin = _spkrPin;
      thisNoteStartedAt = 0;
      melodyIsPlaying = false;
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
      if ( thisNote >= MELODYLENGTH ) {
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

class Flasher
{
    // Class Member Variables
    // These are initialized at startup
    int ledPin;      // the number of the LED pin
    long OnTime;     // milliseconds of on-time
    long OffTime;    // milliseconds of off-time

    // These maintain the current state
    int ledState;                 // ledState used to set the LED
    unsigned long previousMillis;   // will store last time LED was updated
    boolean flasherIsBlinking;

    // Constructor - creates a Flasher
    // and initializes the member variables and state
  public:
    Flasher(int pin)
    {
      ledPin = pin;
      pinMode(ledPin, OUTPUT);


      ledState = LOW;
      previousMillis = 0;
    }

    void setRate(int _OnTime, int _OffTime) {
      OnTime = _OnTime;
      OffTime = _OffTime;
    }

    void stopBlinking() {
      flasherIsBlinking = false;
      ledState = LOW;
      digitalWrite(ledPin, ledState);
    }

    void startBlinking() {
      flasherIsBlinking = true;
    }

    boolean ledIsOn() {
      return (ledState == HIGH);
    }

    void update()
    {
      if (!flasherIsBlinking) return;

      // check to see if it's time to change the state of the LED
      unsigned long currentMillis = millis();

      if ((ledState == HIGH) && (currentMillis - previousMillis >= OnTime))
      {
        ledState = LOW;  // Turn it off
        previousMillis = currentMillis;  // Remember the time
        digitalWrite(ledPin, ledState);  // Update the actual LED
      }
      else if ((ledState == LOW) && (currentMillis - previousMillis >= OffTime))
      {
        ledState = HIGH;  // turn it on
        previousMillis = currentMillis;   // Remember the time
        digitalWrite(ledPin, ledState);   // Update the actual LED
      }
    }
};


Flasher myFlasher(BLUELEDPIN);
MelodyPlayer myTune(SPKRPIN);
int state;

void setup() {
  Serial.begin(9600);
  state = 99;
}

void loop() {

  /* States
     99 - everything off; next state: 1
     1 - start blinking LED slowly; next state: 2
     2 - if blue switch pressed, start the melody, and blink the LED faster; next state = 4
     4 - when the melody finishes, blink the LED slowly, next state = 7
     7 - if the blue switch is pressed, next state = 9
       - if the green switch is pressed, stop blinking, next state = 8
     8 - next state = 8
     9 - if the blue switch is NOT pressed, next state = 1
  */

  Serial.print("Current state = ");
  Serial.println(state);

  switch (state) {
    case 99:
      myFlasher.stopBlinking();
      myTune.stopPlaying();
      state = 1;
      break;
    case 1:
      myFlasher.setRate(1000, 1000);
      myFlasher.startBlinking();
      state = 2;
      break;
    case 2:
      if (digitalRead(BLUESWITCHPIN) == HIGH) {
        myTune.startPlaying();
        myFlasher.setRate(100, 100);
        myFlasher.startBlinking();
        state = 4;
      }
      break;
    case 4:
      if (!myTune.isPlaying()) {
        myFlasher.setRate(1000, 1000);
        myFlasher.startBlinking();
        state = 7;
      }
      break;
    case 7:
      if (digitalRead(BLUESWITCHPIN) == HIGH) {
        state = 9;
      }
      if (digitalRead(GREENSWITCHPIN) == HIGH) {
        myFlasher.stopBlinking();
        state = 8;
      }
      break;
    case 8:
      break;
    case 9:
      if (digitalRead(BLUESWITCHPIN) != HIGH) {
        state = 1;
      }
      break;
    default:
      Serial.println("invalid state, hanging");
      while (true);
      break;
  }

  // Don't forget to update everything!
  myTune.update();
  myFlasher.update();

}
