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

int check(char guess, char *new_name, char *new_empty_name, int lang)
{
    int counter=0;
    for(int i = 0; i<lang; i++)
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
    char* userInput = getWordInput();
    int strich;
    int accept;
    char guess;
    int Bedingung;
    int lang=sizeof(userInput);
    lang=lang+1;
    char new_empty_name[lang];
    for(int z=0;z< lang;z++)
    {
        new_empty_name[z]='-';
    }
    while(strich <10 && accept!=lang)
    {
        printString("Please enter a guess (single letter pls)\n");

        guess=read_input();

        int q=check(guess, userInput, new_empty_name, lang);
        accept=accept+q;
        if(q==0)
        {
            char versuchen[] ={"Sorry but   is not in the word\n"};
            versuchen[10]=guess;
            printString(versuchen);
            strich++;
            printFails(strich);
        }
        else
        {
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
