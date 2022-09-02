// Uses code examples from https://gist.github.com/hsiboy/11545fd0241ab60b567d for FastLED
// Uses code examples from https://medium.com/@werneckpaiva/how-to-read-rc-signal-with-arduino-using-flysky-ibus-73448bc924eb for IBus

#include <IBusBM.h>
#include "FastLED.h" // FastLED library for WS2812 RGB Stick http://fastled.io/

//LED Vars
#define LED_PIN 3              // Arduino pin number LED strip is connected to
#define NUM_LEDS 8             // Number of LEDs in strip
#define COLOR_ORDER GRB         // LED Color order
#define LED_TYPE WS2812B        // LED Strip Type
#define MAX_BRIGHTNESS 255      // Thats full on, watch the power!
#define MIN_BRIGHTNESS 32       // Set to a minimum of 25%

CRGB leds[NUM_LEDS]; // FastLED Library Init

IBusBM ibusRc;

HardwareSerial& ibusRcSerial = Serial1;
Serial_ & debugSerial = SerialUSB;

void setup() {
  ibusRc.begin(ibusRcSerial, IBUSBM_NOTIMER);   // Initialize the IBus connection to the receiver
  debugSerial.begin(74880);

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

  int valColor;
  int valBright;
  ibusRc.loop(); // call internal loop function to update the communication to the receiver 
  valColor = ibusRc.readChannel(2);     // Channel 3 Switch
  valBright = map(ibusRc.readChannel(3),1000,2000,0,255);    // Channel 4 Pot

  debugSerial.print("Channel 3: ");
  debugSerial.print(valColor);
  debugSerial.println();
  debugSerial.print("Channel 4: ");
  debugSerial.print(valBright);
  debugSerial.println();
  
//if ( valColor = 0)    // No value detected
//{
// for(int x = 0; x != NUM_LEDS; x++)
//  {
//  leds[x] = CRGB::Yellow;
//  FastLED.setBrightness(50);
//  FastLED.show();
//  }
//}

//else if (valColor = 1000)    // Switch high
//  {
//  for(int x = 0; x != NUM_LEDS; x++)
//    {
//    leds[x] = CRGB::Green;
//    FastLED.setBrightness(valBright);
//    FastLED.show();
//    }
//  }
  
//else if (valColor = 2000)    // Switch low
//  {
//  for(int x = 0; x != NUM_LEDS; x++)
//    {
//    leds[x] = CRGB::Red;
//    FastLED.setBrightness(valBright);
//    FastLED.show();
//    }
//  }
switch (valColor) {
  case 1000:
    for(int x = 0; x != NUM_LEDS; x++)
      {
      leds[x] = CRGB::Green;
      FastLED.setBrightness(valBright);
//      FastLED.show();
      }
    break;
  case 2000:
    for(int x = 0; x != NUM_LEDS; x++)
      {
      leds[x] = CRGB::Red;
      FastLED.setBrightness(valBright);
//      FastLED.show();
      }
    break;
  default:
   for(int x = 0; x != NUM_LEDS; x++)
    {
    leds[x] = CRGB::Yellow;
    FastLED.setBrightness(50);
//    FastLED.show();
    }
    break;
}  
      FastLED.show();
  delay(10);
}
