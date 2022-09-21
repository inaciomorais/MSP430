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

    P1DIR  |=  0x40; // Set P1.6 to output-direction
    P1SEL  |=  0x40; // Set selection register 1 for timer-function
    P1SEL2 &= ~0x40; // Clear selection register 2 for timer-function (not needed, as it is 0 after startup)
                     // 0x40 = BIT6

    TA0CCTL1 = OUTMOD_7;    // PWM output mode: 7 - PWM reset/set

    TA0CCR0 = 19531;        // Period
    TA0CCR1 = 17578;        // Duty-cycle

    TA0CTL  = (TASSEL_2 + ID_3 + MC_1);    // TASSEL_2: Timer A clock source select: 2 - SMCLK
                                           // ID_3: Timer A input divider: 3 - /8
                                           // MC_1: Timer A mode control: 1 - Up to CCR0


    while(1);
}
