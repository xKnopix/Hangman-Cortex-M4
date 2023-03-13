#include "main.h"
#include "uart.h"
#include "registers.h"
#include "io.h"
#include "clockticks.h"
#include <stdint.h>
#include <stdio.h>

#define CONTROLLSTSTUS 0xE000E010
#define RELOADVALUEREGISTER 0xE000E014
#define CURRENTVALUEREGISTER 0xE000E018
#define CALIBRATIONVALUEREGISTER 0xE000E01C

static uint32_t counter = 0;            
static uint32_t countermain = 0;        
static uint32_t timercondition = 0;     


void setTimercondition( uint32_t condition){
    timercondition = condition;
}

uint32_t check( char guess,
                char *alreadyGuessed,
                char *wordToGuess,
                char *guessWordProgress,
                uint32_t round)
{
    /**
       * Funktion um ein Wort von einem Spieler abzufragen und als char Array zurückzugeben 
       * @param guess  Das aktuell eingegebene Zeichen, welches geprüft werden soll.
       * @param alreadyGuessed Ein Array, welcher die bereits eingegebenen Zeichen des Nutzers enthält.
       * @param wordToGuess Ein Array, welcher das Wort, welches erraten werden soll enthält
       * @param guessWordProgress Ein Array, welcher die Ausgabe des zu erratenden Wortes mit Strichen für fehlende Buchstaben enthält
       * @param round Ein Integer, welcher die Anzahl der Rateversuche des aktuellen Spiels repräsentiert
       * 
       * Die Funktion fragt in einer Endlosschleife Zeichen vom Spieler ab, bis Enter gedrückt wird.
       * Dabei werden die eingegebenen Zeichen direkt ausgegeben und in einem char Array gespeichert
       * 
       * @see main()
       * @return 0 wenn der geratene Buchstabe falsch ist oder bereits geraten wurde, sonst 1(oder mehr)
       */
    uint32_t checkResult=0; 
    for(uint32_t i = 0; wordToGuess[i] != 0; i++)
    {
        if(guess>=97)
        {
            if (wordToGuess[i] == guess) {
                guessWordProgress[i] = guess;
                checkResult++;
            } else {
                if (wordToGuess[i] == guess - 32) {
                    guessWordProgress[i] = guess - 32;
                    checkResult++;
                }
            }
        }
        else
            {
                if(wordToGuess[i]== guess)
                {
                    guessWordProgress[i]=guess;
                    checkResult++;
                }
                else
                {
                    if(wordToGuess[i]==guess+32)
                    {
                        guessWordProgress[i]= guess+32;
                        checkResult++;
                    }
                }
            }
        }

        for ( int n = 0; alreadyGuessed[n] != 0; n++ )
        {
            if(alreadyGuessed[n] == guess)
            {
                checkResult = 0;
            }
        }
        alreadyGuessed[round] = guess;
    return checkResult;
}


void main(void /*!<Für den guten Stil*/){
    /**
       * Dies ist die main()-Funktion des Hangman Spiels.
       * Sie beinhaltet eine Endlosschleife, welche einmal
       * pro gespieltem Spiel durchlaufen wird und nur durch
       * drücken von 'q' am Ende eines Spiels beendet werden
       * kann.
       * @see main()
       */
    startClock();
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


        char* wordToGuess = "";
        wordLength = 0;
        while (wordLength <1)
        {
            wordToGuess = getWordInput(&wordLength);            //Hole von einem Spieler das Wort, welches erraten werden soll
        }
        failCount = 0;
        guesses = 0;
        resetClock();
        setTimercondition(0);
        
        char guessWordProgress[wordLength];

        
        

        for(uint32_t z=0;z< wordLength;z++)
        {
            guessWordProgress[z]='-';
        }
        guessWordProgress[wordLength] = '\0';
        while(failCount <9 && correctGuessCounter!=wordLength)
        {
            printString("\033[0;0H"); //Cursor auf (0, 0)
            printString("Please enter a guess (if you take too long it's a guess)\n");

            guess = 0x00;
            while (!((guess >=0x41 && guess<=0x5A)||(guess >=0x61 && guess<=0x7A)) && timercondition == 0)
            {
                guess=read_input();
            }
            

            guessResult=check(guess, alreadyGuessed, wordToGuess, guessWordProgress, guesses);
            correctGuessCounter=correctGuessCounter+guessResult;
            

            printString("\033[0;0H"); //Cursor auf (0 | 0)
            if(guessResult == wrong && timercondition == 0)
            {
                printString("\033[21B");    //Cursor auf Zeile 21
                char versuchen[] ={"Sorry but   is not in the word                               \n"};
                versuchen[10]=guess;
                printString(versuchen);
                failCount++;
                printFails(failCount);
            }
            else if(timercondition == 1)
            {
                printString("\033[21B");    //Cursor auf Zeile 21
                char versuchen[] ={"You took to long to guess!                                   \n"};
                printString(versuchen);
                failCount++;
                printFails(failCount);
                setTimercondition(0);
            } 
            else
            {
                //printString("\033[2J");
                //printFails(failCount);       //ASCII-Art entsprechend erweitern
                printString("\033[19B");    //Cursor auf Zeile 19
                printString(guessWordProgress);
                printString(" ");    //Cursor auf Zeile 19
                printString("\033[2K");
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

        printString("Press [q] to quit the game or any other Key to Play again or wait a few seconds!\n");
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
    for(;;)
    {
       mainTime++;
    }
}
