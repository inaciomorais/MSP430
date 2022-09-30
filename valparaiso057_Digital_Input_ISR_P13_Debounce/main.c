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

    P1DIR = BIT0;

    P1OUT = BIT3;
    P1REN = BIT3;   // Pull-up resistor for P1.3 button

    P1IE = BIT3;    /* Port 1 Interrupt Enable */
    P1IES = BIT3;   /* Port 1 Interrupt Edge Select */
                    // For transitions from HI-to-LO

    P1IFG = 0x00;   /* Port 1 Interrupt Flag */
                    // Ensure no ISRs are pending

    _BIS_SR(GIE);

    while(1);
}

#pragma vector=PORT1_VECTOR

__interrupt void Port_1 (void)
{
    unsigned long delay;
    for(delay=0;delay<2000;delay++);

    P1OUT = P1OUT ^ BIT0;

    P1IFG &= ~(BIT3);   // Clear P1.3 interrupt flag
}
