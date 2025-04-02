#include "uart.h"
#include "gpio.h"

#define TXD_pin 6
#define RXD_pin 8
#define Baud9600 0x00275000
#define DISCONNECTED 0xFFFFFFFF


void uart_init(){
    GPIO->PIN_CNF[TXD_pin] =1;
    GPIO->PIN_CNF[RXD_pin] =0;

    UART->PSELTXD = TXD_pin;
    UART->PSELRXD = RXD_pin;

    UART->BAUDRATE = Baud9600;

    UART->PSELRTS = DISCONNECTED;
    UART->PSELCTS = DISCONNECTED;

    UART->ENABLE = 4;
    UART->TASKS_STARTTX = 1;
}

void uart_send(char letter){
    UART->TASKS_STARTTX = 1;
    UART->TXD = letter;
    while (!UART->EVENTS_TXDRDY){
    }
    UART->TASKS_STOPTX = 1;
    UART->TASKS_STARTTX = 0;
    UART->EVENTS_TXDRDY = 0;
}

char uart_read(){
    UART->TASKS_STARTRX = 1;
    if (UART->EVENTS_RXDRDY != 0) {
        // Nullstill EVENTS_RXDRDY før vi leser RXD for å unngå å lese samme data flere ganger
        UART->EVENTS_RXDRDY = 0;
        char letter = UART->RXD;
        
        return letter;
    }else {
        // Hvis ingen data er tilgjengelig, returner '\0'
        return '\0';
    }

  
}