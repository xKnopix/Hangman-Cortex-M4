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

uint32_t check(char guess, char *alreadyGuessed, char *new_name, char *new_empty_name, uint32_t lang, uint32_t round)
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

        for ( int n = 0; alreadyGuessed[n] != 0; n++ )
        {
            if(alreadyGuessed[n] == guess)
            {
                counter = 0;
            }
        }
        alreadyGuessed[round] = guess;
    return counter;
}


void main(void){
    printWelcomeHangman();
    uint32_t lang = 0;
    
    uint32_t ON = 1;
    uint32_t OFF = 0;
    uint32_t game = ON;
    while(game == ON)
    {
        char alreadyGuessed[26];
        for ( int n = 0; alreadyGuessed[n] != 0; n++ )
        {
            alreadyGuessed[n] = ' ';
        }

        char* userInput = getWordInput(&lang);
        uint32_t strich = 0;
        uint32_t accept = 0;
        char guess;
        uint32_t Bedingung = 0;
        char new_empty_name[lang];
        uint32_t guesses = 0;

        for(uint32_t z=0;z< lang;z++)
        {
            new_empty_name[z]='-';
        }
        new_empty_name[lang] = '\0';
        while(strich <9 && accept!=lang)
        {
            printString("\033[0;0H"); //Cursor auf (0, 0)
            //printString("\033[19B");
            printString("Please enter a guess (single letter pls)\n");

            guess=read_input();

            uint32_t guessResult=check(guess, alreadyGuessed, userInput, new_empty_name, lang, guesses);
            accept=accept+guessResult;
            uint32_t wrong = 0;

            if(guessResult == wrong)
            {
                //printString("\033[2J");
                printString("\033[0;0H");
                printString("\033[21B");
                char versuchen[] ={"Sorry but   is not in the word\n"};
                versuchen[10]=guess;
                printString(versuchen);
                strich++;
                printFails(strich);
            }
            else
            {
                //printString("\033[2J");
                printString("\033[0;0H"); //Cursor auf (0, 0)
                printFails(strich);       //ASCII-Art entsprechend erweitern
                printString("\033[19B");
                printString(new_empty_name);
                printString("\n");
            }

            guesses++;
        }
    
    
        if(strich>=9)
        {
            printString("\033[0;0H"); //Cursor auf (0, 0)
            printString("\033[21B");
            printString("\x1b[1;31mYou Loose!                              \n"); //Leerzeichen, um vorigen Text zu löschen
        }
        else
        {
            printString("\033[0;0H"); //Cursor auf (0, 0)
            printString("\033[21B");
            printString("\x1b[1;33mYou Win!                                \n");
        }

        char failText[] ={"Fails:   \n"};
        char failChar = strich + '0';
        failText[8]= failChar;
        printString(failText);

        char guessText[] ={"Overall Guesses:   \n"};

        uint32_t zehnerStelle = guesses/10;
        uint32_t einerStelle = guesses % 10;
        char zehnerStelleChar = zehnerStelle + '0';
        char einerStelleChar = einerStelle + '0';
        guessText[17]= zehnerStelleChar;
        guessText[18]= einerStelleChar;
        printString(guessText);

        printString("Press [q] to quit the game or any other Key to Play again!");
        char nextAction = read_input();

        if(nextAction == 'q')
        {
            game = OFF;
            printEndMessage();
        }
        else
        {
            game = ON;
        }
        
    }
    for(;;);
}
