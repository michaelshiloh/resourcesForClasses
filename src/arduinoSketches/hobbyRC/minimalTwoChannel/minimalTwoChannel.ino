
/*
   Minimal RC receiver decoding
   Using two interrupt pins for input

   Change log:

   1 May 2022 - MS - Initial entry

   Based on
   https://www.instructables.com/Rc-Controller-for-Better-Control-Over-Arduino-Proj/
   from geeky singh 14th dec 2015 for instructables.com

   This code is in the public domain

*/

// Pins 2 and 3 are the hardware interrupt pins
#define THROTTLE_IN_PIN 2
#define STEERING_IN_PIN 3

// These bit flags are set in bUpdateFlagsShared to indicate which
// channels have new signals
#define THROTTLE_FLAG 1
#define STEERING_FLAG 2

// holds the update flags defined above
volatile uint8_t bUpdateFlagsShared;

// shared variables are updated by the ISR and read by loop.
// In loop we immediatley take local copies so that the ISR can keep ownership of the
// shared ones. To access these in loop
// we first turn interrupts off with noInterrupts
// we take a copy to use in loop and the turn interrupts back on
// as quickly as possible, this ensures that we are always able to receive new signals
volatile uint16_t unThrottleInShared;
volatile uint16_t unSteeringInShared;

// These are used to record the rising edge of a pulse in the calcInput functions
// They do not need to be volatile as they are only used in the ISR. If we wanted
// to refer to these in loop and the ISR then they would need to be declared volatile
uint32_t ulThrottleStart;
uint32_t ulSteeringStart;



unsigned long pulse_time  ;

void setup()
{
  Serial.begin(9600);
  Serial.println("hello");

  // Attach the ISR to the interrupt, specifying that we want an interrupt
  // on any change of the signal (i.e. both rising and falling)
  attachInterrupt(0 /* INT0 = THROTTLE_IN_PIN */, calcThrottle, CHANGE);
  attachInterrupt(1 /* INT1 = STEERING_IN_PIN */, calcSteering, CHANGE);

  pulse_time = millis() ;
}

void loop()
{
  // create local variables to hold a local copies of the channel inputs
  // these are declared static so that thier values will be retained
  // between calls to loop.
  static uint16_t unThrottleIn;
  static uint16_t unSteeringIn;
  // local copy of update flags
  static uint8_t bUpdateFlags;

  // check shared update flags to see if any channels have a new signal
  if (bUpdateFlagsShared)
  {
    noInterrupts(); // turn interrupts off quickly while we take local copies of the shared variables
    pulse_time = millis() ;
    // take a local copy of which channels were updated in case we need to use this in the rest of loop
    bUpdateFlags = bUpdateFlagsShared;

    // in the current code, the shared values are always populated
    // so we could copy them without testing the flags
    // however in the future this could change, so lets
    // only copy when the flags tell us we can.

    if (bUpdateFlags & THROTTLE_FLAG)
    {
      unThrottleIn = unThrottleInShared;
    }

    if (bUpdateFlags & STEERING_FLAG)
    {
      unSteeringIn = unSteeringInShared;
    }

    // clear shared copy of updated flags as we have already taken the updates
    // we still have a local copy if we need to use it in bUpdateFlags
    bUpdateFlagsShared = 0;

    interrupts(); // we have local copies of the inputs, so now we can turn interrupts back on
    // as soon as interrupts are back on, we can no longer use the shared copies, the interrupt
    // service routines own these and could update them at any time. During the update, the
    // shared copies may contain junk. Luckily we have our local copies to work with :-)
  }


  // do any processing from here onwards
  // only use the local values unAuxIn, unThrottleIn and unSteeringIn, the shared
  // variables unAuxInShared, unThrottleInShared, unSteeringInShared are always owned by
  // the interrupt routines and should not be used in loop

  // we are checking to see if the channel value has changed, this is indicated
  // by the flags. For the simple pass through we don't really need this check,
  // but for a more complex project where a new signal requires significant processing
  // this allows us to only calculate new values when we have new inputs, rather than
  // on every cycle.
  if (bUpdateFlags & THROTTLE_FLAG)
  {
    /* I'm not sure what this means (from geeky singh's code):
      // A good idea would be to check the before and after value,
      // if they are not equal we are receiving out of range signals
      // this could be an error, interference or a transmitter setting change
      // in any case its a good idea to at least flag it to the user somehow
    */

    // Optional
    // unThrottleIn = constrain(unThrottleIn, unThrottleMin, unThrottleMax);
  }

  if (bUpdateFlags & STEERING_FLAG)
  {
    //unSteeringIn = constrain(unSteeringIn, unSteeringMin, unSteeringMax);
  }

  // Clear the flags
  bUpdateFlags = 0;

  Serial.print("throttle = ");
  Serial.print(unThrottleIn);
  Serial.print("\tsteering = ");
  Serial.print(unSteeringIn);
  Serial.println();
}


// simple interrupt service routine
void calcThrottle()
{
  // if the pin is high, its a rising edge of the signal pulse, so lets record its value
  if (digitalRead(THROTTLE_IN_PIN) == HIGH)
  {
    ulThrottleStart = micros();
  }
  else
  {
    // else it must be a falling edge, so lets get the time and subtract the time of the rising edge
    // this gives use the time between the rising and falling edges i.e. the pulse duration.
    unThrottleInShared = (uint16_t)(micros() - ulThrottleStart);
    // use set the throttle flag to indicate that a new throttle signal has been received
    bUpdateFlagsShared |= THROTTLE_FLAG;
  }
}

void calcSteering()
{
  if (digitalRead(STEERING_IN_PIN) == HIGH)
  {
    ulSteeringStart = micros();
  }
  else
  {
    unSteeringInShared = (uint16_t)(micros() - ulSteeringStart);
    bUpdateFlagsShared |= STEERING_FLAG;
  }
}
