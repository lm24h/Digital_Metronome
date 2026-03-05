#pragma once
#include "metronome_defines.h"

#define WGM13 BIT4
#define WGM12 BIT3
#define WGM11 BIT1
#define WGM10 BIT0
#define OCIE1A BIT1


#define TOGGLE_ON_COMPARE_MATCH BIT6 // Toggle OC1A on Compare Match for Timer1
#define CLEAR_ON_COMPARE_MATCH BIT7 // Clear OC1A on Compare Match for Timer1

#define PRESCALER_1024 0b00000101
#define PRESCALER_256  0b00000100
#define PRESCALER_64   0b00000011
#define PRESCALER_8    0b00000010
#define PRESCALER_1    0b00000001
#define PRESCALER_STOP 0b00000000

#ifdef __cplusplus
extern "C" {
#endif

void configBoard() {

    // Set D13 as output (PORTB bit 7)
    __set_BIT(DIR_BIT_REG_PORTB, D13); 

    // Set D5 as output (PORTE bit 5)
    __set_BIT(DIR_BIT_REG_PORTE, D5); 

    // Set pin 11 as Input w/ pull-up resistor
    __clear_BIT(DIR_BIT_REG_PORTB, D11);   
    __set_BIT(OUT_BIT_REG_PORTB, D11); 

    __set_BIT(DIR_BIT_REG_PORTE, IR_RECEIVE_PIN); // Set IR_RECEIVE_PIN as input
    __set_BIT(OUT_BIT_REG_PORTE, IR_RECEIVE_PIN); // Enable pull
} 

void configTimer1(uint16_t topValue, uint8_t prescaler) {
    // Configure Timer1 for CTC mode 
    TIMER1_CTRL_REG_A    = 0;                   // normal operation, no PWM
    TIMER1_CTRL_REG_B    = WGM12;               // CTC mode with OCR1A as TOP
    OUTPUT_CAP_REG_1A_H  = HIGH_BYTE(topValue); // Set TOP value for 8-bit resolution
    OUTPUT_CAP_REG_1A_L  = LOW_BYTE(topValue);  // Set TOP value for 8-bit resolution
    TIMER1_INT_MASK_REG |= OCIE1A;              // OCIE1A: Enable Timer1 Compare Match A interrupt
    TIMER1_CTRL_REG_B   |= prescaler;           // Start Timer1 with prescaler 
}

void configPWMTimer3(uint16_t frequency, uint8_t dutyCycle) {
    
    uint8_t prescaler = 8; // Choose a prescaler value (e.g., 8)
    uint16_t top = (16000000 / (prescaler*frequency)) - 1; // Calculate frequency for debugging
    uint16_t duty = (top * dutyCycle) / 100; // Calculate duty cycle value for debugging

    TIMER3_CTRL_REG_A     = (CLEAR_ON_COMPARE_MATCH |  WGM11);     // fast PWM / CTC mode with ICR3 as TOP, clear OC3A on compare match
    TIMER3_CTRL_REG_B     = (WGM12 | WGM13);     // CTC mode with OCR3A as TOP
    INPUT_CAPTURE_REG_3H  = HIGH_BYTE(top); // Set TOP value for 8-bit resolution
    INPUT_CAPTURE_REG_3L  = LOW_BYTE(top);  // Set TOP value for 8-bit resolution
    OUTPUT_CAP_REG_3A_H  = HIGH_BYTE(duty); // Set compare match value for the specified duty cycle
    OUTPUT_CAP_REG_3A_L  = LOW_BYTE(duty);  
    TIMER3_CTRL_REG_B    |= PRESCALER_8;           // Start Timer3 with prescaler 
}

#ifdef __cplusplus
} // extern "C"
#endif
