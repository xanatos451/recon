# Seeeduino Xiao

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
