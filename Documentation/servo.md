# PWM Servo Driver

## Hardware

PCA9685 16-Channel 12-bit PM Driver
- https://www.amazon.com/dp/B07Z8R2YB9

### Specs

Voltage
- DC5-10V power supply

Communication Interface
- IIC

16-way steering gear control

Size
- 25*61mm

Features
- The PCA9685 chip is wrapped in the center of the board
- Power input terminal
- Green power indicator
- In the 4 groups of 3-pin connector to facilitate the insertion of 16 servo motor (servo motor plug slightly wider than 0.1 ")
- The polarity of the reverse polarity is input on the terminal block
- Cascade design
    - V + line to place a large capacitor, the maximum external input voltage depends on the 10V 1000uf capacitor
    - All PWM output lines have a 220 ohm series resistor protection and can easily drive LED

## Libary

https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library
