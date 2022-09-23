#include <msp430.h> 

main()
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop Watchdog Timer

    BCSCTL1 = CALBC1_1MHZ;      // 1MHz DCO Frequency (Calibrated DCOCTL and
    DCOCTL = CALDCO_1MHZ;       // BCSCTL1 register settings)
    BCSCTL2 = DIVS_3;           // Basic Clock System Control Register 2
                                // DIVS_3 = SMCLK Divider 3: /8
                                // 1 s / ( 1000000 MHz [DCOCLK] / 8 [BCSCTL2 DIVSx: SMCLK Divider] / 8 [TACTL IDx: Timer A input divider] )
                                // = 0,000064 s = 64 us

    TA0CCR0 = 7812; //valparaiso 20000

    TA0CTL  = (TASSEL_2 + ID_3 + MC_1);    // TASSEL_2: Timer A clock source select: 2 - SMCLK
                                           // ID_3: Timer A input divider: 3 - /8
                                           // MC_1: Timer A mode control: 1 - Up to CCR0
    TA0CCTL0 = CCIE;

    P1DIR = BIT0 | BIT6;

    _BIS_SR(LPM0_bits | GIE);

    P1OUT = BIT6;

    while(1);
}

#pragma vector=TIMER0_A0_VECTOR

__interrupt void Timer0_ISR (void)
{
    P1OUT = P1OUT ^ BIT0;
}

