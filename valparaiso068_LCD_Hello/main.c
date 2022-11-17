// LCD VCC pin (2) to +5Vcc from Test Pin 1 (TP1) MSP430G2553 Value Line Launchpad

#include <msp430.h>
#include "delay_xs.h"
#include "lcd_display.h"

void clock_config(void);

main()
{
	WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
	
	clock_config();
	LCD_Initialize(16);         // 16MHz DCO Frequency

	LCDGoto(0,0);
	LCDPutStr("                ");

	LCDGoto(0,1);
	LCDPutStr("           HELLO");
}

void clock_config(void)
{
    BCSCTL1 = CALBC1_16MHZ;      // 16MHz DCO Frequency (Calibrated DCOCTL and
    DCOCTL  = CALDCO_16MHZ;      // BCSCTL1 register settings)
}

/* HITACHI HD44780U ROM A02 Pattern (Datasheet page 18)
 *   LCDPutChar(0x9A); // Ω      LCDPutChar(0xAB); // <<
 *   LCDPutChar(0xBB); // >>     LCDPutChar(0xB0); // °
 *   LCDPutChar(0xC0); // À      LCDPutChar(0xE0); // à
 *   LCDPutChar(0xC1); // Á      LCDPutChar(0xE1); // á
 *   LCDPutChar(0xC2); // Â      LCDPutChar(0xE2); // â
 *   LCDPutChar(0xC3); // Ã      LCDPutChar(0xE3); // ã
 *   LCDPutChar(0xC9); // É      LCDPutChar(0xE9); // é
 *   LCDPutChar(0xCA); // Ê      LCDPutChar(0xEA); // ê
 *   LCDPutChar(0xCD); // Í      LCDPutChar(0xED); // í
 *   LCDPutChar(0xD3); // Ó      LCDPutChar(0xF3); // ó
 *   LCDPutChar(0xD4); // Ô      LCDPutChar(0xF4); // ô
 *   LCDPutChar(0xD5); // Õ      LCDPutChar(0xF5); // õ
 *   LCDPutChar(0xF6); // ö      LCDPutChar(0xC7); // Ç
 *   LCDPutChar(0xE7); // ç      LCDPutChar(0xDA); // Ú
 *   LCDPutChar(0xFA); // ú      LCDPutChar(0xFC); // ü
 *
 * WINSTAR WH1602C English and European standard font (ET) - See Extended ASCII table */
