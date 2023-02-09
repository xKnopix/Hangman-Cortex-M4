#include "main.h"
#include "uart.h"
#include "registers.h"
#include <stdint.h>

#define CONTROLLSTSTUS 0xE000E010
#define RELOADVALUEREGISTER 0xE000E014
#define CURRENTVALUEREGISTER 0xE000E018
#define CALIBRATIONVALUEREGISTER 0xE000E01C

static uint32_t counter = 0;//global
static uint32_t countermain = 0;

void main(void){
    //writeToRegister(0x20001000, 0xCAFEAFFE);
    //uint32_t value = 0;
    //value = readFromRegister(0x20001000);

    //Timer setzen
    writeToRegister(RELOADVALUEREGISTER, 0x100000); // Reload Value Register 
    writeToRegister(CURRENTVALUEREGISTER, 0x100000); // CurrentValue Register 0xE000E018
    //writeToRegister(CALIBRATIONVALUEREGISTER, 0x100); // Calibration value Register somehow Not used
    writeToRegister(CONTROLLSTSTUS, 0x07); // Controll and Status register

    char textInput[100];
    int n = 0;

    // Eingabe lesen, bis Enter gedrückt wird
    char c = read_input();
    while (c != '\r')
    {
        textInput[n] = c;
        n++;
        printString(textInput);
        c = read_input();
        printString("\033[2J");
        printString("\033[0;0H");
    }

    // Null-Terminierung hinzufügen
    textInput[n] = '\0';

    // Ausgabe mit printString()
    printString(textInput);
    

    //text = "\033[2J";
    //printString(text);
    
    for(;;){
        countermain++;
    }

}

//ISR
void SysTick_Handler(){
    counter++;
    writeToRegister(0x20001000, 0xCAFEAFFE);
}