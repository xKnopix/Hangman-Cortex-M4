#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>

void setTimercondition(uint32_t condition);
uint32_t check(char guess, char *alreadyGuessed, char *wordToGuess, char *guessWordProgress, uint32_t guesses);
void main(void);


#endif
