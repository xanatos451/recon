// Uses code examples from https://gist.github.com/hsiboy/11545fd0241ab60b567d for FastLED
// Uses code examples from https://medium.com/@werneckpaiva/how-to-read-rc-signal-with-arduino-using-flysky-ibus-73448bc924eb for IBus

#include <IBusBM.h>
//#include <Adafruit_NeoPixel.h>

#include "FastLED.h" // FastLED library for WS2812 RGB Stick http://fastled.io/

//LED Vars
#define LED_PIN 3             // Arduino pin number LED strip is connected to
#define NUM_LEDS 8            // Number of LEDs in strip
#define COLOR_ORDER RGBW       // LED Color order
#define LED_TYPE SK6812      // LED Strip Type
#define MAX_BRIGHTNESS 255    // Thats full on, watch the power!
#define MIN_BRIGHTNESS 0      // Set to a minimum of 25%
#define MAX_SPEED 1000        // Maximum Animation Speed
#define MIN_SPEED 10          // Minimum Animation Speed
//#define UPDATES_PER_SECOND 100


CRGB leds[NUM_LEDS]; // FastLED Library Init
CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

IBusBM ibusRc;    // init IBUS library
HardwareSerial& ibusRcSerial = Serial1;   // IBUS communication channel

Serial_ & debugSerial = SerialUSB;    // Used for debugging via serial monitor




void setup() {
 ibusRc.begin(ibusRcSerial, IBUSBM_NOTIMER);   // Initialize the IBus connection to the receiver
 debugSerial.begin(74880);    // Used for debugging via serial monitor

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
//  FastLED.setBrightness(150);

//  FastLED.clear(); // Clear the RGB Stick LEDs
//  FastLED.setBrightness(MIN_BRIGHTNESS);

//  currentPalette = RainbowColors_p;
//  currentBlending = LINEARBLEND;

//  FastLED.show();
  
//  pinMode(LED_PIN, OUTPUT); // Set RGB Stick UNO pin to an OUTPUT

//      currentPalette = RainbowColors_p;
//    currentBlending = LINEARBLEND;
}

// Read the number of a given channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(byte channelInput, int minLimit, int maxLimit, int defaultValue){
  ibusRc.loop(); // call internal loop function to update the communication to the receiver
  uint16_t ch = ibusRc.readChannel(channelInput);
  if (ch < 1000) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

//// Red the channel and return a boolean value
//bool redSwitch(byte channelInput, bool defaultValue){
//  int intDefaultValue = (defaultValue)? 100: 0;
//  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
//  return (ch > 50);
//
//  delay(3000); // in case we do something stupid. We dont want to get locked out.


//  // Light up starting LED's
//  for(int x = 0; x != NUM_LEDS; x++) {
//    leds[x] = CRGB::Red;
//  }

//}

void loop() {
  //int mappedValue = map(analogRead(brightnessInPin), 0, 1023, 0, 255);    //Map values - map(value, fromLow, fromHigh, toLow, toHigh)
  //FastLED.setBrightness(constrain(mappedValue, MIN_BRIGHTNESS, MAX_BRIGHTNESS));
  
 // for (byte i = 0; i<5; i++){
//   int value = readChannel(3, -100, 100, 0);

//  int valColor;
//  int valBright;
 

//  int valBright = map(ibusRc.readChannel(2),1000,2000,MIN_BRIGHTNESS,MAX_BRIGHTNESS);   // Channel 3 Left Stick (Up/Down)
//  int valHue = map(ibusRc.readChannel(4),1000,2000,MIN_BRIGHTNESS,MAX_BRIGHTNESS);      // Channel 5 Pot (VrA)
//  int valSpeed = map(ibusRc.readChannel(5),1000,2000,MIN_SPEED,MAX_SPEED);    // Channel 6 Pot (VrB)
//  int valBlending = ibusRc.readChannel(7);     // Channel 7 Switch (SwA)
//  int valPalette = ibusRc.readChannel(8);     // Channel 9 Switch (SwA)
//int valColor = ibusRc.readChannel(6);
//readChannel(i, -100, 100, 0);

  int valBright = map(readChannel(2, 1000, 2000, 1000), 1000, 2000, MIN_BRIGHTNESS, MAX_BRIGHTNESS);   // Channel 3 Left Stick (Up/Down)
  int valHue = map(readChannel(4, 1000, 2000, 1000), 1000, 2000, MIN_BRIGHTNESS, MAX_BRIGHTNESS);      // Channel 5 Pot (VrA)
  int valSpeed = map(readChannel(5, 1000, 2000, 1000), 1000, 2000, MIN_SPEED, MAX_SPEED);    // Channel 6 Pot (VrB)
  int valBlending = readChannel(7, 1000, 2000, 1000);     // Channel 7 Switch (SwA)
  int valPalette = readChannel(8, 1000, 2000, 1000);     // Channel 9 Switch (SwA)

//
//  debugSerial.print("valBright: ");
//  debugSerial.print(valBright);
//  debugSerial.println();  
//  debugSerial.print("valSpeed: ");
//  debugSerial.print(valSpeed);
//  debugSerial.println();
//  debugSerial.print("valBlending: ");
//  debugSerial.print(valBlending);
//  debugSerial.println();
//  debugSerial.print("valPalette: ");
//  debugSerial.print(valPalette);
//  debugSerial.println();
//  

  // Linear Blending
  switch (valBlending) {
    case 2000:
      currentBlending = LINEARBLEND;
      break;
    default:
      currentBlending = NOBLEND;
      break;    
  }
//  if (valBlending = 1000)
//    {currentBlending = NOBLEND;}
//  else
//    {currentBlending = LINEARBLEND;}

  // Color Palette Selection
  switch (valPalette) {
    case 1000:
      currentPalette = RainbowColors_p;
      break;
    case 1500:
      currentPalette = PartyColors_p;
      break;
    case 2000:
      currentPalette = myRedWhiteBluePalette_p;
      break;
    }  
  

// --- Debugging example below ---
//  debugSerial.print("Channel 1: ");
//  debugSerial.print(valBright);
//  debugSerial.println();  
//  debugSerial.print("Channel 2: ");
//  debugSerial.print(valBright);
//  debugSerial.println();  
//  debugSerial.print("Channel 3: ");
//  debugSerial.print(valBright);
//  debugSerial.println();  
//  debugSerial.print("Channel 6: ");
//  debugSerial.print(valSpeed);
//  debugSerial.println();
  debugSerial.print("Channel 7: ");
  debugSerial.print(valBlending);
  debugSerial.println();
//  debugSerial.print("Channel 9: ");
//  debugSerial.print(valPalette);
//  debugSerial.println();
  
//  for (byte i = 0; i<10; i++){
//    int value = readChannel(i, 1000, 2000, 1000);
//    debugSerial.print("Ch");
//    debugSerial.print(i + 1);
//    debugSerial.print(": ");
//    debugSerial.print(value);
//    debugSerial.print(" ");
//  }

//currentPalette = RainbowColors_p;         
//currentBlending = LINEARBLEND;
//int valSpeed = 100;

    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    
    FillLEDsFromPaletteColors(startIndex, valBright);


  FastLED.show();
  FastLED.delay(1000 / valSpeed);
      
//  delay(10);
}

void FillLEDsFromPaletteColors( uint8_t colorIndex, uint8_t brightness)
{
   // uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}

//// 
void fadeAll() 
  { 
  for(int i = 0; i < NUM_LEDS; i++) 
    { leds[i].nscale8(250); } 
  }

/////// NEEDS WORK!!!!
void larsonScan(uint16_t cycleSpeed, uint8_t cylonHue, uint8_t brightness) 
  { 

  // First slide the led in one direction
  for(int i = 0; i < NUM_LEDS; i++) 
    {    
    leds[i] = CHSV(cylonHue, 255, brightness);    // Set the i'th led to red 
    FastLED.show(); 
    
    leds[i] = CRGB::Black;    // Reset the i'th led to black
    fadeAll();

    delay(cycleSpeed);    // Wait a little bit before we loop around and do it again
    }


  // Now go in the other direction.  
  for(int i = (NUM_LEDS)-1; i >= 0; i--) 
    {
    leds[i] = CHSV(cylonHue, 255, brightness);    // Set the i'th led to red 
    FastLED.show();
    
    leds[i] = CRGB::Black;    // Reset the i'th led to black
    fadeAll();
    
    delay(cycleSpeed);    // Wait a little bit before we loop around and do it again
    }
  }
//////////////////////////////////


// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
    CRGB::Red,
    CRGB::Gray, // 'white' is too bright compared to red and blue
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Black
};


//void ChangePalettePeriodically()
//{
// //   uint8_t secondHand = (millis() / 1000) % 60;
//    static uint8_t lastSecond = 99;
//    
//    if( lastSecond != secondHand) {
//        lastSecond = secondHand;
//        if( secondHand ==  0)  { currentPalette = RainbowColors_p;         currentBlending = LINEARBLEND; }
//        if( secondHand == 10)  { currentPalette = RainbowStripeColors_p;   currentBlending = NOBLEND;  }
//        if( secondHand == 15)  { currentPalette = RainbowStripeColors_p;   currentBlending = LINEARBLEND; }
//        if( secondHand == 20)  { SetupPurpleAndGreenPalette();             currentBlending = LINEARBLEND; }
//        if( secondHand == 25)  { SetupTotallyRandomPalette();              currentBlending = LINEARBLEND; }
//        if( secondHand == 30)  { SetupBlackAndWhiteStripedPalette();       currentBlending = NOBLEND; }
//        if( secondHand == 35)  { SetupBlackAndWhiteStripedPalette();       currentBlending = LINEARBLEND; }
//        if( secondHand == 40)  { currentPalette = CloudColors_p;           currentBlending = LINEARBLEND; }
//        if( secondHand == 45)  { currentPalette = PartyColors_p;           currentBlending = LINEARBLEND; }
//        if( secondHand == 50)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = NOBLEND;  }
//        if( secondHand == 55)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = LINEARBLEND; }
//    }
//}
