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
    float   ExtV;
  };

// --------------------------------------------------
// voltage stuff

// Define analog input
#define ANALOG_IN_PIN A0

// Float input voltage
float in_voltage = 0.0;
 
// Floats for resistor values in divider (in ohms)
float R1 = 27000.0;
float R2 = 6800.0;

// Float for Reference Voltage
float ref_voltage = 5.0;
 
const unsigned long intervalVoltage = 1000;
unsigned long pTimeVoltage;


void setup() {
    Serial.begin(9600);  // debugger

    ibusRc.begin(ibusRcSerial);         // initialize radio receiver connection
    ibusRc.addSensor(IBUSS_EXTV);
    // in_voltage = readVoltageValue();   // initial voltage value reading

    myServo.setPWMFreq(60);    
}

void loop() {
    readVoltage(rcvr.ExtV);    // update the voltage reading
    
    Serial.print("Input Voltage = ");
    Serial.println(rcvr.ExtV, 2);
}

// from readRadio
        ibR.setSensorMeasurement(1, r.ExtV);    // send sensor data to transmitter


// void sendRadioSensor(IBusBM& ibR, radio r){
//     ibR.setSensorMeasurement(1, r.ExtV);
// }

void readVoltage(float& in_vdc){
    if (millis() - pTimeVoltage >= intervalVoltage) {
        // Read the Analog Input
        int adc_value = analogRead(ANALOG_IN_PIN);
        
        // Determine voltage at ADC input
        float adc_voltage = (adc_value * ref_voltage) / 1024.0;

        in_vdc = adc_voltage / (R2/(R1+R2));

        pTimeVoltage = millis();    // set the previous time to current time
    }
}
