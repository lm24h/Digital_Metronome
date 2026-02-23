#include <config.h>
#include <IORegister_types.h>
#include <remote.h>


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
     

    // Start with D13 LOW
     __clear_BIT(OUT_BIT_REG_PORTB, D13);

    // Enable Idle Sleep Mode
     SLEEP_CTRL_REG = SLEEP_ENABLE;

    // Enable global interrupts
     __global_interrupts(ENABLE); 

    while (true){
        asm volatile ("sleep"); // Enter sleep mode, will wake up on Timer1 Compare Match A interrupt
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
