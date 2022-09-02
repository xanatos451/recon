/*
Created by Yvan / https://Brainy-Bits.com

This code is in the public domain...
You can: copy it, use it, modify it, share it or just plain ignore it!
Thx!

*/

// NRF24L01 Module Tutorial - Code for Transmitter using Arduino NANO

//Include needed Libraries at beginning
#include "nRF24L01.h" //NRF24L01 library created by TMRh20 https://github.com/TMRh20/RF24
#include "RF24.h"
#include "SPI.h"
#include "FastLED.h" // FastLED library for WS2812 RGB Stick http://fastled.io/

//LED Vars
#define NUM_LEDS 4 // Number of leds on stick
#define LED_PIN 5 // Digital In (DI) of RGB Stick connected to pin 8 of the UNO

CRGB leds[NUM_LEDS]; // FastLED Library Init


//
//#include <Adafruit_NeoPixel.h>
//#ifdef __AVR__
// #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
//#endif

// Which pin on the Arduino is connected to the NeoPixels?
//#define PIN        5 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
//#define NUMPIXELS 4 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
//Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 1000 // Time (in milliseconds) to pause between pixels

#define SwitchPin 8 // Arcade switch is connected to Pin 8 on NANO
int SentMessage[1] = {000}; // Used to store value before being sent through the NRF24L01

RF24 radio(9,10); // NRF24L01 used SPI pins + Pin 9 and 10 on the NANO

const uint64_t pipe = 0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01 


void setup(void){
//    Serial.begin(115200);
FastLED.addLeds<WS2812B,LED_PIN>(leds, NUM_LEDS); // Setup FastLED Library
FastLED.clear(); // Clear the RGB Stick LEDs

// Light up starting LED's
for(int x = 0; x != NUM_LEDS; x++) {
leds[x] = CRGB::Red;
}

FastLED.setBrightness(50);
FastLED.show();

//  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
//    pixels.clear(); // Set all pixel colors to 'off'
//    pixels.setPixelColor(0, pixels.Color(150, 0, 0));
//
//    pixels.show();   // Send the updated pixel colors to the hardware.
    
pinMode(SwitchPin, INPUT_PULLUP); // Define the arcade switch NANO pin as an Input using Internal Pullups
digitalWrite(SwitchPin,HIGH); // Set Pin to HIGH at beginning

radio.begin(); // Start the NRF24L01
radio.openWritingPipe(pipe); // Get NRF24L01 ready to transmit

pinMode(LED_PIN, OUTPUT); // Set RGB Stick UNO pin to an OUTPUT
}

void loop(void){


while (radio.available())
  {
  if (digitalRead(SwitchPin) == LOW)  // If Switch is Activated
    { 
  //  pixels.setPixelColor(0, pixels.Color(0, 150, 0));
  //  pixels.show();   // Send the updated pixel colors to the hardware.
  
    SentMessage[0] = 111;
    radio.write(SentMessage, 1); // Send value through NRF24L01
    for(int x = 0; x != NUM_LEDS; x++)
      {
      leds[x] = CRGB::Green;
      FastLED.show();
//      Serial.println("Command sent");
      }
    }
  else 
    {
      //    pixels.setPixelColor(0, pixels.Color(150, 0, 0));
      //  pixels.show();   // Send the updated pixel colors to the hardware.
    SentMessage[0] = 000;
    radio.write(SentMessage, 1);
    for(int x = 0; x != NUM_LEDS; x++) 
      {
      leds[x] = CRGB::Red;
      FastLED.show();
//      Serial.println("End Transmission");
      }
    }
  }
 for(int x = 0; x != NUM_LEDS; x++)
  {
  leds[x] = CRGB::Yellow;
  FastLED.show();
  }
//delay(1000);
}
