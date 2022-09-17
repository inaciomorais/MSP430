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
    unsigned char t0_count = 0;
    unsigned char t1_count = 0;

    BCSCTL2 = _DIV_8; //Basic Clock System Control Register 2

    TA0CCR0 = 172;
    TA0CTL  = _SMCLK | _ID_8 | _UP;

    TA1CCR0 = 17187;
    TA1CTL  = _SMCLK | _ID_8 | _UP;

    P1DIR = RED_LED | GREEN_LED;

    while(1)
    {
        if(TA0CTL & _TAIFG) {
            WDTCTL = WDTPW | WDTCNTCL;
            TA0CTL = TA0CTL & (~_TAIFG);
            t0_count++;

            if(t0_count == 10) {
                t0_count = 0;
                P1OUT = P1OUT ^ RED_LED;
            }
        }

        if(TA1CTL & _TAIFG) {
            TA1CTL = TA1CTL & (~_TAIFG);
            t1_count++;

            if(t1_count == 3) {
                t1_count = 0;
                P1OUT = P1OUT ^ GREEN_LED;
            }
        }
    }
}
