#line 1 "d:\\Sandbox\\github\\xanatos451\\recon\\readReceiver.cpp"
#include <IBusBM.h>

class ReadReceiver
{

  public:

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

  void read();

  // Read the number of a given channel and convert to the range provided.
  // If the channel is off, return the default value
  int readChannel(byte channelInput, int minLimit, int maxLimit, int defaultValue){
    uint16_t ch = ibusRc.readChannel(channelInput);
    if (ch < 100) return defaultValue;
    return map(ch, 1000, 2000, minLimit, maxLimit);
  }

  private:
    int ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8, ch9, ch10;
};



