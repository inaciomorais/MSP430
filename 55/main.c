#include <msp430.h> 

main()
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop Watchdog Timer

    BCSCTL1 = CALBC1_1MHZ;      // 1MHz DCO Frequency (Calibrated DCOCTL and
    DCOCTL = CALDCO_1MHZ;       // BCSCTL1 register settings)
    BCSCTL2 = DIVS_3;           // Basic Clock System Control Register 2
                                // DIVS_3 = SMCLK Divider 3: /8
                                // 1 s / ( 1000000 MHz [DCOCLK] / 8 [BCSCTL2 DIVSx: SMCLK Divider] / 8 [TACTL IDx: Timer A input divider] )
                                // = 0.000064 s = 64 us

    P1DIR = BIT0;
    P1OUT = 0x00;

    P1OUT = BIT3;
    P1REN = BIT3;

    TA0CCR0 = 7812;

    TA0CTL  = (TASSEL_2 + ID_3 + MC_1);    // TASSEL_2: Timer A clock source select: 2 - SMCLK
                                           // ID_3: Timer A input divider: 3 - /8
                                           // MC_1: Timer A mode control: 1 - Up to CCR0
    TA0CCTL0 = CCIE;

    _BIS_SR(LPM0_bits | GIE);

    while(1);
}

#pragma vector=TIMER0_A0_VECTOR

__interrupt void Timer0_ISR (void)
{
    if(P1IN & BIT3) {
        P1OUT = P1OUT & ~BIT0;  //  BIT0 = 0000 0001
                                // ~BIT0 = 1111 1110
                                // P1OUT = 0000 100X
                                // Bit-wise AND will clear P1OUT.0 and not change P1.3 pull-up resistor config
    }
    else {
        P1OUT = P1OUT | BIT0;
    }
}
