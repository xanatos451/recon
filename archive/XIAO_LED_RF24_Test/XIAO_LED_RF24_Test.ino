#include <Adafruit_NeoPixel.h>

#include "nRF24L01.h" // NRF24L01 library created by TMRh20 https://github.com/TMRh20/RF24
#include "RF24.h"
#include "SPI.h"
//#include "FastLED.h"



#define PIXEL_PIN    1    // Digital IO pin connected to the NeoPixels.

#define PIXEL_COUNT 4 //number of LEDs


Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);




RF24 radio(4, 7); // NRF24L01 used SPI pins + Pin 9 and 10 on the NANO

const uint64_t pipe = 0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01
int ReceivedMessage[1];

void setup() {
  Serial.begin(115200);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  radio.begin(); // Start the NRF24L01

  radio.openReadingPipe(1, pipe); // Get NRF24L01 ready to receive

  radio.startListening(); // Listen to see if information received
pinMode(PIXEL_PIN, OUTPUT); // Set RGB Stick UNO pin to an OUTPUT
}

void loop() {
  if (radio.available()) radio.read(ReceivedMessage, 1);

  int iMessage = ReceivedMessage[0];
  Serial.println(iMessage);

  if (ReceivedMessage[0] == 101 || ReceivedMessage[0] == 100 || ReceivedMessage[0] == 111 )

    switch (iMessage) {
      case 101:
        colorWipe(strip.Color(255, 0, 0), 50);  // led animation
        break;
      case 100:
        theaterChase(strip.Color(127,   0,   0), 50); // led animation
        break;
      case 111:
        rainbow(20);
        break;
      default:
        rainbow(20);
        break;
    }

  else {}

}

//Led show

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}



//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, c);  //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}



// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
