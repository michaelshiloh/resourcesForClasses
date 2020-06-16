/*
   derived from
   https://ledhacker.blogspot.com/2011/12/led-candle-light-flicker-with-arduino.html?m=1
   with ideas from
   

   Each LED has 5 flickerStates

   State 0: Resetting for a new flicker (generate new random values)
   State 1: Ramping from low to high
   State 2: Pause at the brightest level
   State 3: Ramping from high to low
   State 4: Pause at the lowest level
*/

// the start of the flicker (low)
static int flicker_low_min = 0;
static int flicker_low_max = 10;

// the end value of the flicker (high)
static int flicker_high_min = 230;
static int flicker_high_max = 255;

// delay between each low-high-low cycle
// low->high |flicker_hold| high->low
// i.e. pause at brightest light
static int flicker_holdAtHigh_min = 100; // milliseconds
static int flicker_holdAtHigh_max = 2000; // milliseconds

// delay after each low-high-low cycle
// low->high->low |flicker_pause| low->high...
// i.e. pause at dimmest light
static int flicker_holdAtLow_min = 100; // milliseconds
static int flicker_holdAtLow_max = 2000;  // milliseconds

// delay low to high and high to low cycle
// i.e. pause at each brightness step
static int flicker_holdAtStep_min = 1; 
static int flicker_holdAtStep_max = 1;


class Flickerer
{

    // Constructor - creates a Flickerer
    // and initializes the member variables and flickerState
  public:
    Flickerer(int pin )
    {
      ledPin = pin;
      pinMode(ledPin, OUTPUT);

      flickerState = 0;
      ledLevel = 0;
      previousMillis = 0;
      flicker_reset();
    } // Constructor

    void Update()
    {
//      Serial.print(flickerState);
//      Serial.print('\t');
//      Serial.print(ledLevel);
//      Serial.println();
      
      if (flickerState == 0) {// resetting for a new flicker
        flicker_reset();

        // Enter flickerState 1
        flickerState = 1; // flickerState 1 is ramping from low to high

        // Starting light level
        ledLevel = flicker_random_low_start;
        analogWrite(ledPin, ledLevel);  // Do the LED

        // Record time
        previousMillis = millis();

        // Set correct interval
        interval = flicker_random_DelayAtStepRampingUp;
      }

      if (flickerState == 1) { // flickerState 1 is ramping from low to high
        if (millis() - previousMillis >= interval)
        {
          ledLevel ++;                    // bump up light level
          analogWrite(ledPin, ledLevel);  // Do the LED
          previousMillis = millis(); // Remember the time

          // if we've reached the final light level, go to the next flickerState
          if (ledLevel >= flicker_random_high) {

            // enter flickerState 2
            flickerState = 2; // flickerState 2 is the pause at the brightest level

            // no change to ledLevel
            interval =  flicker_random_holdAtHigh;
          }
        }
      } // end of flickerState 1

      if (flickerState == 2) { // flickerState 2 is the pause at the brightest level
        if (millis() - previousMillis >= interval)
        {
          // when the time is up, go to the next flickerState
          // enter flickerState 3
          flickerState = 3; // flickerState 3 is ramping from high to low

          // Starting light level
          ledLevel = flicker_random_high; // strictly speaking not necessary
          analogWrite(ledPin, ledLevel);  // Do the LED

          // Record time
          previousMillis = millis();

          // Set correct interval
          interval = flicker_random_DelayAtStepRampingDown;
        }
      }

      if (flickerState == 3) { // flickerState 3 is ramping from high to low
        if (millis() - previousMillis >= interval)
        {
          ledLevel --;                    // bump up light level
          analogWrite(ledPin, ledLevel);  // Do the LED
          previousMillis = millis(); // Remember the time

          // if we've reached the final light level, go to the next flickerState
          if (ledLevel <= flicker_random_low_end) {

            // enter flickerState 4
            flickerState = 4; // flickerState 4 is the pause at the dimmest level

            // no change to ledLevel
            interval =  flicker_random_holdAtLow;
          }
        }
      } // end of flickerState 3


      if (flickerState == 4) { // flickerState 4 is the pause at the dimmest level
        if (millis() - previousMillis >= interval)
        {
          // when the time is up, reset to start at state zero
          flicker_reset();
        }
      }
      
    } // end of Update

  private:

    // Class Member Variables
    // These are initialized at startup
    int ledPin;      // the pin being controlled by this object

    int flicker_random_low_start; // low value at beginning
    int flicker_random_low_end;   // low value at end
    int flicker_random_high;      // high value
    int flicker_random_DelayAtStepRampingUp;//
    int flicker_random_DelayAtStepRampingDown;
    int flicker_random_holdAtLow;
    int flicker_random_holdAtHigh;

    // The current flickerState of this object
    int flickerState;               // Current flickerState of this object
    int ledLevel;                   // Current LED light level
    unsigned long previousMillis;   // Last time we did something
    unsigned long interval;         // Interval to next time we should do something


    void flicker_reset() {
      // random low light levels (one at beginning, one at end)
      flicker_random_low_start = random(flicker_low_min, flicker_low_max);
      flicker_random_low_end = random(flicker_low_min, flicker_low_max);

      // random high light level
      flicker_random_high = random(flicker_high_min, flicker_high_max);

      // How long to hold at low
      flicker_random_holdAtLow = random(flicker_holdAtLow_min, flicker_holdAtLow_max);

      // How long to hold at high
      flicker_random_holdAtHigh = random(flicker_holdAtHigh_min, flicker_holdAtHigh_max);

      // random time for speed
      flicker_random_DelayAtStepRampingUp = random(flicker_holdAtStep_min, flicker_holdAtStep_max);
      flicker_random_DelayAtStepRampingDown = random(flicker_holdAtStep_min, flicker_holdAtStep_max);

      flickerState = 0; // not sure this is wise or necessary
    } // flicker_reset
}; // end of Flickerer class

// Do this for each LED you use
Flickerer led1(3); // put the LED pin number in the parenthesis
Flickerer led2(5);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  // Do this for each LED you have
  led1.Update();
  led2.Update();
}


