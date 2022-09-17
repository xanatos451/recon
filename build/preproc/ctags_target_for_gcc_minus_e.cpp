# 1 "d:\\Sandbox\\github\\xanatos451\\recon\\Recon_Main\\Recon_Main.ino"
# 2 "d:\\Sandbox\\github\\xanatos451\\recon\\Recon_Main\\Recon_Main.ino" 2
// #include "readRadio.ino"
// #include "readVoltage.ino"

// radio stuff
# 7 "d:\\Sandbox\\github\\xanatos451\\recon\\Recon_Main\\Recon_Main.ino" 2
IBusBM ibusRc;
::HardwareSerial& ibusRcSerial = Serial1;

struct radio{
    bool SwA;
    bool SwB;
    int SwC;
    bool SwD;
    int VrA;
    int VrB;
    int LsUD;
    int LsLR;
    int RsUD;
    int RsLR;
    float ExtV;
  };

radio rcvr = {false, false, 1000, false, 1000, 1000, 1000, 1000, 1000, 1000, 0.00}; // initial receiver value

const unsigned long intervalRadio = 10;
unsigned long pTimeRadio;
// --------------------------------------------------

// voltage stuff
// Define analog input


// Float input voltage
float in_voltage = 0.0;

// Floats for resistor values in divider (in ohms)
float R1 = 27000.0;
float R2 = 6800.0;

// Float for Reference Voltage
float ref_voltage = 5.0;

const unsigned long intervalVoltage = 1000;
unsigned long pTimeVoltage;
// --------------------------------------------------


void setup() {
    SerialUSB.begin(9600); // debugger

    ibusRc.begin(ibusRcSerial); // initialize radio receiver connection
    ibusRc.addSensor(0x00 /* Internal voltage (in 0.01)*/);
    // in_voltage = readVoltageValue();   // initial voltage value reading

    // rcvr readRadioValues();     // initial radio value reading

}

void loop() {
    readVoltage(rcvr.ExtV); // update the voltage reading
    readRadio(rcvr, ibusRc); // update the receiver values from the transmitter
    // ibusRc.setSensorMeasurement(1, in_voltage);


    SerialUSB.print("Input Voltage = ");
    SerialUSB.println(rcvr.ExtV, 2);
}


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

        sendRadioSensor(ibR, r); // send sensor data to transmitter

        pTimeRadio = millis(); // set the previous time to current time
    }
}

void sendRadioSensor(IBusBM& ibR, radio r){
    ibR.setSensorMeasurement(1, r.ExtV);
}

void readVoltage(float& in_vdc){
    if (millis() - pTimeVoltage >= intervalVoltage) {
        // Read the Analog Input
        int adc_value = analogRead(A0);

        // Determine voltage at ADC input
        float adc_voltage = (adc_value * ref_voltage) / 1024.0;

        in_vdc = adc_voltage / (R2/(R1+R2));

        pTimeVoltage = millis(); // set the previous time to current time
    }
}
