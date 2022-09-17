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
    WDTCTL = WDTPW | WDTHOLD;   // Stop Watchdog Timer
    BCSCTL2 = _DIV_8; //Basic Clock System Control Register 2

    TA0CCR0 = 8594; //valparaiso 20000
    TA0CTL  = _SMCLK | _ID_8 | _UP;
    TA0CCTL0 = CCIE;

    P1DIR = RED_LED;

    _BIS_SR(GIE);

    while(1);
}

#pragma vector=TIMER0_A0_VECTOR

__interrupt void Timer0_ISR (void)
{
    static unsigned char x = 0;
    x++;

    if(x == 15) {
        P1OUT = P1OUT ^ RED_LED;
        x = 0;
    }
}
