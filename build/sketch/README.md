#line 1 "d:\\Sandbox\\github\\xanatos451\\recon\\README.md"
# ReCon
Remote control package library

## Transmitter

Channel Assignment:

- **SwA**
  - Ch5: 2 position switch
- **SwB**
  - Ch6: 2 position switch
- **SwC**
  - Ch7: 3 position switch
- **SwD**
  - Ch8: 2 position switch
- **VrA**
  - Ch9: variable pot selector
- **VrB**
  - Ch10: variable pot selector
- **LsUD**
  - Ch3: Left Stick Up/Down variable
- **LsLR**
  - Ch4: Left Stick Left/Right variable
- **RsUD**
  - Ch2: Right Stick Up/Down variable
- **RsLR**
  - Ch1: Right Stick Left/Right variable

Transmitter firmware is upgraded via the FlySky i6 10ch mod. Sticks are assigned to Mode 2 layout with aux channels assigned to the above layout via the setup menu (long press OK on transmitter).

- ../FlySky i6 Firmware/FlySky-i6-Mod--master/FlySky-i6-Mod--master/10ch Mod i6 Updater/10ch_MOD_i6_Programmer_V1_5

## Processor

This project uses the Arduino compatible Seeeduino XIAO (SAMD21) microprocessor

- 32-bit single-core processor
- Clock speed up to 48MHz
- 32KB SRAM
- 256KB Flash Memory
- 11 Digital I/O
- 11 12-bit ADC Inputs
- 1 DAC Output
- Support for up to 120 touch channels
- USB-C Device and Embedded host
- Hardware RTC
- 1.62V to 3.63V power supply
  - 3.3 vdc (pin 11)
  - VCC (pin 13) can be powered with 3.7-5vdc
- Extremely low power consumption
- 6 serial communication modules (SERCOM) configurable as UART/USART, SPI or I2C

https://dronebotworkshop.com/seeeduino-xiao-intro/


## Library Updates

- IBusBM requires code changes to support samd21 processors
    - https://github.com/bmellink/IBusBM/pull/23/files 