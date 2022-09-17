#include <FastLED>

//LED Vars --------------------------------------------------------------------
#define LED_PIN 3              // Arduino pin number LED strip is connected to
#define NUM_LEDS 8             // Number of LEDs in strip
#define COLOR_ORDER GRB         // LED Color order
#define LED_TYPE WS2812B        // LED Strip Type
#define MAX_BRIGHTNESS 164      // Thats full on, watch the power!
#define MIN_BRIGHTNESS 32       // Set to a minimum of 25%

CRGB leds[NUM_LEDS]; // FastLED Library Init
// ----------------------------------------------------------------------------
// button vars
int buttonPin = 1;
const unsigned long intervalButton = 100;
unsigned long pTimeButton;
bool buttonPressed = false;
// ----------------------------------------------------------------------------

void setup() {  
    pinMode(buttonPin, INPUT);  // button 
    
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.clear(); // Clear the RGB Stick LEDs
    FastLED.setBrightness(50);
    FastLED.show();
    pinMode(LED_PIN, OUTPUT); // Set RGB Stick UNO pin to an OUTPUT
}

// MAIN LOOP -----------------------------------------------------------
void loop() {
    checkButton();

    if (buttonPressed) {
        // color green
    } 
    else {
        // color red
    }
}

// -----------------------------------------------------
// read button stuff

// checks button state at intervals
void checkButton(){
    unsigned long currTime = millis();
    if (currTime - pTimeButton > intervalButton){
       if (digitalRead(buttonPin) == LOW){
            buttonPressed = true;
       }
       else{
        buttonPressed = false;
       }
       pTimeButton = currTime;
    }
}

// -----------------------------------------------------
// set LED stuff

// sets LED color
void setLED(bool state){
    if (state){
        for(int x = 0; x != NUM_LEDS; x++){
            leds[x] = CRGB::green;
            FastLED.show();
        }
    }
}
