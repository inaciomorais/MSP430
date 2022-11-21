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
#include "delay_xs.h"
#include "lcd_display.h"

void clock_config(void);

main()
{
    WDTCTL = WDTPW | WDTHOLD;     // stop watchdog timer

    clock_config();
    LCD_Initialize(16);           // This routine initializes the LCD driver. 16MHz (DCO Frequency)

    LCDPutCmd(LCD_CGRAM);   // Entering initial CGRAM address
    LCDPutChar(0x00);       // It includes the first CGRAM(1) line      XXX000000
    LCDPutChar(0x0A);       // It includes the second CGRAM(1) line     XXX001010
    LCDPutChar(0x1F);       // It includes the third CGRAM(1) line      XXX011111
    LCDPutChar(0x1F);       // It includes the fourth CGRAM(1) line     XXX011111
    LCDPutChar(0x1F);       // It includes the fifth CGRAM(1) line      XXX011111
    LCDPutChar(0x0E);       // It includes the sixth CGRAM(1) line      XXX001110
    LCDPutChar(0x04);       // It includes the seventh CGRAM(1) line    XXX000100
    LCDPutChar(0x00);       // It includes the seventh CGRAM(1) line    XXX000000 - Always blank (cursor location)
    // Continue the sequence of 8 lines per custom character above to include characters in other CGRAM positions

    // How to call CGRAM characters:
    // LCDPutChar(0x00); // Calling the first  CGRAM character [CGRAM(1)]
    // LCDPutChar(0x01); // Calling the second CGRAM character [CGRAM(2)]
    // [...]
    // LCDPutChar(0x07); // Calling the eighth CGRAM character [CGRAM(8)]

    while(1)
    {
       LCDGoto(2,0);              // This function positions the cursor at the specified Line and column   
       LCDPutChar(0x00);          
       delay_ms(500, 16);         // 500ms, 16MHz (DCO Frequency)

       LCDGoto(2,0);
       LCDPutStr(" ");            // This routine writes string to LCD at current cursor position
       delay_ms(400, 16);
    }
}

void clock_config(void)
{
    BCSCTL1 = CALBC1_16MHZ;      // 16MHz DCO Frequency (Calibrated DCOCTL and
    DCOCTL  = CALDCO_16MHZ;      // BCSCTL1 register settings)
}
