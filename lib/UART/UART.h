#pragma once
#include "metronome_defines.h"
#define F_CPU 16000000UL // Define CPU frequency for baud rate calculation

// Defines for UART
#define TXEN0  BIT3 // Transmitter Enable bit in UCSR0B
#define RXEN0  BIT4 // Receiver Enable bit in UCSR0B
#define UCSZ00 BIT1 // Character Size bit 0 in UCSR0C
#define UCSZ01 BIT2 // Character Size bit 1 in UCSR0C
#define UDRE0  BIT5 // USART Data Register Empty bit in UCSR0A

#ifdef __cplusplus
extern "C" {    
#endif

void UART_init(void);
void UART_transmit(const char *data);
void UART_transmit_char(char data);
void UART_transmit_uint(uint32_t data);

#ifdef __cplusplus
} // extern "C"
#endif