#include "UART.h"

void UART_init(void){
    // Calculated using the formula: baud = F_CPU / (16 * baud_rate) - 1
    uint16_t baud = 103; 

    // Set baud rate
    BAUD_RATE_REG0_HIGH = HIGH_BYTE(baud);
    BAUD_RATE_REG0_LOW  = LOW_BYTE(baud);

    // Enable transmitter
    __set_BIT(USART_CTL_STATUS_0B, TXEN0); 

    // Set frame format: 8data, 1stop bit
    __set_BIT(USART_CTL_STATUS_0C, UCSZ01 | UCSZ00); // Asynchronous mode, no parity
}
void UART_transmit_char(char data){

    // Wait for the transmit buffer to be empty
    while (!(USART_CTL_STATUS_0A & (1 << UDR0)));

    // Put data into buffer, sends the data
    USART_DATA_0 = data;
}
void UART_transmit(const char *data){
    while (*data) {
        UART_transmit_char(*data++);
    }
}
void UART_transmit_uint(uint32_t data){

    char buffer[10]; // Buffer to hold the string representation of the number (max 5 digits + null terminator)
    int i = 0;

    if (data == 0) {
        UART_transmit_char('0');
        return;
    }

    while (data > 0){
        buffer[i++] = (data % 10) + '0'; // Convert digit to character
        data /= 10; // Remove the last digit
    }

    while (i--)
        UART_transmit_char(buffer[i]);
}