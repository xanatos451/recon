// NRF24L01 Module Tutorial - Code for Receiver using Arduino UNO

//Include needed Libraries at beginning
//#include "C:\Users\xanat\Documents\ArduinoData\packages\Seeeduino\hardware\samd\1.8.0\libraries\SPI\SPI.h"
#include "nRF24L01.h" // NRF24L01 library created by TMRh20 https://github.com/TMRh20/RF24
#include "RF24.h"
#include <SPI.h>
#include "FastLED.h" // FastLED library for WS2812 RGB Stick http://fastled.io/
#include "printf.h"

//LED Vars
#define NUM_LEDS 4 // Number of leds on stick
#define LED_PIN 1 // Digital In (DI) of RGB Stick connected to pin 8 of the UNO

CRGB leds[NUM_LEDS]; // FastLED Library Init

//Radio Vars
// Pin
//#define SPI_MISO_PIN 9
//#define SPI_MOSI_PIN 10
//#define SPI_SCK_PIN 8
// 4 - SS(CS)
// 8 - SCK - SERCOM0 - PAD 3
// 9 - MISO - SERCOM0 - PAD 1
// 10 - MOSI - SERCOM0 - PAD 2

const int CE = 2; // Chip Enable pin
const int CS = 3; // Slave Select pin

int ReceivedMessage[1] = {000}; // Used to store value received by the NRF24L01
const uint64_t pipe = 0xE1E1E1E1E1E1; // Radio ID - Needs to be the same for communicating between 2 NRF24L01 

RF24 radio(2,3); // RF24 Library Init - NRF24L01+ (CE, CS)


void setup(void){
//     pinMode(CS, OUTPUT);
////     digitalWrite(CS, HIGH); // disable Slave Select
//     SPI.begin ();
//     SPI.setClockDivider(SPI_CLOCK_DIV8);//divide the clock by 8
     
  FastLED.addLeds<WS2812B,LED_PIN>(leds, NUM_LEDS); // Setup FastLED Library
  FastLED.clear(); // Clear the RGB Stick LEDs
  // Light up starting LED's
  for(int x = 0; x != NUM_LEDS; x++) {
    leds[x] = CRGB::Red;
  }

FastLED.setBrightness(50);
FastLED.show();

delay(100);


radio.begin(); // Start the NRF24L01
radio.setAutoAck(false); // May try removing later
radio.setPALevel(RF24_PA_LOW);  // Set the power level
radio.setChannel(120);  // Set the channel

radio.openReadingPipe(1,pipe); // Get NRF24L01 ready to receive
radio.startListening(); // Listen to see if information received


}

void loop(void){
//if (!radio.available())
//{
//  for(int x = 0; x != NUM_LEDS; x++) 
//{
//leds[x] = CRGB::Yellow;
//FastLED.show();
//}
//delay(10000);
//}
if (radio.available())
  {
  radio.read(ReceivedMessage, 1); // Read information from the NRF24L01

  if (ReceivedMessage[0] == 000) // Indicates switch is pressed
    {
    for(int x = 0; x != NUM_LEDS; x++)
      {
      leds[x] = CRGB::Green;
      FastLED.show();
      }
     delay(100);
    }

  else if (ReceivedMessage[0] == 111)
    {
    for(int x = 0; x != NUM_LEDS; x++) 
      {
      leds[x] = CRGB::Red;
      FastLED.show();
      }
      delay(100);
    }

  delay(100);
  }
  else
    {
    for(int x = 0; x != NUM_LEDS; x++) 
      {
      leds[x] = CRGB::Yellow;
      FastLED.show();
      }
    }
  delay(100);     
}
