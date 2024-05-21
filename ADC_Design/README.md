# Implementation of an Analog-to-Digtal Converter (ADC) using discrete components and Integrated Circuits (IC)

#### Created by: Brandon Ramos

## Table of Contents
1. [Objectives or Purpose](#objectives-or-purpose)
2. [Preliminary Design](#preliminary-design)
3. [Hardware schematic](#hardware-schematic)
4. [Software flow chart or algorithms](#software-flow-chart-or-algorithms)
5. [Debugging](#debugging)
6. [Testing methodology or results](#testing-methodology-or-results)
7. [Observations and Conclusions](#observations-and-conclusions)
8. [Documentation](#documentation)
 
### Objectives or Purpose
In this project, I will go over my implementation to create an ADC from scratch which will be used with an Arduino Uno to read the data in. I first plan to design a 2-bit Flash ADC then increase the 
resolution to 4-bit. Another implementation is the SAR ADC which will be my next design starting with 2-bit resolution then increasing to 4-bit. After the 4-bit designs have been tested on breadboards and have no issues, 
I will move the product from the breadboard to a Printed Circuit Board (PCB).

### Preliminary design
The first design of the Flash ADC will have a 2-bit resolution. The ADC will take an analog signal in and output to a priority encoder to produce a weighted binary output. This output will be read with an 
Arduino Uno to determine the analog voltage. Below is the architecture of the 2-bit Flash ADC.

![architecture_of_2-bit_Flash_ADC](README_IMAGES/architecture_of_2-bit_Flash_ADC.png)

A Flash ADC will use a resistive ladder, comparators and a Priority Encoder to read the analog voltage and output a weighted binary value. The ADC Logic will have a resistor ladder used as the voltage divider. 
Each node on the ladder will be the input to the non-inverting side of an operational amplifier. Although a comparator IC could be used here, I do not plan to use the ADC in a high frequency design. Therefore 
the LM358N Op-Amp can substitue the need for a comparator. The Priority Encoder will take the unweighted binary value from the LM358N and use combinational logic to output a weighted binary value for the Arduino 
Uno to read in. For a 2-bit ADC, the resolution is one part in 3 (2<sup>2</sup>-1) which is not very useful. The Arduino Uno has a 10-bit ADC which has 1023 levels. Although the internal will need 2<sup>n</sup>-bits between the ADC Logic and the Priority Encoder, we reduce the number of lines out back to n-bits, in our case 2-bits.

Within the Flash ADC, the Priority Encoder will first be designed. The ADC Logic will be designed later in Altium in Section [Hardware schematic](#hardware-schematic). With the Priority Encoder taking in 4 bits and outputting 2 bits, created below is the Truth Table with inputs x[3..0] and outputs y[1..0]. Note that only the realized outputs are shown in the table as others are not possible and considered as don't cares (X). In any combination where the higher bits are '1' then all lower bits must also be '1' as the resistor ladder will have lower potential nodes already lactive.  

![Priority_Encoder_2-bit_Truth_Table](README_IMAGES/Priority_Encoder_2-bit_Truth_Table.png)

Given the truth table, we can draw a 4 variable Karnaugh Map (K-Map) for both outputs. Shown below in the 2-bit Priority Encoder K-Map, we can use the don't cares in our combinational logic design because they will never be an outcome in the ADC Logic. Being able to do this, we can decrease the number of logic gates used. This decreases the cost of the design as well as the critical path when considering propagation delay.

![Priority_Encoder_2-bit_K-Map](README_IMAGES/Priority_Encoder_2-bit_K-Map.png)

By including 'X' in the K-Map grouping, we end up only using 3 logic gates shown below for the 2-bit ADC. 

![Priority_Encoder_2-bit_combinational_logic](README_IMAGES/Priority_Encoder_2-bit_combinational_logic.png)

Given the design of the Priority Encoder, we will next use this design alongside the Flash ADC resistive ladder and Op-Amps to create the hardware schematic. Included will be supplemental discrete components such as coupling capacitors and a voltage regulator. 

### Hardware schematic
can be left for PCB Schematic


### Software flow chart or algorithms
Not at stage of product where Arduino has been implemented.

### Debugging
* LM358 is not a Rail-to=Rail IC and max input is Vcc-1.5V

### Testing methodology or results
![2-bit_Flash_ADC_Breadboard](README_IMAGES/2-bit_Flash_ADC_Breadboard.jpg)
[2-bit_Flash_ADC_Breadboard](https://youtu.be/c9W4OWWYJ1M)

### Observations and Conclusions

### Documentation
