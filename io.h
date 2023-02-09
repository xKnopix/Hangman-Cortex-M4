#ifndef IO_H
#define IO_H

#include <stdint.h>

char* getWordInput(void); //Überprufen ob String ohne Zahlen usw. 
uint8_t getReplay(void);
void printWelcomeHangman(void);
void printHangman(uint8_t mistakes, char input[]);// [--ll-]
void printEndMessage(void);

#endif