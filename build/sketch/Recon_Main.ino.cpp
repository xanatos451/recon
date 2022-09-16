#include <Arduino.h>
#line 1 "d:\\Sandbox\\github\\xanatos451\\recon\\Recon_Main.ino"
#include <FastLED_NeoPixel.h>

#include <IBusBM.h>

IBusBM ibusRc;
HardwareSerial& ibusRcSerial = Serial1;

#define receiverPin

#line 10 "d:\\Sandbox\\github\\xanatos451\\recon\\Recon_Main.ino"
void setup();
#line 15 "d:\\Sandbox\\github\\xanatos451\\recon\\Recon_Main.ino"
void loop();
#line 22 "d:\\Sandbox\\github\\xanatos451\\recon\\Recon_Main.ino"
int readChannel(byte channelInput, int minLimit, int maxLimit, int defaultValue);
#line 10 "d:\\Sandbox\\github\\xanatos451\\recon\\Recon_Main.ino"
void setup() {
    Serial.begin(9600);
    ibusRc.begin(ibusRcSerial);
}

void loop() {

}


// Read the number of a given channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(byte channelInput, int minLimit, int maxLimit, int defaultValue){
uint16_t ch = ibusRc.readChannel(channelInput);
if (ch < 100) return defaultValue;
return map(ch, 1000, 2000, minLimit, maxLimit);
}
