#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>

void setTimercondition(uint32_t condition);
uint32_t check(char guess, char *alreadyGuessed, char *new_name, char *new_empty_name, uint32_t round);
void main(void);


#endif
