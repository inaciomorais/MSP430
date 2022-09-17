#include <msp430.h> 

#define RED_LED 0x01        // P1.0 is the RED LED
#define GREEN_LED 0x40        // P1.6 is the GREEN LED
#define _SMCLK  0x0200
#define _UP     0x0010
#define _TAIFG  0x0001
//#define _ID_2   0x40        // Input divider - /2
//#define _ID_4   0x80        // Input divider - /4
#define _ID_8   0xC0        // Input divider - /8
//#define _DIV_2  0x02        // Divider for SMCLK - /2
//#define _DIV_4  0x04        // Divider for SMCLK - /4
#define _DIV_8  0x06        // Divider for SMCLK - /8
//_ID_8 and _DIV_8 = 0.00005818182 s

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop Watchdog Timer
    BCSCTL2 = _DIV_8; //Basic Clock System Control Register 2

    TA0CCR0 = 14180;
    TA0CTL  = _SMCLK | _ID_8 | _UP;

    TA1CCR0 = 2148;
    TA1CTL  = _SMCLK | _ID_8 | _UP;

    P1DIR = RED_LED | GREEN_LED;

    while(1)
    {
        if(TA0CTL & _TAIFG) {
            P1OUT = P1OUT ^ RED_LED;
            TA0CTL = TA0CTL & (~_TAIFG);
        }

        if(TA1CTL & _TAIFG) {
            P1OUT = P1OUT ^ GREEN_LED;
            TA1CTL = TA1CTL & (~_TAIFG);
        }
    }
}
