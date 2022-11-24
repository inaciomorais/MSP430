/* 
 * Using External 16x2 LCD Display
 *
 * LCD VSS pin (1) to ground
 * LCD VCC pin (2) to +5Vcc from MSP430G2553 Value Line Launchpad Test Pin 1 (TP1)
 * LCD Register Select line - RS (4) P2.4
 * LCD R/W pin (5) to ground
 * LCD Enable - E (6) P2.5
 * LCD D4 (11) P2.0
 * LCD D5 (12) P2.1
 * LCD D6 (13) P2.2
 * LCD D7 (14) P2.3
 */

#include <msp430.h>
#include "lcd_display.h"

void clock_config(void);

main()
{
	WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer
	
	clock_config();             			
	LCD_Initialize(16);             // This routine initializes the LCD driver. 16MHz (DCO Frequency)

	LCDGoto(0,0);                   // This function positions the cursor at the specified Line and column
	LCDPutStr("                ");  // This routine writes string to LCD at current cursor position

	LCDGoto(0,1);
	LCDPutStr("           HELLO");
}

void clock_config(void)
{
    BCSCTL1 = CALBC1_16MHZ;      // 16MHz DCO Frequency (Calibrated DCOCTL and
    DCOCTL  = CALDCO_16MHZ;      // BCSCTL1 register settings)
}

/* How to call some special built-in characters:
 *
 * HITACHI HD44780U ROM A02 Pattern (Datasheet page 18)
 *
 *   LCDPutChar(0x9A); // Ω      LCDPutChar(0xAB); // <<     LCDPutChar(0xBB); // >>     LCDPutChar(0xB0); // °
 *   LCDPutChar(0xC0); // À      LCDPutChar(0xE0); // à      LCDPutChar(0xC1); // Á      LCDPutChar(0xE1); // á
 *   LCDPutChar(0xC1); // Á      LCDPutChar(0xE1); // á      LCDPutChar(0xC2); // Â      LCDPutChar(0xE2); // â
 *   LCDPutChar(0xC3); // Ã      LCDPutChar(0xE3); // ã      LCDPutChar(0xC9); // É      LCDPutChar(0xE9); // é
 *   LCDPutChar(0xCA); // Ê      LCDPutChar(0xEA); // ê      LCDPutChar(0xCD); // Í      LCDPutChar(0xED); // í
 *   LCDPutChar(0xD3); // Ó      LCDPutChar(0xF3); // ó      LCDPutChar(0xD4); // Ô      LCDPutChar(0xF4); // ô
 *   LCDPutChar(0xD5); // Õ      LCDPutChar(0xF5); // õ      LCDPutChar(0xF6); // ö      LCDPutChar(0xC7); // Ç
 *   LCDPutChar(0xE7); // ç      LCDPutChar(0xDA); // Ú      LCDPutChar(0xFA); // ú      LCDPutChar(0xFC); // ü
 *
 * WINSTAR WH1602C English and European standard font (ET) - See Extended ASCII table
 */
