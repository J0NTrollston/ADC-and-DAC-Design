/*--------------------------------------------------------------------
Name:   Brandon Ramos
Date:   5/27/2024
Project: ADC-and-DAC-Design

Purp:  2-bit ADC code to pull data from breadboard circuit

Doc: 

--------------------------------------------------------------------*/
#include <Arduino.h>

#define PINB_Reg (*((volatile uint8_t *) 0x23)) //Reads the state of INPUT pin
#define DDRB_Reg (*((volatile uint8_t *) 0x24)) // I/O register, if set high the state is an output
#define PORTB_Reg (*((volatile uint8_t *) 0x25)) //Determines if pin is HIGH or LOW

#define PIND_Reg (*((volatile uint8_t *) 0x29)) //Reads the state of INPUT pin
#define DDRD_Reg (*((volatile uint8_t *) 0x2a)) // I/O register, if set high the state is an output
#define PORTD_Reg (*((volatile uint8_t *) 0x2b)) //Determines if pin is HIGH or LOW

// 2-Bit Flash ADC <-------------------------------------------------------------------->
#define Enable_Pin 2 // Pin 2 on the Arduino Uno is used as the enable pin for the latch
#define y1_Pin 9 //MSB of encoder output
#define y0_Pin 8 //LSB of encoder output

// encoder bits
bool y0 = 0;
bool y1 = 0;

void setup() {
  Serial.begin(9600);

  ADC_2_bit_setup();
}

void loop() {
  ADC_2_bit();
}


// 2-Bit Flash ADC Functions <-------------------------------------------------------------------->
void ADC_2_bit_setup(){
  // seet the enable pin as an active high output
  DDRD_Reg |= (1<<Enable_Pin);
  PORTD_Reg |= (1<<Enable_Pin);

  // set encoder inputs
  DDRB_Reg &= ~(1<<y0_Pin);
  DDRB_Reg &= ~(1<<y1_Pin);
}

void ADC_2_bit(){
    // set enable to low and latch onto current data
  PORTD_Reg &= ~(1<<Enable_Pin);

  // read data
  y0 = (PINB_Reg) &= (1<<PINB0);
  y1 = (PINB_Reg) &= (1<<PINB1);

  // set enable back to high
  PORTD_Reg |= (1<<Enable_Pin);

  Serial.print("Value: ");
  Serial.print(y1);
  Serial.println(y0);

  delay(100); //10 samples/s
}