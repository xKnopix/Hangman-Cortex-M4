#include "uart.h"
#include "registers.h"
#include "clockticks.h"
#include "main.h"
// Specific implementation for ARM-Cortex M4 here:

void uartInit( void )
{
  // Enable FIFO:
  // LCRH <-- LCRH_FEN
  writeToRegister( 0x4000C000 + 0x2C, 0x10 );

  // TODO: Calculate Baudrate
  // Todo: Settings for 115200,8,n,1

  // [9]    RXE   Receive enable
  // [8]    TXE   Transmit enable
  // [0] UARTEN   UART enable: 1-enable, 0-disable
  writeToRegister( 0x4000C000 + 0x30, 0x00000031 );// Control
}

void printString( const char *text )
{

  // Loop out the Data until zero reached!
  for ( int n = 0; text[n] != 0; n++ )
  {
    writeToRegister( 0x4000C000 + 0x00, text[n] );// Data
  }

  // Append \r\n, which results in a new line
  writeToRegister( 0x4000C000 + 0x00, '\r' );// Data
  writeToRegister( 0x4000C000 + 0x00, '\n' );// Data
}

void printStringWithLen( const char *text, int len )
{
  // Loop out the Data
  for ( int n = 0; n < len; n++ )
  {
    writeToRegister( 0x4000C000 + 0x00, text[n] );// Data
  }

  // Append \r\n, which results in a new line
  writeToRegister( 0x4000C000 + 0x00, '\r' );// Data
  writeToRegister( 0x4000C000 + 0x00, '\n' );// Data
}

// =================================================================================

char read_input( void )
{
  uint32_t DataRegister;
  uint32_t startTime = getCurrentTime();

  // FE = "FIFO EMPTY"
  // Active wait for not Empty fifo
  while ( readFromRegister( 0x4000C000 + 0x18 ) & 0x10 ){
    if ((getCurrentTime() - startTime) == 1000)
    {
      setTimercondition(1);
      return ' ';
    }
    
  }

  // Read from UART_O_DR
  DataRegister = readFromRegister( 0x4000C000 + 0x00 );

  DataRegister = DataRegister & 0x000000FF;// sanitize

  return (char)DataRegister;
}