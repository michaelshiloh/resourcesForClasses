//
// manyServosNoDelay
//
// This program sweeps 8 servos without using delay()
//
// Based on the excellent Adafruit tutorial
// "Multi-tasking the Arduino - Part 1"
// by Bill Earl


// 05 Apr 2024 - MS - Initial entry

#include "Servo.h"

class Sweeper
{
    Servo servo;          // the servo object
    int updateInterval;        // interval between updates
    int degreesPerInterval = 1; // degrees to move for each interval
    int maxPos = 180;
    int minPos = 0;
    int pos;              // current servo position
    unsigned long lastUpdate;   // last update of position

  public:
    // interval, steps, min, max, init
    Sweeper(int _updateInterval,
            int _degreesPerInterval,
            int _minPos,
            int _maxPos,
            int _pos)
    {
      updateInterval = _updateInterval;
      degreesPerInterval = _degreesPerInterval;
      minPos = _minPos;
      maxPos = _maxPos;
      pos = _pos;
    }

    void Attach(int pin)
    {
      servo.attach(pin);
    }

    void Detach()
    {
      servo.detach();
    }

    void Update()
    {
      if ((millis() - lastUpdate) > updateInterval) // time to update
      {
        lastUpdate = millis();
        pos += degreesPerInterval;
        servo.write(pos);
        Serial.println(pos);
        if ((pos >= maxPos) || (pos <= minPos)) // end of sweep
        {
          // reverse direction
          degreesPerInterval = -degreesPerInterval;
        }
      }
    }
};


// Arguments are interval, steps, min, max, initial postion
Sweeper allTheSweepers[] = {
  Sweeper (15, 1, 0, 180, 0), // traditional range
  Sweeper (100, 1, 80, 100, 90), // very slow and very small motion
  Sweeper (30, 20, 0, 180, 0), // big steps
  Sweeper (15, -1, 30, 180, 180), // start going backwards
  Sweeper (15, 1, 0, 180, 0), // traditional range
  Sweeper (100, 1, 80, 100, 90), // very slow and very small motion
  Sweeper (30, 20, 0, 180, 0), // big steps
  Sweeper (15, -1, 30, 180, 180) // start going backwards
};

// These really should be in an array
void setup()
{
  allTheSweepers[0].Attach(A0);
  allTheSweepers[1].Attach(A1);
  allTheSweepers[2].Attach(A2);
  allTheSweepers[3].Attach(A3);
  allTheSweepers[4].Attach(2);
  allTheSweepers[5].Attach(4);
  allTheSweepers[6].Attach(7);
  allTheSweepers[7].Attach(8);
}


void loop()
{
  for (int i = 0; i < 8; i++) {
    allTheSweepers[i].Update();
  }
}
