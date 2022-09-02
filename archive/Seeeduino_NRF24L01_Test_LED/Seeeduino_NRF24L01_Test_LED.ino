#include <SPI.h>

#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

/* 
Created by Yvan / https://Brainy-Bits.com

This code is in the public domain...
You can: copy it, use it, modify it, share it or just plain ignore it!
Thx!

*/


// NRF24L01 Module Tutorial - Code for Receiver using Arduino UNO

//Include needed Libraries at beginning

//#include "RF24_config.h"
//#include "nRF24L01.h" // NRF24L01 library created by TMRh20 https://github.com/TMRh20/RF24
//#include "RF24.h"
//#include "SPI.h"
//#include "FastLED.h" // FastLED library for WS2812 RGB Stick http://fastled.io/d

//#define NUM_LEDS 8 // Number of leds on stick
#define LED_PIN 1 // Digital In (DI) of RGB Stick connected to pin 8 of the UNO

//CRGB leds[NUM_LEDS]; // FastLED Library Init

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        1 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 4 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 1000 // Time (in milliseconds) to pause between pixels

int ReceivedMessage[1] = {000}; // Used to store value received by the NRF24L01

RF24 radio(2,3); // NRF24L01 used SPI pins + Pin 9 and 10 on the UNO

const uint64_t pipe = 0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01 


void setup(void){
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
    pixels.clear(); // Set all pixel colors to 'off'
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));

    pixels.show();   // Send the updated pixel colors to the hardware.
    
//FastLED.addLeds<NEOPIXEL,LED_PIN>(leds, NUM_LEDS); // Setup FastLED Library
//FastLED.clear(); // Clear the RGB Stick LEDs
//
//// Light up starting LED's
//for(int x = 0; x != NUM_LEDS; x++) {
//leds[x] = CRGB::Red;
//}
//
//FastLED.setBrightness(50);
//FastLED.show();

radio.begin(); // Start the NRF24L01

radio.openReadingPipe(1,pipe); // Get NRF24L01 ready to receive

radio.startListening(); // Listen to see if information received

pinMode(LED_PIN, OUTPUT); // Set RGB Stick UNO pin to an OUTPUT
}

void loop(void){

while (radio.available())
{
radio.read(ReceivedMessage, 1); // Read information from the NRF24L01

if (ReceivedMessage[0] == 111) // Indicates switch is pressed
{
//for(int x = 0; x != NUM_LEDS; x++)
//{
//leds[x] = CRGB::Green;
//FastLED.show();
//}
//}
//else
//{

//for(int x = 0; x != NUM_LEDS; x++) 
//{
//leds[x] = CRGB::Red;
//FastLED.show();
//}

  pixels.setPixelColor(0, pixels.Color(0, 150, 0));
  pixels.show();   // Send the updated pixel colors to the hardware.
  }
else
  {
  pixels.setPixelColor(0, pixels.Color(150, 0, 0));
  pixels.show();   // Send the updated pixel colors to the hardware.
  }

}
delay(10);
}
