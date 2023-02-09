#include "main.h"
#include "uart.h"
#include "registers.h"
#include "io.h"
#include <stdint.h>
#include <stdio.h>

#define CONTROLLSTSTUS 0xE000E010
#define RELOADVALUEREGISTER 0xE000E014
#define CURRENTVALUEREGISTER 0xE000E018
#define CALIBRATIONVALUEREGISTER 0xE000E01C

static uint32_t counter = 0;//global
static uint32_t countermain = 0;

void main(void){
    printWelcomeHangman();
    char* userInput = getWordInput();
    printEndMessage();

    for(;;);
}