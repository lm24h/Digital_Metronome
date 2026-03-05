#pragma once
// This file defines the I/O registers and bit masks and types for the microcontroller.
// It is used to configure the pins and control the digital I/O.

// define unsigned types
typedef unsigned char uint8_t;
typedef unsigned int  uint16_t;
typedef unsigned long uint32_t;

// define signed types
typedef char int8_t;
typedef int  int16_t;
typedef long int32_t;

// Define volatile types for I/O registers
typedef volatile uint8_t  reg8_t;
typedef volatile uint16_t reg16_t;


// Define bit masks each bit in a byte for easy manipulation
#define BIT0 0b00000001
#define BIT1 0b00000010
#define BIT2 0b00000100
#define BIT3 0b00001000
#define BIT4 0b00010000
#define BIT5 0b00100000
#define BIT6 0b01000000
#define BIT7 0b10000000

#define D13 BIT7
#define D12 BIT6
#define D5  BIT3
#define D11 BIT5
#define IR_RECEIVE_PIN BIT1

// Sleep mode
#define SMCR 0x53 // Sleep Mode Control Register
#define SLEEP_ENABLE   BIT0 // Sleep Enable bit in SMCR

// Define Pin Adresses
#define PORTA 0x22 // Pins A8-A15 (analog pins)
#define DDRA  0x21      // Data Direction Register for Port A
#define PINA  0x20      // Input Pins for Port A
#define PORTB 0x25 // Pins D8-D13, D53 (digital pins)
#define DDRB  0x24      // Data Direction Register for Port B
#define PINB  0x23      // Input Pins for Port B
#define PORTC 0x28 // Pins A0-A7 (analog input pins)
#define DDRC  0x27      // Data Direction Register for Port C
#define PINC  0x26      // Input Pins for Port C
#define PORTD 0x2B // Pins D0-D7 (digital pins, D0/D1: RX/TX)
#define DDRD  0x2A      // Data Direction Register for Port D
#define PIND  0x29      // Input Pins for Port D
#define PORTE 0x2E // Pins D2-D7, D3-D5 (digital pins, D3/D5: PWM pins)
#define DDRE  0x2D      // Data Direction Register for Port E
#define PINE  0x2C      // Input Pins for Port E
#define PORTF 0x31 // Pins A0-A7 (analog) (ADC channels 0-7)
#define DDRF  0x30      // Data Direction Register for Port F
#define PINF  0x2F      // Input Pins for Port F
#define PORTG 0x34 // Pins D22-D29 (digital pins)
#define DDRG  0x33      // Data Direction Register for Port G
#define PING  0x32      // Input Pins for Port G
#define PORTJ 0x105 // Pins D14-D21 (Serial1 pins TX1/RX1)
#define DDRJ  0x104      // Data Direction Register for Port J
#define PINJ  0x103      // Input Pins for Port J
#define PORTL 0x10B // Pins D42-D49 (PWM: D44-D46, digital pins)
#define DDRL  0x10A      // Data Direction Register for Port L
#define PINL  0x109      // Input Pins for Port L

// Defines for Timer1 
#define TCCR1A 0x80
#define TCCR1B 0x81
#define TIMSK1 0x6F
#define TIFR1  0x36
#define TCNT1  0x84
#define OCR1AH 0x89
#define OCR1AL 0x88
#define OCIF1A  BIT0 // Output Compare Interrupt Flag for Timer1 Compare Match A

// Defines for Timer3
#define TCCR3A 0x90
#define TCCR3B 0x91
#define TIMSK3 0x71 
#define TIFR3  0x38
#define TCNT3  0x94
#define OCR3AH 0x99
#define OCR3AL 0x98
#define ICR3H  0x97
#define ICR3L  0x96
#define OCF3A  BIT1 // Output Compare Flag for Timer3 Compare Match A

// Defines for UART
#define UBRR0H 0xC5
#define UBRR0L 0xC4
#define UCSR0A 0xC0
#define UCSR0B 0xC1
#define UCSR0C 0xC2
#define UDR0   0xC6

// Define some convenient macros for accessing the registers
#define DIR_BIT_REG_PORTB (*(reg8_t *)DDRB)
#define OUT_BIT_REG_PORTB (*(reg8_t *)PORTB)
#define DIR_BIT_REG_PORTD (*(reg8_t *)DDRD)
#define OUT_BIT_REG_PORTD (*(reg8_t *)PORTD)
#define DIR_BIT_REG_PORTE (*(reg8_t *)DDRE)
#define OUT_BIT_REG_PORTE (*(reg8_t *)PORTE)

// Define macros for Timer 1 registers
#define TIMER1_CTRL_REG_A   (*(reg8_t *)TCCR1A)
#define TIMER1_CTRL_REG_B   (*(reg8_t *)TCCR1B)
#define TIMER1_INT_MASK_REG (*(reg8_t *)TIMSK1)
#define OUTPUT_CAP_REG_1A_H (*(reg8_t *)(OCR1AH)) // Output Compare Register A high byte for Timer1
#define OUTPUT_CAP_REG_1A_L (*(reg8_t *)(OCR1AL)) // Output Compare Register A low byte for Timer1
#define TIMER1_INT_FLAG_REG (*(reg8_t *)TIFR1) // Timer1 Interrupt Flag Register
#define TIMER1_COUNT_REG    (*(reg16_t *)(TCNT1)) // Timer1 Counter Register

// Define macros for Timer3 registers
#define TIMER3_CTRL_REG_A   (*(reg8_t *)TCCR3A)
#define TIMER3_CTRL_REG_B   (*(reg8_t *)TCCR3B)
#define TIMER3_INT_MASK_REG (*(reg8_t *)TIMSK3)
#define OUTPUT_CAP_REG_3A_H (*(reg8_t *)(OCR3AH)) // Output Compare Register A high byte for Timer3
#define OUTPUT_CAP_REG_3A_L (*(reg8_t *)(OCR3AL)) // Output Compare Register A low byte for Timer3
#define TIMER3_INT_FLAG_REG (*(reg8_t *)TIFR3) // Timer3 Interrupt Flag Register
#define TIMER3_COUNT_REG    (*(reg16_t *)(TCNT3)) // Timer3 Counter Register
#define INPUT_CAPTURE_REG_3H (*(reg8_t *)(ICR3H)) // Input Capture Register high byte for Timer3
#define INPUT_CAPTURE_REG_3L (*(reg8_t *)(ICR3L)) // Input Capture Register low byte for Timer3

// Define macros for UART registers
#define BAUD_RATE_REG0_HIGH (*(reg8_t *)UBRR0H)
#define BAUD_RATE_REG0_LOW  (*(reg8_t *)UBRR0L)
#define USART_CTL_STATUS_0A (*(reg8_t *)UCSR0A)
#define USART_CTL_STATUS_0B (*(reg8_t *)UCSR0B)
#define USART_CTL_STATUS_0C (*(reg8_t *)UCSR0C)
#define USART_DATA_0        (*(reg8_t *)UDR0) // USART Data Register for UART0

#define SLEEP_CTRL_REG (*(reg8_t *)SMCR) // Sleep Mode Control Register

#define __INTR_ATTRS used, externally_visible

// Define some common functions for bit manipulation
#define __set_BIT(reg, bit)    ((reg) |=  (bit))
#define __clear_BIT(reg, bit)  ((reg) &= ~(bit))
#define __toggle_BIT(reg, bit) ((reg) ^=  (bit))
#define __read_BIT(reg, bit)   (((reg) &  (bit)) ? 1 : 0)
#define __start_TIMER1()       ((TIMER1_CTRL_REG_B) |=  0b00000101) // Start Timer1 with prescaler 1024
#define __stop_TIMER1()        ((TIMER1_CTRL_REG_B) &= ~0b00000111) // Stop Timer1
#define HIGH_BYTE(value)       (((value) >> 8) & 0xFF)
#define LOW_BYTE(value)        ((value) & 0xFF)