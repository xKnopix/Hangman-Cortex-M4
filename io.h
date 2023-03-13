#ifndef IO_H
#define IO_H

#include <stdint.h>

char* getWordInput(uint32_t *size); //Überprufen ob String ohne Zahlen usw.
uint8_t getReplay(void);
void printWelcomeHangman(void);
void printHangman(uint8_t mistakes, char input[]);// [--ll-]
void printEndMessage(void);

void printFails(uint32_t failCount);
void printFailOne(void);
void printFailTwo(void);
void printFailThree(void);
void printFailFour(void);
void printFailFive(void);
void printFailSix(void);
void printFailSeven(void);
void printFailEight(void);
void printFailNine(void);

#endif
