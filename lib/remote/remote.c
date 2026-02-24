#include "remote.h"

void configTimer3() {
    // Configure Timer3 for free count 
    TIMER3_CTRL_REG_A    = 0;            // normal operation, no PWM
    TIMER3_CTRL_REG_B    = BIT0;   // no prescaler
    TIMER3_COUNT_REG     = 0;            // Reset Timer3 count to 0
}

uint16_t waitForLevel(uint8_t level){

    configTimer3(); // Reset Timer3 count to 0 before starting to decode

    while (__read_BIT(OUT_BIT_REG_PORTB, D11) != level);  // Wait for the specified level on the IR receiver pin
    uint16_t count1 = TIMER3_COUNT_REG;                    // Capture the count value at the moment the level is detected
    while (__read_BIT(OUT_BIT_REG_PORTB, D11) == level);  // Wait for the level to change back                

    TIMER3_CTRL_REG_B = 0;                  // Stop Timer3 after capturing the duration
    return TIMER3_COUNT_REG - count1;       // Return the elapsed count, which corresponds to the duration of the level
}

uint32_t decodeRemoteCode() {

    uint32_t code = 0;

    // Wait for the initial HIGH burst and get its duration
    uint16_t low  = waitForLevel(0); 
    uint16_t high = waitForLevel(1); 

    // Crude start check
    if (low < 8000 || high < 4000) {
        return 0; // Invalid start signal, return 0 or some error code
    }

    for (int i = 0; i < 32; i++) {

        waitForLevel(0); // Wait for the LOW level before each bit
        uint16_t duration = waitForLevel(1); // Wait for the HIGH level and get its duration

        if (duration > 1000) { // Threshold to distinguish between '0' and '1' (adjust as needed)
            code |= (1UL << i); // Set the appropriate bit if it's a '1'
        }
    }

    return code;
}


