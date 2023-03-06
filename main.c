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

uint32_t check(char guess, char *alreadyGuessed, char *new_name, char *guessWordProgress, uint32_t round)
{
    uint32_t counter=0;
    for(uint32_t i = 0; new_name[i] != 0; i++)
    {
        if(guess>=97)
        {
            if (new_name[i] == guess) {
                guessWordProgress[i] = guess;
                counter++;
            } else {
                if (new_name[i] == guess - 32) {
                    guessWordProgress[i] = guess - 32;
                    counter++;
                }
            }
        }
        else
            {
                if(new_name[i]== guess)
                {
                    guessWordProgress[i]=guess;
                    counter++;
                }
                else
                {
                    if(new_name[i]==guess+32)
                    {
                        guessWordProgress[i]= guess+32;
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
    uint32_t wordLength = 0;                                    //Integer in welchem die Länge des zu ratenden Wortes gespeichert wird
    
    uint32_t ON = 1;                                            //Integer zur Besseren Lesbarkeit des Codes
    uint32_t OFF = 0;                                           //                  ||
    uint32_t game = ON;                                         //                  ||
    uint32_t wrong = 0;                                         //                  ||

    while(game == ON)
    {   
        uint32_t    failCount = 0,
                    correctGuessCounter = 0,
                    guesses = 0,
                    guessResult = 0;

        char alreadyGuessed[26];                                //Array für bereits geratene Buchstaben zur Überprüfung doppelter Eingaben
        char guess;

        for ( int n = 0; alreadyGuessed[n] != 0; n++ )          //Den Array leeren, dass keine Eingaben bei einem Spielneustart vorhanden sind
        {
            alreadyGuessed[n] = ' ';
        }

        char* userInput = getWordInput(&wordLength);            //Hole von einem Spieler das Wort, welches erraten werden soll

        char guessWordProgress[wordLength];

        
        

        for(uint32_t z=0;z< wordLength;z++)
        {
            guessWordProgress[z]='-';
        }
        guessWordProgress[wordLength] = '\0';
        while(failCount <9 && correctGuessCounter!=wordLength)
        {
            printString("\033[0;0H"); //Cursor auf (0, 0)
            printString("Please enter a guess (single letter pls)\n");

            guess=read_input();

            guessResult=check(guess, alreadyGuessed, userInput, guessWordProgress, guesses);
            correctGuessCounter=correctGuessCounter+guessResult;
            

            printString("\033[0;0H"); //Cursor auf (0 | 0)
            if(guessResult == wrong)
            {
                printString("\033[21B");    //Cursor auf Zeile 21
                char versuchen[] ={"Sorry but   is not in the word\n"};
                versuchen[10]=guess;
                printString(versuchen);
                failCount++;
                printFails(failCount);
            }
            else
            {
                //printString("\033[2J");
                //printFails(failCount);       //ASCII-Art entsprechend erweitern
                printString("\033[19B");    //Cursor auf Zeile 19
                printString(guessWordProgress);
                printString("\n");
            }

            guesses++;
        }
    
    
        if(failCount>=9)
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
        char failChar = failCount + '0';
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
