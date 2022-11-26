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
    unsigned long i = 0;
    unsigned char j;

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    clock_config();
    LCD_Initialize(16);         // 16MHz DCO Frequency

    LCDGoto(0,0);
    LCDPutStr("                ");
    LCDGoto(0,1);
    LCDPutStr("                ");

    while(1)
    {
        while (i < 999999999)
        {
            if (i < 10)
            {
                LCDGoto(15,0);
                j = i;
                LCDPutChar(48 + j);     // Corresponding the integer value to the ASCII table
            }

            else if (i < 100)
            {
                LCDGoto(14,0);
                j = i / 10;
                LCDPutChar(48 + j);
                j = i % 10;
                LCDPutChar(48 + j);
            }

            else if (i < 1000)
            {
                LCDGoto(13,0);
                j = i / 100;
                LCDPutChar(48 + j);
                j = (i / 10) % 10;
                LCDPutChar(48 + j);
                j = i % 10;
                LCDPutChar(48 + j);
            }

            else if (i < 10000)
            {
                LCDGoto(12,0);
                j = i / 1000;
                LCDPutChar(48 + j);
                j = (i / 100) % 10;
                LCDPutChar(48 + j);
                j = (i / 10) % 10;
                LCDPutChar(48 + j);
                j = i % 10;
                LCDPutChar(48 + j);
            }

            else if (i < 100000)
            {
                LCDGoto(11,0);
                j = i / 10000;
                LCDPutChar(48 + j);
                j = (i / 1000) % 10;
                LCDPutChar(48 + j);
                j = (i / 100) % 10;
                LCDPutChar(48 + j);
                j = (i / 10) % 10;
                LCDPutChar(48 + j);
                j = i % 10;
                LCDPutChar(48 + j);
            }

            else if (i < 1000000)
            {
                LCDGoto(10,0);
                j = i / 100000;
                LCDPutChar(48 + j);
                j = (i / 10000) % 10;
                LCDPutChar(48 + j);
                j = (i / 1000) % 10;
                LCDPutChar(48 + j);
                j = (i / 100) % 10;
                LCDPutChar(48 + j);
                j = (i / 10) % 10;
                LCDPutChar(48 + j);
                j = i % 10;
                LCDPutChar(48 + j);
            }

            else if (i < 10000000)
            {
                LCDGoto(9,0);
                j = i / 1000000;
                LCDPutChar(48 + j);
                j = (i / 100000) % 10;
                LCDPutChar(48 + j);
                j = (i / 10000) % 10;
                LCDPutChar(48 + j);
                j = (i / 1000) % 10;
                LCDPutChar(48 + j);
                j = (i / 100) % 10;
                LCDPutChar(48 + j);
                j = (i / 10) % 10;
                LCDPutChar(48 + j);
                j = i % 10;
                LCDPutChar(48 + j);
            }

            else if (i < 100000000)
            {
                LCDGoto(8,0);
                j = i / 10000000;
                LCDPutChar(48 + j);
                j = (i / 1000000) % 10;
                LCDPutChar(48 + j);
                j = (i / 100000) % 10;
                LCDPutChar(48 + j);
                j = (i / 10000) % 10;
                LCDPutChar(48 + j);
                j = (i / 1000) % 10;
                LCDPutChar(48 + j);
                j = (i / 100) % 10;
                LCDPutChar(48 + j);
                j = (i / 10) % 10;
                LCDPutChar(48 + j);
                j = i % 10;
                LCDPutChar(48 + j);
            }

            else
            {
                LCDGoto(7,0);
                j = i / 100000000;
                LCDPutChar(48 + j);
                j = (i / 10000000) % 10;
                LCDPutChar(48 + j);
                j = (i / 1000000) % 10;
                LCDPutChar(48 + j);
                j = (i / 100000) % 10;
                LCDPutChar(48 + j);
                j = (i / 10000) % 10;
                LCDPutChar(48 + j);
                j = (i / 1000) % 10;
                LCDPutChar(48 + j);
                j = (i / 100) % 10;
                LCDPutChar(48 + j);
                j = (i / 10) % 10;
                LCDPutChar(48 + j);
                j = i % 10;
                LCDPutChar(48 + j);
            }

            delay_ms(1, 16);
            i++;
        }
    }
}

void clock_config(void)
{
    BCSCTL1 = CALBC1_16MHZ;      // 16MHz DCO Frequency (Calibrated DCOCTL and
    DCOCTL  = CALDCO_16MHZ;      // BCSCTL1 register settings)
}
