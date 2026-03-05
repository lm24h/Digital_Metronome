// ----------------------------Includes---------------------------- //
#include "metronome_defines.h"
#include "config.h"
#include "remote.h"

// ------------ Defines ------------ //
#define DELAY_1HZ 7813  // Calculated for 16MHz clock with prescaler 1024
#define DELAY_2HZ 15624
 // Macro to calculate delay value for a given BPM

// ------------ Global Variables ------------ //
enum InterruptState {
    ENABLE,
    DISABLE
};
enum TimeUnit {
    SECOND,
    MILLISECOND,
    MICROSECOND
};

// ------------ Function Prototypes ------------ //
void __global_interrupts(InterruptState);
void Timer1Delay(uint32_t delay, TimeUnit unit);
void turnOffBuzzer();
void turnOnBuzzer();

// ----------------------------Main Routine---------------------------- //
int main() {

    // Configure the board
     configBoard();

    // Configure Timer1 with a TOP value corresponding to 8-bit resolution (255)
     configTimer1(DELAY_1HZ, PRESCALER_1024);
     
    // Start with D13 HIGH
     __set_BIT(OUT_BIT_REG_PORTB, D13);

    // Enable Idle Sleep Mode
     SLEEP_CTRL_REG = SLEEP_ENABLE;

    // Enable global interrupts
     __global_interrupts(DISABLE); 

    configPWMTimer3(100, 90);

    while (true){
        // configure and start PMW on Timer3 for buzzer
        turnOnBuzzer(); // Start the buzzer
        Timer1Delay(100, MILLISECOND); // Delay for .1 second
        turnOffBuzzer(); // Stop the buzzer
        Timer1Delay(757143, MICROSECOND); // Delay for .757 second
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

void Timer1Delay(uint32_t delay, TimeUnit unit) {

    uint16_t delayValue;
    switch (unit) {

        case MICROSECOND:
            delayValue = delay / 64;
            break;

        case MILLISECOND:
            delayValue = (delay * 1000) / 64;
            break;

        case SECOND:
            delayValue = (delay * 1000000) / 64;
            break;
    }

    configTimer1(delayValue, PRESCALER_1024);
    while (!(TIMER1_INT_FLAG_REG & OCIE1A)); // Wait for the compare match flag to be set
    TIMER1_INT_FLAG_REG |= OCIE1A; // Clear the interrupt flag by writing a 1 to it
}

void turnOffBuzzer() {
    // Stop Timer3 to turn off the buzzer
    TIMER3_CTRL_REG_B &= ~0b00000111; // Clear the prescaler bits to stop Timer3
}

void turnOnBuzzer() {
    // Start Timer3 with prescaler 8 to turn on the buzzer
    TIMER3_CTRL_REG_B |= PRESCALER_8; 
}

// ----------------------------Timer1 Compare Match A ISR---------------------------- //
extern "C" void __vector_17(void) __attribute__((signal, __INTR_ATTRS));
void __vector_17(void)
{  
    __toggle_BIT(OUT_BIT_REG_PORTB, D13);    
}
