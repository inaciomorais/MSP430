#include <msp430.h> 

#define _SMCLK  0x0200
#define _UP     0x0010
#define _ID_8   0xC0        // Input divider - /8
#define _DIV_8  0x06        // Divider for SMCLK - /8
//_ID_8 and _DIV_8 = 0.00005818182 s

main()
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop Watchdog Timer
    BCSCTL2 = _DIV_8; //Basic Clock System Control Register 2

    P1DIR = BIT0;
    P1OUT = 0x00;

    TA0CTL  = _SMCLK | _ID_8 | _UP;

    TA0CCR0 = 21484;
    TA0CCTL0 = CCIE;

    TA0CCR1 = 19336;
    TA0CCTL1 = CCIE;

    _BIS_SR(GIE);

    while(1);
}

#pragma vector=TIMER0_A1_VECTOR

__interrupt void Timer0_CCR1_MATCH(void)
{
    if(TA0IV == 2) {
        P1OUT = BIT0;
    }
}

#pragma vector=TIMER0_A0_VECTOR

__interrupt void Timer0_CCR0_MATCH(void)
{
    P1OUT = 0x00;
}
