#include <msp430.h> 

#define RED_LED 0x01        // P1.0 is the RED LED
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

main()
{
    unsigned char interval = 0;

    BCSCTL2 = _DIV_8; //Basic Clock System Control Register 2
    TACCR0 = 172;
    TACTL  = _SMCLK | _ID_8 | _UP;

    P1DIR = RED_LED;

    while(1)
    {
        if(TACTL & _TAIFG) {
            interval++;
            TACTL = TACTL & (~_TAIFG);
            WDTCTL = WDTPW | WDTCNTCL;

            if (interval == 100) {
                interval = 0;
                P1OUT = P1OUT ^ RED_LED; // ~12,5s
            }
        }
    }
}
