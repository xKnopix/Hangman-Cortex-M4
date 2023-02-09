#ifndef UART_H
#define UART_H

#include <stdint.h>


// for Init the UART:
void uartInit(void);

// Output Routines:
void printString(const char *text);
void printStringWithLen(const char *text, int len);

// Input Routines:
char read_input(void);

#endif