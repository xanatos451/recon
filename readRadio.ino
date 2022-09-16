#include <IBusBM.h>
IBusBM ibusRc;
HardwareSerial& ibusRcSerial = Serial1;
radio rcvr;

struct radio{
    bool  SwA;
    bool  SwB;
    int   SwC;
    bool  SwD;
    int   VrA;
    int   VrB;
    int   LsUD;
    int   LsLR;
    int   RsUD;
    int   RsLR;
  };

const unsigned long intervalRadio = 10;
unsigned long pTimeRadio = 0;

// Read the number of a given channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(byte channelInput, int minLimit, int maxLimit, int defaultValue){
uint16_t ch = ibusRc.readChannel(channelInput);
if (ch < 100) return defaultValue;
return map(ch, 1000, 2000, minLimit, maxLimit);
}

// parses channel list and returns latest values
radio readRadioValues(){
    radio r;

    r.RsLR = readChannel(0, 1000, 2000, 1000);
    r.RsLR = readChannel(1, 1000, 2000, 1000);
    r.RsLR = readChannel(2, 1000, 2000, 1000);
    r.RsLR = readChannel(3, 1000, 2000, 1000);
    r.SwA = readChannel(4, 1000, 2000, 1000) > 1500 ? true : false;
    r.SwB = readChannel(5, 1000, 2000, 1000) > 1500 ? true : false;
    r.SwC = readChannel(6, 1000, 2000, 1000);
    r.SwD = readChannel(7, 1000, 2000, 1000) > 1500 ? true : false;
    r.VrA = readChannel(8, 1000, 2000, 1000);
    r.VrB = readChannel(9, 1000, 2000, 1000);

    return r;
}

// checks the radio for value updates in set intervals
void readRadio(radio& r){
    if (millis() - pTimeRadio >= intervalRadio) {
        r = readRadioValues();
    }
}
