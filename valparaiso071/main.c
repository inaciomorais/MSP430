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
void adc_setup(void);

main()
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop Watchdog Timer

    adc_setup();
    clock_config();

    LCD_Initialize(16);         // 16MHz DCO Frequency

    LCDPutCmd(LCD_CGRAM); // Entering initial CGRAM address
    LCDPutChar(0x3F);   // It includes the first CGRAM(1) line      XXX111111
    LCDPutChar(0x3F);   // It includes the second CGRAM(1) line     XXX111111
    LCDPutChar(0x3F);   // It includes the third CGRAM(1) line      XXX111111
    LCDPutChar(0x3F);   // It includes the fourth CGRAM(1) line     XXX111111
    LCDPutChar(0x3F);   // It includes the fifth CGRAM(1) line      XXX111111
    LCDPutChar(0x3F);   // It includes the sixth CGRAM(1) line      XXX111111
    LCDPutChar(0x3F);   // It includes the seventh CGRAM(1) line    XXX111111
    LCDPutChar(0x00);   // It includes the seventh CGRAM(1) line    XXX000000 - Always blank (cursor location)
    // Continue the sequence of 8 lines per custom character above to include characters in other CGRAM positions

    // How to call CGRAM characters:
    // LCDPutChar(0x00); // Calling the first  CGRAM character [CGRAM(1)]
    // LCDPutChar(0x01); // Calling the second CGRAM character [CGRAM(2)]
    // [...]
    // LCDPutChar(0x07); // Calling the eighth CGRAM character [CGRAM(8)]

    LCDPutCmd(LCD_CLEAR);

    ADC10CTL0 |= ADC10IE;

    _BIS_SR(GIE);

    ADC10CTL0 |= ENC + ADC10SC;     /* ENC - ADC10 Enable Conversion */
                                    /* ADC10SC - ADC10 Start Conversion */
                                    // ADC10SC and ENC may be set together with one instruction

    while(1);
}

void adc_setup(void)
{
    ADC10CTL0 = ADC10SHT_2 | ADC10ON;    /*SREF_0 - VR+ = AVCC and VR- = AVSS */
                                         /* ADC10SHT_2 - 16 x ADC10CLKs */
                                         /* ADC10ON - ADC10 On/Enable */

    ADC10CTL1 = INCH_4;     /* INCH_4 - Selects Channel 4 (A4)*/
                                    //These bits select the channel for a single-conversion or the highest channel for a sequence of conversions
                            /* SHS_0 - ADC10SC */
                            /* ADC10SSEL_0 - ADC10OSC */
                            /* CONSEQ_0 - Single channel single conversion */
    ADC10AE0 = BIT4;        // Analog input enable (A4)
                                    //These bits enable the corresponding pin for analog input
}

void clock_config(void)
{
    BCSCTL1 = CALBC1_16MHZ;      // 16MHz DCO Frequency (Calibrated DCOCTL and
    DCOCTL  = CALDCO_16MHZ;      // BCSCTL1 register settings)
}

#pragma vector = ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
    LCDGoto(0,0);

    if (ADC10MEM > 0x048) // 1
    {
        LCDPutStr("[");
        LCDPutChar(0x00);
    }
    else
    {
        LCDPutStr("[ ");
    }

    if (ADC10MEM > 0x090) // 2
    {
        LCDPutChar(0x00);
    }
    else
    {
        LCDPutStr(" ");
    }

    if (ADC10MEM > 0x0D8) // 3
    {
        LCDPutChar(0x00);
    }
    else
    {
        LCDPutStr(" ");
    }

    if (ADC10MEM > 0x120) // 4
    {
        LCDPutChar(0x00);
    }
    else
    {
        LCDPutStr(" ");
    }

    if (ADC10MEM > 0x168) // 5
    {
        LCDPutChar(0x00);
    }
    else
    {
        LCDPutStr(" ");
    }

    if (ADC10MEM > 0x1B0) // 6
    {
        LCDPutChar(0x00);
    }
    else
    {
        LCDPutStr(" ");
    }

    if (ADC10MEM > 0x1F8) // 7
    {
        LCDPutChar(0x00);
    }
    else
    {
        LCDPutStr(" ");
    }

    if (ADC10MEM > 0x240) // 8
    {
        LCDPutChar(0x00);
    }
    else
    {
        LCDPutStr(" ");
    }

    if (ADC10MEM > 0x288) // 9
    {
        LCDPutChar(0x00);
    }
    else
    {
        LCDPutStr(" ");
    }

    if (ADC10MEM > 0x2D0) // 10
    {
        LCDPutChar(0x00);
    }
    else
    {
        LCDPutStr(" ");
    }

    if (ADC10MEM > 0x318) // 11
    {
        LCDPutChar(0x00);
    }
    else
    {
        LCDPutStr(" ");
    }

    if (ADC10MEM > 0x360) // 12
    {
        LCDPutChar(0x00);
    }
    else
    {
        LCDPutStr(" ");
    }

    if (ADC10MEM > 0x3A8) // 13
    {
        LCDPutChar(0x00);
    }
    else
    {
        LCDPutStr(" ");
    }

    if (ADC10MEM > 0x3F0) // 14
    {
        LCDPutChar(0x00);
        LCDPutStr("]");
    }
    else
    {
        LCDPutStr(" ]");
    }

    ADC10CTL0 |= ENC + ADC10SC;
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
