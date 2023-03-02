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
//neu
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

char* getWordInput(uint32_t *size){


    
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
        *size = n;

    }

    if(n ==20){
      printString("Die maximale Laenge wurde erreicht druecke Enter...");
      while (c != '\r'){
        c = read_input();
      }
    }
    printString("\033[2;32;40m");
    //Lösche alle Zeichen
    printString("\033[2J");
    printString("\033[0;0H");

    // Null-Terminierung hinzufügen
    //textInput[n] = '\0';

    char* t = textInput;

    return t;

}

void printFails(int failCount)
{
  switch(failCount)
  {
    case 1:
      printFailOne();
      break;
    case 2:
      printFailTwo();
      break;
    case 3:
      printFailThree();
      break;
    case 4:
      printFailFour();
      break;
    case 5:
      printFailFive();
      break;
    case 6:
      printFailSix();
      break;
    case 7:
      printFailSeven();
      break;
    case 8:
      printFailEight();
      break;
    case 9:
      printFailNine();
      break;
  }
}
    void printFailOne(void)
{
  printString("\033[2;32;40m");
  printString("\033[2J");
  printString("\033[4;0H");

  printString("\033[14;0f");
  printString("\033[1A       ____________");
  printString("     /\\___________/\\");
  printString("    / /   _____   \\ \\");
  printString("   / /   /     \\   \\ \\");
  printString("  / /   /       \\   \\ \\");
  printString(" / /   /         \\   \\ \\");
  printString(" \\/___/           \\___\\/");
}

void printFailTwo(void)
{
  printString("\033[2;32;40m");
  //printString("\033[2J");
  printString("\033[4;0H");

  printString("\033[4;0f");
  printString("\033[1A            ___");
  printString("           /__/|");
  printString("          |   ||");
  printString("          |   ||");
  printString("          |   ||");
  printString("          |   ||");
  printString("          |   ||");
  printString("          |   ||");
  printString("          |   ||");
  printString("          |   ||");
  printString("\033[10C|   ||");
  printString("\033[10C|\033[3C|/");
}
void printFailThree(void)
{
  printString("\033[2;32;40m");
  //printString("\033[2J");
  printString("\033[3;0H");

  printString("\033[4;13f_______________");
  printString("\033[12C______________/|");
  printString("\033[11C               ||");
  printString("\033[11C    ___________|/");
}
void printFailFour(void)
{
  printString("\033[2;32;40m");
  //printString("\033[2J");
  printString("\033[3;0H");

  printString("\033[8;17f/ //");
  printString("\033[9;16f/ //");
  printString("\033[10;16f //");
  printString("\033[11;16f//");
  printString("\033[12;16f/");
}
void printFailFive(void)
{
  printString("\033[2;32;40m");
  //printString("\033[2J");
  printString("\033[3;0H");

  printString("\033[8;25f//");
  printString("\033[9;25f\\\\");
  printString("\033[10;25f//");
}
void printFailSix(void)
{
  printString("\033[2;32;40m");
  //printString("\033[2J");
  printString("\033[3;0H");

  printString("\033[11;25fO");
}
void printFailSeven(void)
{
  printString("\033[2;32;40m");
  //printString("\033[2J");
  printString("\033[3;0H");

  printString("\033[12;25f|");
  printString("\033[13;25f|");
}
void printFailEight(void)
{
  printString("\033[2;32;40m");
  //printString("\033[2J");
  printString("\033[3;0H");

  printString("\033[12;24f\\\033[1C/");
}
void printFailNine(void)
{
  printString("\033[2;32;40m");
  //printString("\033[2J");
  printString("\033[3;0H");

  printString("\033[14;24f/ \\");
}


