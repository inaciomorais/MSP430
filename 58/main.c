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

    P1DIR = BIT0 | BIT6;

    P1OUT = BIT3 | BIT4;
    P1REN = BIT3 | BIT4;    // Pull-up resistors for buttons (P1.4 Extra Digital Input - External button)

    P1IE = BIT3 | BIT4;    /* Port 1 Interrupt Enable */
    P1IES = BIT3 | BIT4;   /* Port 1 Interrupt Edge Select */
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
    unsigned char _BIT3, _BIT4;

    for(delay=0;delay<10000;delay++);

    _BIT3 = BIT3 & P1IN;
    _BIT4 = BIT4 & P1IN;

    if (_BIT3 == 0) {
        P1OUT = P1OUT ^ BIT0;
        P1IFG &= ~(BIT3);   // Clear P1.3 interrupt flag
    }

    if (_BIT4 == 0) {
        P1OUT = P1OUT ^ BIT6;
        P1IFG &= ~(BIT4);   // Clear P1.4 interrupt flag
    }
}
