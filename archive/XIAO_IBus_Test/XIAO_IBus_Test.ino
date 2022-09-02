// Uses code examples from https://gist.github.com/hsiboy/11545fd0241ab60b567d for FastLED
// Uses code examples from https://medium.com/@werneckpaiva/how-to-read-rc-signal-with-arduino-using-flysky-ibus-73448bc924eb for IBus

#include <IBusBM.h>
#include "FastLED.h" // FastLED library for WS2812 RGB Stick http://fastled.io/

//LED Vars
#define LED_PIN 3              // Arduino pin number LED strip is connected to
#define NUM_LEDS 4             // Number of LEDs in strip
#define COLOR_ORDER GRB         // LED Color order
#define LED_TYPE WS2812B        // LED Strip Type
#define MAX_BRIGHTNESS 164      // Thats full on, watch the power!
#define MIN_BRIGHTNESS 32       // Set to a minimum of 25%

CRGB leds[NUM_LEDS]; // FastLED Library Init

IBusBM ibusRc;

HardwareSerial& ibusRcSerial = Serial1;
//Serial_ & debugSerial = SerialUSB;

void setup() {
//debugSerial.begin(115200);
  ibusRc.begin(ibusRcSerial);

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.setBrightness(MAX_BRIGHTNESS);

  FastLED.clear(); // Clear the RGB Stick LEDs
  FastLED.setBrightness(50);
  FastLED.show();
  
  pinMode(LED_PIN, OUTPUT); // Set RGB Stick UNO pin to an OUTPUT
}

// Read the number of a given channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(byte channelInput, int minLimit, int maxLimit, int defaultValue){
  uint16_t ch = ibusRc.readChannel(channelInput);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

// Red the channel and return a boolean value
bool redSwitch(byte channelInput, bool defaultValue){
  int intDefaultValue = (defaultValue)? 100: 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);

  delay(3000); // in case we do something stupid. We dont want to get locked out.


//  // Light up starting LED's
//  for(int x = 0; x != NUM_LEDS; x++) {
//    leds[x] = CRGB::Red;
//  }

}

void loop() {
  //int mappedValue = map(analogRead(brightnessInPin), 0, 1023, 0, 255);    //Map values - map(value, fromLow, fromHigh, toLow, toHigh)
  //FastLED.setBrightness(constrain(mappedValue, MIN_BRIGHTNESS, MAX_BRIGHTNESS));
  
 // for (byte i = 0; i<5; i++){
//   int value = readChannel(3, -100, 100, 0);
//    debugSerial.print("Ch");
//    debugSerial.print(i + 1);
//    debugSerial.print(": ");
//    debugSerial.print(value);
//    debugSerial.print(" ");
  int value;
  value = ibusRc.readChannel(2);
  
if ( value < 1000)    // No value detected
{
 for(int x = 0; x != NUM_LEDS; x++)
  {
  leds[x] = CRGB::Yellow;
  FastLED.show();
  }
}

else if ((value > 1000) && (value < 1600))    // Switch low
  {
  for(int x = 0; x != NUM_LEDS; x++)
    {
    leds[x] = CRGB::Red;
    FastLED.show();
    }
  }
else if ((value > 1600) && (value < 2100))    // Switch high
  {
  for(int x = 0; x != NUM_LEDS; x++)
    {
    leds[x] = CRGB::Green;
    FastLED.show();
    }
  }


//  }
//  debugSerial.print("Ch6: ");
//  debugSerial.print(redSwitch(4, false));
//  debugSerial.println();
  delay(10);
}
