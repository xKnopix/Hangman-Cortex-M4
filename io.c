#include "io.h"
#include "uart.h"

void printWelcomeHangman(void){
    //Setze Farbe auf Grün(32) und Hintergrund schwarz(40) 2 = dim/faint mode.
    printString("\033[2;32;40m");
    printString("\033[2J");
    printString("\033[1;0H");

    printString(" ____ ____ ____ ____ ____ ____ ____ ");
    printString("||H |||a |||n |||g |||m |||a |||n ||");
    printString("||__|||__|||__|||__|||__|||__|||__||");
    printString("|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|");

    printString("");
    printString("Druecke Enter um das Spiel zu beginnen...");

    char c = read_input();
    while (c != '\r')
    {
        c = read_input();
    }

    //Alles Löschen
    printString("\033[2J");
    printString("\033[1;0H");
    
   
}

void printEndMessage(void){
    //Setze Farbe auf Grün(32) und Hintergrund schwarz(40) 2 = dim/faint mode.
    printString("\033[2;32;40m");
    printString("\033[2J");
    printString("\033[1;0H");

    printString(" ____ ____ ____ ");
    printString("||B |||y |||e ||");
    printString("||__|||__|||__||");
    printString("|/__\\|/__\\|/__\\|");


}

char* getWordInput(void){
    
    //Setze Farbe auf Grün(32) und Hintergrund schwarz(40) 2 = dim/faint mode.
    printString("\033[2;32;40m");
    printString("\033[2J");
    printString("\033[1;0H");

    printString("Geben Sie das Wort ein, welches erraten werden soll");
    char textInput[100];
    int n = 0;

    printString("\033[2;37;40m");

    // Eingabe lesen, bis Enter gedrückt wird
    char c = read_input();
    while (c != '\r' && n<20 ){
        //Setze Curser auf stelle 2|0
        printString("\033[2;0H");
        if(c != ' ' && c != '1'&& c != '2'&& c != '3'&& c != '4'&& c != '5'&& c != '6'&& c != '7'&& c != '8'&& c != '9'&& c != '0'){
            textInput[n] = c;
            n++;
            printString(textInput);
        }

        c = read_input();
        //Lösche alle Zeichen in der Zeile
        if(c != ' ' && c != '1'&& c != '2'&& c != '3'&& c != '4'&& c != '5'&& c != '6'&& c != '7'&& c != '8'&& c != '9'&& c != '0'){
            printString("\033[2K"); 
        }

    }
    printString("\033[2;32;40m");
    //Lösche alle Zeichen
    printString("\033[2J");
    printString("\033[0;0H");

    // Null-Terminierung hinzufügen
    textInput[n] = '\0';

    char* t = textInput;

    return t;

}