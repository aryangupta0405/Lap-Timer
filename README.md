# Lap Timer

## Introduction
The lap timer was implemented to measure accurate lap timings to check the consistency of the driver. This was implemented using a laser, LDR(light-dependent resistor), 16x2 LCD, LoRa modules and Arduino Nano. The lap timer can be used to find lap timings for a circular track as well as for a straight-line acceleration test. The straight-line version makes use of LoRa modules for wireless communication between the start and finish of the test.

## Components Used
* Arduino Nano
* [EBYTE E32-433T30D LoRa Module](https://www.ebyte.com/en/product-view-news.aspx?id=108)
* 16X2 LCD
* [I2C Converter for 16X2 LCD](https://robu.in/product/iic-i2c-serial-interface-adapter-module/?gclid=Cj0KCQjwjryjBhD0ARIsAMLvnF-gvuL3Ke7y_DiaVVzhbOAR8XDawyDECBaH5qey6SnCRU7ZZTEmUDYaAowEEALw_wcB)
* Light Dependent Resistor(LDR)
* Resistor(10K ohm)
* Push Button
## Schematic Diagram 

![Alt text](Fritzing%20LapTimer.png)
            

## Pin Description
| Pin Name        | Pin Number | Input/Output |
|-----------------|------------|--------------|
| Laser Interrupt | D2         | Input        |
| Reset Button    | D3         | Input        |
| LoRa TX         | D10        | Input        |
| LoRa RX         | D11        | Output       |
| LCD SDA         | A4         | Output       |
| LCD SCL         | A5         | Output       |

## Working


    
The Lap Timer consists of two parts: a laser positioned on one side of the track and a main circuit featuring an Arduino Nano connected to an LDR, an LCD, and a LoRa module. It can be used in two ways - for measuring circular track lap timings and for measuring acceleration track timings using the same main module. 

To measure circular track timings, the laser is positioned to strike the LDR continuously. The LDR's resistance value decreases when the laser strikes it and increases when it doesn't. The LDR is connected to an interrupt-enabled pin on the Arduino Nano. When the laser is striking the LDR, no interrupt is called and the timer hasn't started. When the car crosses the laser, the resistance value of the LDR momentarily increases, and the interrupt is triggered, starting the timer from zero. When the car completes the lap and crosses the laser again, the interrupt is called, and the time difference between the two interrupts and the lap number are displayed on the 16X2 LCD. At the start of the next session, the reset button can be pressed to reset the timer.

To measure acceleration track timings, the laser and the main module are positioned at the finish line of the track. A secondary module with an Arduino Mega or another microcontroller interfaced with a second LoRa module is placed at the start line, with another laser striking another LDR on the opposite side of the track, just like the finish line module. When the vehicle passes through the laser at the start line, a symbol is sent via the LoRa module to the finish line module, triggering the timer. When the vehicle passes through the laser at the finish line, the time taken to cover the known distance is displayed on the 16X2 LCD.

![Alt text](LTimer%20Flowchart.png)
            
            Lap Timer Transmitter and Receiver Flowchart