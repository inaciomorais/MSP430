#include <msp430.h> 

#define RED_LED 0x01        // P1.0 is the RED LED
#define GREEN_LED 0x40        // P1.6 is the GREEN LED

void main(void)
{
    unsigned char t0_count = 0;
    unsigned char t1_count = 0;

    BCSCTL1 = CALBC1_1MHZ;      // 1MHz DCO Frequency (Calibrated DCOCTL and
    DCOCTL = CALDCO_1MHZ;       // BCSCTL1 register settings)
    BCSCTL2 = DIVS_3;           // Basic Clock System Control Register 2
                                // DIVS_3 = SMCLK Divider 3: /8
                                // 1 s / ( 1000000 MHz [DCOCLK] / 8 [BCSCTL2 DIVSx: SMCLK Divider] / 8 [TACTL IDx: Timer A input divider] )
                                // = 0.000064 s = 64 us

    TA0CCR0 = 156;
    TA0CTL  = (TASSEL_2 + ID_3 + MC_1);    // TASSEL_2: Timer A clock source select: 2 - SMCLK
                                           // ID_3: Timer A input divider: 3 - /8
                                           // MC_1: Timer A mode control: 1 - Up to CCR0

    TA1CCR0 = 15625;
    TA1CTL  = (TASSEL_2 + ID_3 + MC_1);    // TASSEL_2: Timer A clock source select: 2 - SMCLK
                                           // ID_3: Timer A input divider: 3 - /8
                                           // MC_1: Timer A mode control: 1 - Up to CCR0

    P1DIR = RED_LED | GREEN_LED;

    while(1)
    {
        if(TA0CTL & TAIFG) {
            WDTCTL = WDTPW | WDTCNTCL;
            TA0CTL = TA0CTL & (~TAIFG);
            t0_count++;

            if(t0_count == 10) {
                t0_count = 0;
                P1OUT = P1OUT ^ RED_LED;
            }
        }

        if(TA1CTL & TAIFG) {
            TA1CTL = TA1CTL & (~TAIFG);
            t1_count++;

            if(t1_count == 3) {
                t1_count = 0;
                P1OUT = P1OUT ^ GREEN_LED;
            }
        }
    }
}
