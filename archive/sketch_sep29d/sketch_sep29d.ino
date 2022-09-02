#include<FastLED.h> // header file

#define NUM_LEDS 8 // number of led present in your strip
#define DATA_PIN 1 // digital pin of your arduino

CRGB leds[NUM_LEDS];

void setup() {

FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

}
void loop()
{ leds[0] = CRGB::Blue;

FastLED.show();

delay(200);

leds[0] = CRGB::Black;

FastLED.show();

delay(200);

}
