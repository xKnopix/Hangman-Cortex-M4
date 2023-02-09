#ifndef IO_H
#define IO_H

#include <stdint.h>

char* getWordInput(); //Überprufen ob String ohne Zahlen usw. 
uint8_t getReplay();
void printWelcomeHangman();
void printHangman(uint8_t mistakes, char input[]);// [--ll-]
void printEndMessage();

#endif