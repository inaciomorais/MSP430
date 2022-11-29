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
#include <string.h>
#include "lcd_display.h"

void clock_config(void);
void scrollwords(char words[250], char line, unsigned int ms, char MHz);

main()
{
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer

    clock_config();
    LCD_Initialize(16);             // This routine initializes the LCD driver. 16MHz (DCO Frequency)

    LCDPutCmd(LCD_CLEAR);

    while(1)
    {
        scrollwords("This message moves...", 0, 300, 16);   // (string, line, delay_ms, clock)
    }
}


void clock_config(void)
{
    BCSCTL1 = CALBC1_16MHZ;      // 16MHz DCO Frequency (Calibrated DCOCTL and
    DCOCTL  = CALDCO_16MHZ;      // BCSCTL1 register settings)
}

void scrollwords(char words[250], char line, unsigned int ms, char MHz)
{
    unsigned int length = strlen(words);
    unsigned int _shifted = 0;

    if (length < 17)   // 16 + '/0'
    {
        LCDGoto(0,line);
        LCDPutStr(words);
        delay_ms(1000, MHz);
    }
    else
    {
        while (_shifted < (length - 15))
        {
            LCDGoto(0,line);
            LCDPutChar(words[_shifted]);       //0
            LCDPutChar(words[_shifted + 1]);   //1
            LCDPutChar(words[_shifted + 2]);   //2
            LCDPutChar(words[_shifted + 3]);   //3
            LCDPutChar(words[_shifted + 4]);   //4
            LCDPutChar(words[_shifted + 5]);   //5
            LCDPutChar(words[_shifted + 6]);   //6
            LCDPutChar(words[_shifted + 7]);   //7
            LCDPutChar(words[_shifted + 8]);   //8
            LCDPutChar(words[_shifted + 9]);   //9
            LCDPutChar(words[_shifted + 10]);  //10
            LCDPutChar(words[_shifted + 11]);  //11
            LCDPutChar(words[_shifted + 12]);  //12
            LCDPutChar(words[_shifted + 13]);  //13
            LCDPutChar(words[_shifted + 14]);  //14
            LCDPutChar(words[_shifted + 15]);  //15

            if(_shifted == 0) delay_ms(2000, MHz);  // first delay
            else if (_shifted == (length - 16)) delay_ms(1000, MHz); // last delay
            else delay_ms(ms, MHz);

            _shifted++;
        }
    }
}
