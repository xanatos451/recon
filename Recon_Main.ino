#include <FastLED_NeoPixel.h>
#include "readRadio.ino"


void setup() {
    Serial.begin(9600);
    ibusRc.begin(ibusRcSerial);
    radio rcvr = readRadioValues();
}

void loop() {
    readRadio(rcvr);  // update the receiver values from the transmitter

    
}
