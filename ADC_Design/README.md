# Implementation of an Analog-to-Digtal Converter (ADC) using discrete components and Integrated Circuits (IC)

![4-bit_Flash_ADC_Breadboard](README_IMAGES/4-bit_Flash_ADC_Breadboard.jpg)

## Roadmap
- Flash Analog-to-Digital Converter
- [X] 2-bit ADC 
    - [X] Breadboard Implementation
    - [X] Altium Schematic
- [ ] 4-bit ADC 
    - [X] Breadboard Implementation
    - [ ] Altium Schematic
    - [ ] Final PCB Product
- SAR Analog-to-Digital Converter
- [ ] 2-bit ADC 
    - [ ] Breadboard Implementation
    - [ ] Altium Schematic
- [ ] 4-bit ADC 
    - [ ] Altium Schematic
    - [ ] Final PCB Product



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
#### 2-bit Flash ADC
The first design of the Flash ADC will have a 2-bit resolution. The ADC will take an analog signal in and output to a priority encoder to produce a weighted binary output. This output will be read with an 
Arduino Uno to determine the analog voltage. Below is the architecture of the 2-bit Flash ADC.

![architecture_of_2-bit_Flash_ADC](README_IMAGES/architecture_of_2-bit_Flash_ADC.png)

A Flash ADC will use a resistive ladder, comparators and a Priority Encoder to read the analog voltage and output a weighted binary value. An enable pin will be active high nominally. Once the device reading in the weighted binary value is ready, it will set the enable pin low to hold the current value using a latch. The ADC Logic will have a resistor ladder used as the voltage divider. 
Each node on the ladder will be the input to the non-inverting side of an operational amplifier. Although a comparator IC could be used here, I do not plan to use the ADC in a high frequency design. Therefore 
the LM358N Op-Amp can substitue the need for a comparator. Some other drawbacks in using the LM358N are discussed in [Debugging](#debugging). The Priority Encoder will take the unweighted binary value from the LM358N and use combinational logic to output a weighted binary value for the Arduino Uno to read in. For a 2-bit ADC, the resolution is one part in 3 (2<sup>2</sup>-1) which is not very useful. The Arduino Uno has a 10-bit ADC which has 1023 levels. Although the internal will need 2<sup>n</sup>-bits between the ADC Logic and the Priority Encoder, we reduce the number of lines out back to n-bits, in our case 2-bits.

Within the Flash ADC, the Priority Encoder will first be designed. The ADC Logic will be designed later in Altium in Section [Hardware schematic](#hardware-schematic). With the Priority Encoder taking in 4 bits and outputting 2 bits, created below is the Truth Table with inputs x[3..0] and outputs y[1..0]. Note that only the realized outputs are shown in the table as others are not possible and considered as don't cares (X). In any combination where the higher bits are '1' then all lower bits must also be '1' as the resistor ladder will have lower potential nodes already lactive.  

![Priority_Encoder_2-bit_Truth_Table](README_IMAGES/Priority_Encoder_2-bit_Truth_Table.png)

Given the truth table, we can draw a 4 variable Karnaugh Map (K-Map) for both outputs. Shown below in the 2-bit Priority Encoder K-Map, we can use the don't cares in our combinational logic design because they will never be an outcome in the ADC Logic. Being able to do this, we can decrease the number of logic gates used. This decreases the cost of the design as well as the critical path when considering propagation delay.

![Priority_Encoder_2-bit_K-Map](README_IMAGES/Priority_Encoder_2-bit_K-Map.png)

By including 'X' in the K-Map grouping, we end up only using 3 logic gates shown below for the 2-bit ADC. 

![Priority_Encoder_2-bit_combinational_logic](README_IMAGES/Priority_Encoder_2-bit_combinational_logic.png)

Given the design of the Priority Encoder, we will next use this design alongside the Flash ADC resistive ladder and Op-Amps to create the hardware schematic. Included will be supplemental discrete components such as coupling capacitors and a voltage regulator. 

To determine what the max sampling rate will be, we need to determine the critical path of our schematic. As seen in the next section, we can determine the max propagation delay. The longest path for a signal will go through the LM438N and with slew rate of 0.3V/us for a max change from 0V to 5V we would see a 16us delay. 

Next we look at the combinational logic which for the critical path goes through the 74LS04, 74LS08 and 74LS32. The LS04 has a max delay of 15ns, LS08 has a max delay of 18ns and the LS32 has a max delay of 15ns. 

Finally, with the bistable latch we can expect a max delay for the 74LS75 to be 30ns. 

Since the LM358 is a general op-amp we can't expect the propagation delay to be efficient so most of the time waiting for the signal to stabilize can be at the op-amp. Nevertheless, our critical path gives us a max propagation delay of 16us + 15ns + 18ns + 15 + 30ns = 16.078us for a max sampling rate close to 62kHz.

#### 4-bit Flash ADC
The next design is the 4-bit Flash ADC whic is built similar to the 2-bit design but with a slight modification to the priority encoder circuit. Below is the updated architecture for the 4-bit design.

![architecture_of_4-bit_Flash_ADC](README_IMAGES/architecture_of_4-bit_Flash_ADC.png)

Using the LM358N Op-Amp we will need to increase the number of ICs used from 2 to 8 to compare the incoming voltage into 15 distinct levels. In the 2-bit design, the combinational logic for the priority encoder took in 4 variables and was completed using a K-Map. With the 4-bit design, in order to solve using a K-Map we would use 16 variables. As solving a K-Map with 5 variables already becomes difficult by hand, 16 variables for a computer is not efficient when there are simpler solutions. While looking at solutions to this problem within the [Debugging](#debugging) Section, I determined the best solution was to use an 8 to 3 line priority encoder. The 74LS148N is an 8 to 3 line priority encoder that is compatible with Transistor-Transistor Logic (TTL) as it is inside the 74LS IC family. By cascading 2 of these ICs together, we can create a 16 to 4 line priority encoder which can be used in place of our combinatinal logic previously solved by the K-Map. Straight from the datasheet for the [SN74LS148N](https://www.ti.com/lit/ds/symlink/sn54ls148.pdf?ts=1718085474640&ref_url=https%253A%252F%252Fwww.google.com%252F) can be found an application diagram showing how to create the 16 to 4 line priority encoder. Below I have screenshotted this diagram to display the required connections.

![74LS148_16-bit_priority_encoder](README_IMAGES/74LS148_16-bit_priority_encoder.png)

Note that the connections to the 74LS148 are active low and in order to be compatible with the current design, we will need to use inverters for the input and output signals. Once complete, we can use the existing latch IC to output the digital logic upon holding the enable pin low. 

### Hardware schematic
<!-- can be left for PCB Schematic !>> -->
Below is the hardware schematics for the 2-bit Flash ADC. Going with a hierarchical schematic structure, we can see the Top View with the three system blocks.

![TopView_2-bit_Flash_ADC_Schematic](README_IMAGES/TopView_2-bit_Flash_ADC_Schematic.png)

Next is the ADC Logic showing the resistor ladder with each node acting as a voltage comparator.

![ADC_Logic_2-bit_Flash_ADC_Schematic](README_IMAGES/ADC_Logic_2-bit_Flash_ADC_Schematic.png)

Powering the circuit is the 7805CT voltage regulator which provides the 5V supply.

![Power_2-bit_Flash_ADC_Schematic](README_IMAGES/Power_2-bit_Flash_ADC_Schematic.png)

The combinational logic produced form the K-Map shown below

![Priority_Encoder_2-bit_Flash_ADC_Schematic](README_IMAGES/Priority_Encoder_2-bit_Flash_ADC_Schematic.png)

The final design converted to a PCB within Altium is shown below. The Bill Of Materials (BOM) Document for the design can be found in the [Documentation](#documentation) Section.

![2-bit_Flash_ADC_PCB](README_IMAGES/2-bit_Flash_ADC_PCB.png)


### Software algorithms or flow chart
For the 2-bit Flash ADC the [Arduino Code](https://github.com/J0NTrollston/ADC-and-DAC-Design/blob/main/ADC-DAC-Arduino_Code/src/main.cpp) will take in 2 inputs and outputs an enable pin to the ADC to hold the data. The enable pin is active high and is pulled low while reading the 2 bits. Adding a delay will set the sampling frequency from the ADC but should be no less than 1ms for stability. 

    // set enable to low and latch onto current data
    PORTD_Reg &= ~(1<<Enable_Pin);

    // read data
    y0 = (PINB_Reg) &= (1<<PINB0);
    y1 = (PINB_Reg) &= (1<<PINB1);

    // set enable back to high
    PORTD_Reg |= (1<<Enable_Pin);

Below if the general flowchart for the Arduino Code to take in the ADC data.

![Flash ADC Flowchart](/ADC_Design/README_IMAGES/Flash_ADC_Flowchart.png)

### Debugging
This section goes over the various issues I had throughout the project and how I resolved the problem. Not everything will work out as expected and being able to troubleshoot an issues gives you an excersise to determine if you actually know what you are doing. For example, the first issue I had came about when I was created my 2-bit Flash ADC on the breadboard. When I completed the comparator ADC Logic that took in a certain voltage from the resistive ladder, I was getting a different output than what was expected. Although my input voltage was lower than all voltage references on the resistive ladder, I saw a high voltage output from the op-amp used as the MSB. Although all other op-amps were firing as expected in referenc to the input voltage, I took me some time to determine what the issue was. Using the LM358N Operational Amplifier as my comparator in the ADC Logic, I noticed in the datasheet that the LM358N is not a Rail-to-Rail In IC. The highest input voltage allowed is 1.5V less than V<sub>cc</sub> which for a 5V Supply allows for a max input of 3.5V. Since I had an abudance of the LM358N ICs, I went ahead and used them instead of buying more chips for the project. I do see there being a possibility later in the future where I go back and change the LM358N to a different chip that is Rail-to-Rail but for the time being I will leave it as is. However, I cannot leave the resistor ladder unchanged. Because the MSB comparator must be less than 3.5V I doubled the value of the top resistor and left the rest of the values unchanges. For a 5V Supply and a R<sub>eq</sub> for the resistive ladder at 6 k&#8486; gives a current of 0.83 mA. So the voltage drop at the top resistor is 0.83 mA * 2 k&#8486; = 1.67V which is in the range of the max allowed input voltage of 3.5V. With the LM358N not being a Rail-to-Rail op-amp, our 2-bit and 4-bit Flash ADC will not evenly measure the incoming voltage level. Therefore I have created a table below to describe the representation between each incoming voltage level to the output.

#### 2-bit Flash ADC encoded voltage level reference
| Voltage Ladder (Volts) | Encoded Output |
|---|---|
| 3.33 | 11 |
| 2.50 | 10 |
| 1.67 | 01 |
| 0.83 | 00 |

#### 4-bit Flash ADC encoded voltage level reference

| Voltage Ladder (Volts) | Encoded Output |
|---|---|
| 3.49 | 1111 |
| 3.27 | 1110 |
| 3.05 | 1101 |
| 2.83 | 1100 |
| 2.61 | 1011 |
| 2.40 | 1010 |
| 2.18 | 1001 |
| 1.94 | 1000 |
| 1.74 | 0111 |
| 1.52 | 0110 |
| 1.30 | 0101 |
| 1.09 | 0100 |
| 0.87 | 0011 |
| 0.65 | 0010 |
| 0.43 | 0001 |
| 0.21 | 0000 |


When designing the 4-bit Flash ADC, using a K-Map was an obvious no as they already become a hastle to solve for 5 and 6 variables. As the 4-bit Flash ADC was going to have 16 variables into the priority encoder, I had to look elsewhere. I did consider using the Quine-McCluskey Method since it could hand way more variables than a K-Map. But considering space constraints and unnecessary complexity that would be added to the project, I decided to us a different approach. The SN74LS148N is an 8-to-3 line priority encoder which could be cascaded and create a 16-to-4 line encoder. Although the inputs are active low, we can invert the signals coming in and out as to use it with our existing logic.
    

### Testing methodology or results
Testing the 2-bit Flash ADC I had added a variable resistor which is connected as the voltage in for the comparators. While changing the input voltage, the arduino code latches onto the data and reads in the 2-bit value. The breadboard design is shown below but for a visual demonstration without the arduino is shown in this [Video](https://youtu.be/kl4At6pt9WI).
![2-bit_Flash_ADC_Breadboard](README_IMAGES/2-bit_Flash_ADC_Breadboard.jpg)

With the same testing method used for the 2-bit design, I change the input voltage with a variable resistor on the 4-bit breadboard design shown below. For the visual demonstration without the arduino can be shown in this [Video](https://youtu.be/iKHJjdzjozc).

![4-bit_Flash_ADC_Breadboard](README_IMAGES/4-bit_Flash_ADC_Breadboard.jpg)



### Observations and Conclusions

### Documentation
<!-- parts list? Add BOM !>> -->
- [2-bit Flash ADC Bill Of Materials (BOM)](https://github.com/J0NTrollston/ADC-and-DAC-Design/blob/main/ADC_Design/2-bit-Flash-ADC-and-DAC-Design-BOM.xlsx)

- [SN74LS148N Datasheet](https://www.ti.com/lit/ds/symlink/sn54ls148.pdf?ts=1718085474640&ref_url=https%253A%252F%252Fwww.google.com%252F)
