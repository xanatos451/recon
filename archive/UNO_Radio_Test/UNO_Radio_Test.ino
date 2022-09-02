
#include "nRF24L01.h" //NRF24L01 library created by TMRh20 https://github.com/TMRh20/RF24
#include "RF24.h"
#include "SPI.h"
#include "printf.h"


int SentMessage[1] = {000}; // Used to store value before being sent through the NRF24L01

RF24 radio(9, 10); // NRF24L01 used SPI pins + Pin 9 and 10 on the NANO

const uint64_t pipe = 0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01


void setup(void) {

  Serial.begin(9600);
  printf_begin();


  radio.begin(); // Start the NRF24L01
  radio.openWritingPipe(pipe); // Get NRF24L01 ready to transmit
}

void loop(void) {

  if (Serial.available() > 0)               //If we receive something...
  {
    String Received = Serial.readString();  //Save the received String in the Received variable
    Serial.println(Received);    
    if (int(Received[0]) == 1)              //If  character  "Received" is "1"

      SentMessage[0] = 100;                 //send message "100"
    radio.write(SentMessage, 1);


    if (int(Received[0]) == 0)              //If the character of "Received" is "0"

      SentMessage[0] = 111;                 //send message "111"
    radio.write(SentMessage, 1);



    if (int(Received[0]) == 2)              //If the first character of "Received" is "2"

      SentMessage[0] = 101;                 //send message "101"
    radio.write(SentMessage, 1);

  }

}
