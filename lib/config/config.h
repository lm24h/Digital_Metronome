#pragma once
#include "IORegister_types.h"

#define WGM13 BIT4
#define WGM12 BIT3
#define WGM11 BIT1
#define WGM10 BIT0
#define OCIE1A BIT1

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

    // Set pin 11 as Input w/ pull-up resistor
    __clear_BIT(DIR_BIT_REG_PORTB, D11);   
    __set_BIT(OUT_BIT_REG_PORTB, D11); 
} 

void configTimer1(uint16_t topValue, uint8_t prescaler) {
    // Configure Timer1 for CTC mode 
    TIMER1_CTRL_REG_A    = 0;            // normal operation, no PWM
    TIMER1_CTRL_REG_B    = WGM12;   // CTC mode with OCR1A as TOP
    OUTPUT_CAP_REG_1A_H  = HIGH_BYTE(topValue);     // Set TOP value for 8-bit resolution
    OUTPUT_CAP_REG_1A_L  = LOW_BYTE(topValue);   // Set TOP value for 8-bit resolution
    TIMER1_INT_MASK_REG |= OCIE1A; // OCIE1A: Enable Timer1 Compare Match A interrupt
    TIMER1_CTRL_REG_B   |= prescaler; // Start Timer1 with prescaler 
}

void configTimer3() {
    // Configure Timer3 for free count 
    TIMER3_CTRL_REG_A    = 0;            // normal operation, no PWM
    TIMER3_CTRL_REG_B    = BIT0;   // no prescaler
    TIMER3_COUNT_REG     = 0;            // Reset Timer3 count to 0
}
#ifdef __cplusplus
} // extern "C"
#endif
