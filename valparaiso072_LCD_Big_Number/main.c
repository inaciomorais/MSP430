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
    long i = -1050;
    long j;
    unsigned char k;

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    clock_config();
    LCD_Initialize(16);         // 16MHz DCO Frequency

    LCDPutCmd(LCD_CLEAR);

    while(1)
    {
        if (i < 0)
        {
            j = -i;
        }
        else
        {
            j = i;
        }

        if (j < 10)
        {
            LCDPutCmd(LCD_CLEAR);
            LCDGoto(15,0);
            k = j;
            LCDPutChar(48 + k);     // Corresponding the integer value to the ASCII table

            LCDGoto(13,0);
            if (i < 0)
            {
                LCDPutStr(" -");
            }
            else
            {
                LCDPutStr("  ");
            }
        }

        else if (j < 100)
        {
            LCDGoto(14,0);
            k = j / 10;
            LCDPutChar(48 + k);
            k = j % 10;
            LCDPutChar(48 + k);

            LCDGoto(12,0);
            if (i < 0)
            {
                LCDPutStr(" -");
            }
            else
            {
                LCDPutStr("  ");
            }
        }

        else if (j < 1000)
        {
            LCDGoto(13,0);
            k = j / 100;
            LCDPutChar(48 + k);
            k = (j / 10) % 10;
            LCDPutChar(48 + k);
            k = j % 10;
            LCDPutChar(48 + k);

            LCDGoto(11,0);
            if (i < 0)
            {
                LCDPutStr(" -");
            }
            else
            {
                LCDPutStr("  ");
            }
        }

        else if (j < 10000)
        {
            LCDGoto(12,0);
            k = j / 1000;
            LCDPutChar(48 + k);
            k = (j / 100) % 10;
            LCDPutChar(48 + k);
            k = (j / 10) % 10;
            LCDPutChar(48 + k);
            k = j % 10;
            LCDPutChar(48 + k);

            LCDGoto(10,0);
            if (i < 0)
            {
                LCDPutStr(" -");
            }
            else
            {
                LCDPutStr("  ");
            }
        }

        else if (j < 100000)
        {
            LCDGoto(11,0);
            k = j / 10000;
            LCDPutChar(48 + k);
            k = (j / 1000) % 10;
            LCDPutChar(48 + k);
            k = (j / 100) % 10;
            LCDPutChar(48 + k);
            k = (j / 10) % 10;
            LCDPutChar(48 + k);
            k = j % 10;
            LCDPutChar(48 + k);

            LCDGoto(9,0);
            if (i < 0)
            {
                LCDPutStr(" -");
            }
            else
            {
                LCDPutStr("  ");
            }
        }

        else if (j < 1000000)
        {
            LCDGoto(10,0);
            k = j / 100000;
            LCDPutChar(48 + k);
            k = (j / 10000) % 10;
            LCDPutChar(48 + k);
            k = (j / 1000) % 10;
            LCDPutChar(48 + k);
            k = (j / 100) % 10;
            LCDPutChar(48 + k);
            k = (j / 10) % 10;
            LCDPutChar(48 + k);
            k = j % 10;
            LCDPutChar(48 + k);

            LCDGoto(8,0);
            if (i < 0)
            {
                LCDPutStr(" -");
            }
            else
            {
                LCDPutStr("  ");
            }
        }

        else if (j < 10000000)
        {
            LCDGoto(9,0);
            k = j / 1000000;
            LCDPutChar(48 + k);
            k = (j / 100000) % 10;
            LCDPutChar(48 + k);
            k = (j / 10000) % 10;
            LCDPutChar(48 + k);
            k = (j / 1000) % 10;
            LCDPutChar(48 + k);
            k = (j / 100) % 10;
            LCDPutChar(48 + k);
            k = (j / 10) % 10;
            LCDPutChar(48 + k);
            k = j % 10;
            LCDPutChar(48 + k);

            LCDGoto(7,0);
            if (i < 0)
            {
                LCDPutStr(" -");
            }
            else
            {
                LCDPutStr("  ");
            }
        }

        else if (j < 100000000)
        {
            LCDGoto(8,0);
            k = j / 10000000;
            LCDPutChar(48 + k);
            k = (j / 1000000) % 10;
            LCDPutChar(48 + k);
            k = (j / 100000) % 10;
            LCDPutChar(48 + k);
            k = (j / 10000) % 10;
            LCDPutChar(48 + k);
            k = (j / 1000) % 10;
            LCDPutChar(48 + k);
            k = (j / 100) % 10;
            LCDPutChar(48 + k);
            k = (j / 10) % 10;
            LCDPutChar(48 + k);
            k = j % 10;
            LCDPutChar(48 + k);

            LCDGoto(6,0);
            if (i < 0)
            {
                LCDPutStr(" -");
            }
            else
            {
                LCDPutStr("  ");
            }
        }

        else if (j < 1000000000)
        {
            LCDGoto(7,0);
            k = j / 100000000;
            LCDPutChar(48 + k);
            k = (j / 10000000) % 10;
            LCDPutChar(48 + k);
            k = (j / 1000000) % 10;
            LCDPutChar(48 + k);
            k = (j / 100000) % 10;
            LCDPutChar(48 + k);
            k = (j / 10000) % 10;
            LCDPutChar(48 + k);
            k = (j / 1000) % 10;
            LCDPutChar(48 + k);
            k = (j / 100) % 10;
            LCDPutChar(48 + k);
            k = (j / 10) % 10;
            LCDPutChar(48 + k);
            k = j % 10;
            LCDPutChar(48 + k);

            LCDGoto(5,0);
            if (i < 0)
            {
                LCDPutStr(" -");
            }
            else
            {
                LCDPutStr("  ");
            }
        }

        else
        {
            LCDGoto(6,0);
            k = j / 1000000000;
            LCDPutChar(48 + k);
            k = (j / 100000000) % 10;
            LCDPutChar(48 + k);
            k = (j / 10000000) % 10;
            LCDPutChar(48 + k);
            k = (j / 1000000) % 10;
            LCDPutChar(48 + k);
            k = (j / 100000) % 10;
            LCDPutChar(48 + k);
            k = (j / 10000) % 10;
            LCDPutChar(48 + k);
            k = (j / 1000) % 10;
            LCDPutChar(48 + k);
            k = (j / 100) % 10;
            LCDPutChar(48 + k);
            k = (j / 10) % 10;
            LCDPutChar(48 + k);
            k = j % 10;
            LCDPutChar(48 + k);

            LCDGoto(4,0);
            if (i < 0)
            {
                LCDPutStr(" -");
            }
            else
            {
                LCDPutStr("  ");
            }
        }

        delay_ms(50, 16);
        i++;
    }
}

void clock_config(void)
{
    BCSCTL1 = CALBC1_16MHZ;      // 16MHz DCO Frequency (Calibrated DCOCTL and
    DCOCTL  = CALDCO_16MHZ;      // BCSCTL1 register settings)
}
