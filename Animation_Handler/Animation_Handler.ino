
//#define VARIABLE_BRIGHTNESS
//#define FIXED_BRIGHTNESS

#include <FastLED.h>

#define DATA_PIN 7
#define MAX_BRIGHTNESS 127
#define NUM_LEDS 256

CRGB matrixLEDs[NUM_LEDS];          //Instantiate CRGB object, holds LED info
byte ledBrightness = MAX_BRIGHTNESS;
byte ledHue = 96;                   //should be green
byte ledSat = 255;

/*FRAME INFO BELOW*/

int goal_frames_leds[][] =          //2D array for holding LED locations per frame
{
  {112,143},
  {111,112,113,142,143,144},
  {111,112,113,142,143,144,80,110,114,141,145,175}
};  //3 frames, animation for left goal score

int goal_frames_brightness[][]=
{
  {MAX_BRIGHTNESS, MAX_BRIGHTNESS}
};

int totalFrames = 3;
int frameDelayMS = 500;

void setup() 
{
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B,DATA_PIN,GRB>(matrixLEDs,NUM_LEDS);
  FastLED.setBrightness(MAX_BRIGHTNESS);
  
}

void loop() 
{
  

  /*
   * Design choice: Do we clear all leds each loop and set all required leds, or
   * do we update new/changed LEDs and leave others untouched?
   * 
   */
  
  for(int currentFrame = 0; currentFrame < totalFrames; currentFrame++)
  {
    FastLED.clear();
    
    for(int ledCount = 0 ; ledCount < sizeOf(goal_frames_leds[currentFrame]))/4; ledCount++)
    {
      matrixLEDs[goal_frames_LEDs[currentFrame][ledCount]] = CHSV(ledHue, ledSat, ledBrightness);
    }

    FastLED.show();

    //delay based off frame delay
    delay(frameDelayMS);
  }

  
  
  /*
  ifdef FIXED_BRIGHTNESS
  = CHSV(asdf,asdfa,brightness)
  endif
  = CHSV(asdf,asdf,brightnessArray[0])*/
}
