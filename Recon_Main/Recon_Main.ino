#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>
#include <FastLED_NeoPixel.h>
// #include <Servo.h>
// #include "readRadio.ino"
// #include "readVoltage.ino"


int buttonPin = 1;
const unsigned long intervalButton = 100;
unsigned long pTimeButton;
bool buttonPressed = false;


// -----------------------------------------------
// radio stuff
#include <IBusBM.h>
IBusBM ibusRc;
HardwareSerial& ibusRcSerial = Serial1;

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
    // float   ExtV;
  };

radio rcvr = {false, false, 1000, false, 1000, 1000, 1000, 1000, 1000, 1000}; // initial receiver value

const unsigned long intervalRadio = 10;
unsigned long pTimeRadio;

// --------------------------------------------------
// servo stuff

#define SERVOMIN 125
#define SERVOMAX 575

Adafruit_PWMServoDriver myServo = Adafruit_PWMServoDriver(0x40);
uint8_t servoNum = 0;   // servo counter
uint8_t numServos = 2;  // number of servos

// SETUP ---------------------------------------------------------------
void setup() {
    Serial.begin(9600);  // debugger
    
    pinMode(buttonPin, INPUT);  // button 


    ibusRc.begin(ibusRcSerial);         // initialize radio receiver connection
    // ibusRc.addSensor(IBUSS_EXTV);
    // in_voltage = readVoltageValue();   // initial voltage value reading
       
    // servo setup
    myServo.begin();
    myServo.setPWMFreq(60);    
}

// MAIN LOOP -----------------------------------------------------------
void loop() {
    // readVoltage(rcvr.ExtV);    // update the voltage reading
    readRadio(rcvr, ibusRc);  // update the receiver values from the transmitter
    // ibusRc.setSensorMeasurement(1, in_voltage);
    checkButton();



    if (buttonPressed) {
        Serial.println("Button Pressed");

        // for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++){
        //     myServo.setPWM(1, 0, pulselen);
        // }
        myServo.setPWM(1, 0, SERVOMAX);
    } 
    else {
        Serial.println("Button Not Pressed");
        // for(uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--){
        //     
        // }

        myServo.setPWM(1, 0, SERVOMIN);
        
    }
}

// -----------------------------------------------------
// read button stuff

// checks button state at intervals
void checkButton() {
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


// Read the number of a given channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(byte channelInput, int minLimit, int maxLimit, int defaultValue, IBusBM& ibR){
uint16_t ch = ibR.readChannel(channelInput);
if (ch < 100) return defaultValue;
return map(ch, 1000, 2000, minLimit, maxLimit);
}



// checks the radio for value updates in set intervals
void readRadio(radio& r, IBusBM& ibR){
    if (millis() - pTimeRadio >= intervalRadio) {
        // read channel values from receiver
        r.RsLR = readChannel(0, 1000, 2000, 1000, ibR);
        r.RsLR = readChannel(1, 1000, 2000, 1000, ibR);
        r.RsLR = readChannel(2, 1000, 2000, 1000, ibR);
        r.RsLR = readChannel(3, 1000, 2000, 1000, ibR);
        r.SwA = readChannel(4, 1000, 2000, 1000, ibR) > 1500 ? true : false;
        r.SwB = readChannel(5, 1000, 2000, 1000, ibR) > 1500 ? true : false;
        r.SwC = readChannel(6, 1000, 2000, 1000, ibR);
        r.SwD = readChannel(7, 1000, 2000, 1000, ibR) > 1500 ? true : false;
        r.VrA = readChannel(8, 1000, 2000, 1000, ibR);
        r.VrB = readChannel(9, 1000, 2000, 1000, ibR);

        // ibR.setSensorMeasurement(1, r.ExtV);    // send sensor data to transmitter

        pTimeRadio = millis();      // set the previous time to current time
    }
}

