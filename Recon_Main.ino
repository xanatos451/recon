#include <IBusBM.h>

IBusBM ibusRc;
HardwareSerial& ibusRcSerial = Serial1;


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