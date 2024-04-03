//
// fadeNeoWithouDelay
//
// This program fades the three colors of NeoPixel without using delay
// By default, each color goes from 0 to 255 in increments of 1
// but the red values can be changed with setRedValues(). Of course 
// similar functions for green and blue can also be written. This is 
// left as an exercise to the reader.

// 03 Apr 2024 - MS - Initial entry


#include <Adafruit_NeoPixel.h>

class NeoPixelFader
{
    int neoPixelPin;
    int numberOfPixels;
    int delayBetweenSteps; // this could be per each color too

    // these are initial values that can be
    // changed with setRedRange etc.
    //
    // really this should be in a sub-class
    // because they all do the same thing
    // just with different variables
    uint8_t redMinValue = 0;
    uint8_t redMaxValue = 255;
    uint8_t redCurrentValue = 0;
    uint8_t redIncrementAmount = 1;
    unsigned long redPreviousMillis = 0;

    uint8_t greenMinValue = 0;
    uint8_t greenMaxValue = 255;
    uint8_t greenCurrentValue = 0;
    uint8_t greenIncrementAmount = 1;
    unsigned long greenPreviousMillis = 0;

    uint8_t blueMinValue = 0;
    uint8_t blueMaxValue = 255;
    uint8_t blueCurrentValue = 0;
    uint8_t blueIncrementAmount = 1;
    unsigned long bluePreviousMillis = 0;

    Adafruit_NeoPixel pixels;

    // Constructor
  public:
    NeoPixelFader(int _neoPixelPin, int _numberOfPixels,
                  int _delayBetweenSteps)
    {
      neoPixelPin = _neoPixelPin;
      numberOfPixels = _numberOfPixels;
      delayBetweenSteps = _delayBetweenSteps;
      // currently every color gets the same delay
      // but this could also be configured individually

      pixels = Adafruit_NeoPixel(numberOfPixels, neoPixelPin, NEO_GRB + NEO_KHZ800);
    }

    void begin()
    {
      pixels.begin();
    }

    void setRedValues(
      uint8_t _redMinValue,
      uint8_t _redMaxValue,
      uint8_t _redCurrentValue,
      uint8_t _redIncrementAmount)
    {
      redMinValue = _redMinValue;
      redMaxValue = _redMaxValue;
      redCurrentValue = _redCurrentValue;
      redIncrementAmount = _redIncrementAmount;
    }

    void update()
    {
      updateRed();
      updateGreen();
      updateBlue();
    }

    // for debugging
    void print() {
      Serial.print("Red = ");
      Serial.print(redCurrentValue);
      Serial.print("\tGreen = ");
      Serial.print(greenCurrentValue);
      Serial.print("\tBlue = ");
      Serial.print(blueCurrentValue);
      Serial.println();
    }

    void updateRed() {
      unsigned long currentMillis = millis();
      if (currentMillis - redPreviousMillis >= delayBetweenSteps) {

        // calculate the next value of colors
        redCurrentValue += redIncrementAmount;

        // If we've reached the minimum or maximum, change direction
        if ((redCurrentValue >= redMaxValue) || (redCurrentValue <= redMinValue)) {
          redIncrementAmount = -redIncrementAmount;
        }

        // update the NeoPixels
        for (int i = 0; i < numberOfPixels; i++) {
          pixels.setPixelColor(i, redCurrentValue, greenCurrentValue, blueCurrentValue);
        }
        pixels.show();

        // update previousMillis
        redPreviousMillis = currentMillis;
      }
    }

    void updateGreen() {
      unsigned long currentMillis = millis();
      if (currentMillis - greenPreviousMillis >= delayBetweenSteps) {

        // calculate the next value of colors
        greenCurrentValue += greenIncrementAmount;

        // If we've reached the minimum or maximum, change direction
        if ((greenCurrentValue >= greenMaxValue) || (greenCurrentValue <= greenMinValue)) {
          greenIncrementAmount = -greenIncrementAmount;
        }

        // update the NeoPixels
        for (int i = 0; i < numberOfPixels; i++) {
          pixels.setPixelColor(i, redCurrentValue, greenCurrentValue, blueCurrentValue);
        }
        pixels.show();

        // update previousMillis
        greenPreviousMillis = currentMillis;
      }
    }

    void updateBlue()
    {
      unsigned long currentMillis = millis();
      if (currentMillis - bluePreviousMillis >= delayBetweenSteps) {

        // calculate the next value of colors
        blueCurrentValue += blueIncrementAmount;

        // If we've reached the minimum or maximum, change direction
        if ((blueCurrentValue >= blueMaxValue) || (blueCurrentValue <= blueMinValue)) {
          blueIncrementAmount = -blueIncrementAmount;
        }

        // update the NeoPixels
        for (int i = 0; i < numberOfPixels; i++) {
          pixels.setPixelColor(i, redCurrentValue, greenCurrentValue, blueCurrentValue);
        }
        pixels.show();

        // update previousMillis
        bluePreviousMillis = currentMillis;
      }
    }
};


// pin, number of pixels, delay between steps
NeoPixelFader cloud1(A5, 6, 10); 

void setup() {
  Serial.begin(9600);

  // parameters are
  // redMinValue, redMaxValue, redCurrentValue,redIncrementAmount)
  cloud1.setRedValues( 50, 100, 100, -1);
  cloud1.begin();
}

void loop() {
  cloud1.update();
  // cloud1.print();
}
