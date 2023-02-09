#ifndef IO_H
#define IO_H

#include <stdint.h>

char* getWordInput();
uint8_t getReplay();
void printHangman();
void printHangman(uint8_t mistakes, char input[]);
void printEndMessage();

#endif