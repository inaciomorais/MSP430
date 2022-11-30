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

    LCDPutCmd(LCD_CLEAR);

    LCDGoto(0,1);                   // This function positions the cursor at the specified Line and column
    LCDPutStr("MSP430G2553");       // This routine writes string to LCD at current cursor position

    while(1);
}


void clock_config(void)
{
    BCSCTL1 = CALBC1_16MHZ;      // 16MHz DCO Frequency (Calibrated DCOCTL and
    DCOCTL  = CALDCO_16MHZ;      // BCSCTL1 register settings)
}
