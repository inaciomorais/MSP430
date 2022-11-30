#include <msp430.h> 

#define RED_LED 0x01        // P1.0 is the RED LED
#define GREEN_LED 0x40        // P1.6 is the GREEN LED
#define GREEN_LED_OFF 0xBF  // Used to turn off the GREEN LED
#define BUTTON13 0x08       // P1.3 is the button

main()
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop Watchdog Timer

    BCSCTL1 = CALBC1_1MHZ;      // 1MHz DCO Frequency (Calibrated DCOCTL and
    DCOCTL = CALDCO_1MHZ;       // BCSCTL1 register settings)
    BCSCTL2 = DIVS_3;           // Basic Clock System Control Register 2
                                // DIVS_3 = SMCLK Divider 3: /8
                                // 1 s / ( 1000000 MHz [DCOCLK] / 8 [BCSCTL2 DIVSx: SMCLK Divider] / 8 [TACTL IDx: Timer A input divider] )
                                // = 0.000064 s = 64 us

    TA0CCR0 = 15625; //~ 1s

    TA0CTL  = (TASSEL_2 + ID_3 + MC_1);    // TASSEL_2: Timer A clock source select: 2 - SMCLK
                                           // ID_3: Timer A input divider: 3 - /8
                                           // MC_1: Timer A mode control: 1 - Up to CCR0
    TA0CCTL0 = CCIE;

    P1DIR = RED_LED | GREEN_LED;

    P1OUT = BUTTON13;
    P1REN = BUTTON13;

    _BIS_SR(GIE);

    while(1) {
        if((BUTTON13 & P1IN) == 0){
            P1OUT = P1OUT | GREEN_LED;
        }
        else {
            P1OUT = P1OUT & GREEN_LED_OFF;
        }
    }
}

#pragma vector=TIMER0_A0_VECTOR

__interrupt void Timer0_ISR (void)
{
    P1OUT = P1OUT ^ RED_LED;
}
