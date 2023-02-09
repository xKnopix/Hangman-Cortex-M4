#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>

void writeToRegister(uint32_t address, uint32_t value);
uint32_t readFromRegister(uint32_t address);

#endif