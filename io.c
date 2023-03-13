#include "io.h"
#include "uart.h"

void printWelcomeHangman(void){

  /**
   * Dies ist eine Methode, um die Willkommensnachricht in ASCII-Art
   * und die ersten Anweisungen auszugeben.
   * @see printEndMessage()
   */
    //Setze Farbe auf Grün(32) und Hintergrund schwarz(40) 2 = dim/faint mode.
    printString("\033[2;32;40m");
    printString("\033[2J");
    printString("\033[1;0H");

    printString(" ____ ____ ____ ____ ____ ____ ____ ");
    printString("||H |||a |||n |||g |||m |||a |||n ||");
    printString("||__|||__|||__|||__|||__|||__|||__||");
    printString("|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|");

    printString("");
    printString("Set View: Settings -> Change Screen Size -> Rows = 40");
    printString("Press Enter to start the game...");

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

  /**
       * Dies ist eine Methode, um die Abschiedsnachricht in ASCII-Art auszugeben.
       * @see printWelcomeHangman()
       */
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

      /**
       * Funktion um ein Wort von einem Spieler abzufragen und als char Array zurückzugeben 
       * @param size Ein Pointer auf eine Integer-Variable, in welcher nach der Eingabe des Nutzers die Länge des eingegebenen Wortes gespeichert wird.
       * 
       * Die Funktion fragt in einer Endlosschleife Zeichen vom Spieler ab, bis Enter gedrückt wird.
       * Dabei werden die eingegebenen Zeichen direkt ausgegeben und in einem char Array gespeichert
       * 
       * @see getWordInput()
       * @see read_input()
       * @return Das Wort, welches der Spieler eingegeben hat, als char Array
       */
    
    //Setze Farbe auf Grün(32) und Hintergrund schwarz(40) 2 = dim/faint mode.
    printString("\033[2;32;40m");
    printString("\033[2J");
    printString("\033[1;0H");

    printString("Enter a word...(Can't be deleted using backspace)");
    printString("Max Length: 20, only letters");
    char textInput[100];

    for ( int n = 0; textInput[n] != 0; n++ )
      {
        textInput[n] = ' ';
      }

    int n = 0;

    printString("\033[2;37;40m");

    // Eingabe lesen, bis Enter gedrückt wird
    char c = read_input();
    while (c != '\r' && n<20 ){
        //Setze Curser auf stelle 3|0
        printString("\033[3;0H");
        if((c >=0x41 && c<=0x5A)||(c >=0x61 && c<=0x7A)){
            textInput[n] = c;
            n++;
            printString(textInput);
        }

        c = read_input();
        //Lösche alle Zeichen in der Zeile
        if((c >=0x41 && c<=0x5A)||(c >=0x61 && c<=0x7A)){
            printString("\033[2K"); 
        }
        *size = n;
    }

    if(n ==20){
      printString("You have reached the max length. Press Enter to continue...");
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

void printFails(uint32_t failCount)
{
  /**
       * Funktion um die ASCII-Art des Galgens entsprechend des Spielstandes ausuzugeben
       * @param failCount Ein Integer, welcher angibt, wie viele Fehlversuche der Spieler bereits hatte
       * 
       * Diese Funktion gibt die ASCII-Art des Galgens aus. Dabei wird die Zeichnung jedes mal erweitert,
       * ohne jedes mal alle vorigen Fehlversuche nochmals zu zeichnen.
       * 
       * @see printString()
       * @return Das Wort, welches der Spieler eingegeben hat, als char Array
       */
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
    printString("\033[0;0H");
}
    void printFailOne(void)
{
  /**
   * Methode um die ASCII-Art für Einen Fehlversuch auszugeben
  */
  printString("\033[2;32;40m");
  //printString("\033[2J");
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
  /**
   * Methode um die ASCII-Art für Zwei Fehlversuche auszugeben
  */
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
  /**
   * Methode um die ASCII-Art für Drei Fehlversuche auszugeben
  */
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
  /**
   * Methode um die ASCII-Art für Vier Fehlversuche auszugeben
  */
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
  /**
   * Methode um die ASCII-Art für Fünf Fehlversuche auszugeben
  */
  printString("\033[2;32;40m");
  //printString("\033[2J");
  printString("\033[3;0H");

  printString("\033[8;25f//");
  printString("\033[9;25f\\\\");
  printString("\033[10;25f//");
}
void printFailSix(void)
{
  /**
   * Methode um die ASCII-Art für Sechs Fehlversuche auszugeben
  */
  printString("\033[2;32;40m");
  //printString("\033[2J");
  printString("\033[3;0H");

  printString("\033[11;25fO");
}
void printFailSeven(void)
{
  /**
   * Methode um die ASCII-Art für Sieben Fehlversuche auszugeben
  */
  printString("\033[2;32;40m");
  //printString("\033[2J");
  printString("\033[3;0H");

  printString("\033[12;25f|");
  printString("\033[13;25f|");
}
void printFailEight(void)
{
  /**
   * Methode um die ASCII-Art für Acht Fehlversuche auszugeben
  */
  printString("\033[2;32;40m");
  //printString("\033[2J");
  printString("\033[3;0H");

  printString("\033[12;24f\\\033[1C/");
}
void printFailNine(void)
{
  /**
   * Methode um die ASCII-Art für Neun Fehlversuche auszugeben
  */
  printString("\033[2;32;40m");
  //printString("\033[2J");
  printString("\033[3;0H");

  printString("\033[14;24f/ \\");
}


