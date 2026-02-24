#include "metronome_defines.h"
#include "config.h"
#include "remote.h"
#include "UART.h"


#define DELAY_1HZ 15624 // Calculated for 16MHz clock with prescaler 1024

enum InterruptState {
    ENABLE,
    DISABLE
};

// ----------------------------Timer1 Compare Match A ISR---------------------------- //
extern "C" void __vector_17(void) __attribute__((signal, __INTR_ATTRS));
void __vector_17(void)
{  
    __toggle_BIT(OUT_BIT_REG_PORTB, D13);    
}

void __global_interrupts(InterruptState);

// ----------------------------Main Routine---------------------------- //
int main() {

    // Configure the board
     configBoard();

    // Configure Timer1 with a TOP value corresponding to 8-bit resolution (255)
     configTimer1(DELAY_1HZ, PRESCALER_64);

    // Initialize UART for debugging 
     UART_init();
     
    // Start with D13 HIGH
     __set_BIT(OUT_BIT_REG_PORTB, D13);

    // Enable Idle Sleep Mode
     SLEEP_CTRL_REG = SLEEP_ENABLE;

    // Enable global interrupts
     __global_interrupts(DISABLE); 

    while (true){
        UART_transmit_uint(1); // Transmit the decoded code or 0 for invalid code
        UART_transmit_char('\n'); // Transmit newline character for readability
        for (volatile long i = 0; i < 200000; i++); // crude delay
    };

    return 0;
}

void __global_interrupts(InterruptState state) {
    if (state == ENABLE) {
        asm volatile ("sei");
    } else if (state == DISABLE) {
        asm volatile ("cli");
    }
}
