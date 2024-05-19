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
In this project, I will go over my implementation to create an ADC from scratch which will be used with an Arduino Uno to read the data in. I first want to design a 2-bit Flash ADC then increase the 
resolution to 4-bit. Another implementation is the SAR ADC which will be my next design starting with 2-bit resolution then increasing to 4-bit. After each design has been tested and in the final design, 
I plan to move the product from the breadboard to a Printed Circuit Board (PCB).

### Preliminary design
The first design of the Flash ADC will have a 2-bit resolution. The ADC will take an analog signal in and output to a priority encoder to produce a weighted binary output. This output will be read with an 
Arduino Uno to determine the analog voltage. Below is the architecture of the 2-bit Flash ADC.

![architecture_of_2-bit_Flash_ADC](README_IMAGES/architecture_of_2-bit_Flash_ADC.PNG)

A Flash ADC will use a resistive ladder, comparators and a Priority Encoder to read the analog voltage and output a weighted binary value. The ADC Logic will have a resistor ladder used as the voltage divider. 
Each node on the ladder will be the input to the non-inverting side of an operational amplifier. Although a comparator IC could be used here, I do not plan to use the ADC in a high frequency design. Therefore 
the LM358N Op-Amp can substitue the need for a comparator. The Priority Encoder will take the unweighted binary value from the LM358N and use combinational logic to output a weighted binary value for the Arduino 
Uno to read in. 

#### ADC Logic (2-bit)

#### Priority Encoder (2-bit)
k-map here

### Hardware schematic

### Software flow chart or algorithms
Not at stage of product where Arduino has been implemented.

### Debugging

### Testing methodology or results

### Observations and Conclusions

### Documentation
