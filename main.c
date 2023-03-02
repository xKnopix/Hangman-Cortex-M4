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

uint32_t check(char guess, char *new_name, char *new_empty_name, uint32_t lang)
{
    uint32_t counter=0;
    for(uint32_t i = 0; i<lang; i++)
    {
        if(guess>=97)
        {
            if (new_name[i] == guess) {
                new_empty_name[i] = guess;
                counter++;
            } else {
                if (new_name[i] == guess - 32) {
                    new_empty_name[i] = guess - 32;
                    counter++;
                }
            }
        }
        else
            {
                if(new_name[i]== guess)
                {
                    new_empty_name[i]=guess;
                    counter++;
                }
                else
                {
                    if(new_name[i]==guess+32)
                    {
                        new_empty_name[i]= guess+32;
                        counter++;
                    }
                }
            }
        }
    return counter;
}


void main(void){
    printWelcomeHangman();
    uint32_t lang;
    char* userInput = getWordInput(&lang);
    uint32_t strich;
    uint32_t accept;
    char guess;
    uint32_t Bedingung;
    char new_empty_name[lang];
    for(uint32_t z=0;z< lang;z++)
    {
        new_empty_name[z]='-';
    }
    new_empty_name[lang] = '\0';
    while(strich <10 && accept!=lang)
    {
        printString("\033[0;0H");
        printString("\033[19B");
        printString("Please enter a guess (single letter pls)\n");

        guess=read_input();

        uint32_t q=check(guess, userInput, new_empty_name, lang);
        accept=accept+q;
        if(q==0)
        {
            printString("\033[2J");
            printString("\033[0;0H");
            printString("\033[20B");
            char versuchen[] ={"Sorry but   is not in the word\n"};
            versuchen[10]=guess;
            printString(versuchen);
            strich++;
            printFails(strich);
        }
        else
        {
            printString("\033[2J");
            printString("\033[0;0H");
            printString("\033[21B");
                printString(new_empty_name);
                printString("\n");
        }
    }
    if(strich>=10)
    {
        printString("Loooser\n");
    }
    else
    {
        printString("You Win!\n");
    }
    printEndMessage();

    for(;;);
}
