#include <msp430.h> 

#define RED_LED 0x01        // P1.0 is the RED LED
#define GREEN_LED 0x40        // P1.6 is the GREEN LED
#define GREEN_LED_OFF 0xBF  // Used to turn off the GREEN LED
#define BUTTON13 0x08       // P1.3 is the button
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

void init_pins(void);
void setup_timer0(void);
void setup_timer1(void);

main()
{
    BCSCTL2 = _DIV_8; //Basic Clock System Control Register 2

    setup_timer0();

    setup_timer1();

    init_pins();

    _BIS_SR(GIE);

    while(1) {
        while((BUTTON13 & P1IN) == 0){
            P1OUT = P1OUT | GREEN_LED;
        }

        P1OUT = P1OUT & GREEN_LED_OFF;
    }
}

#pragma vector=TIMER0_A0_VECTOR

__interrupt void Timer0_ISR (void)
{
    P1OUT = P1OUT ^ RED_LED;
}

#pragma vector=TIMER1_A0_VECTOR

__interrupt void Timer1_ISR (void)
{
    WDTCTL = WDTPW | WDTCNTCL;
}

void setup_timer0(void) {
    TA0CCR0 = 17187; //~ 1s
    TA0CTL  = _SMCLK | _ID_8 | _UP;
    TA0CCTL0 = CCIE;
}

void setup_timer1(void) {
    TA1CCR0 = 172; //~ 0,01s
    TA1CTL  = _SMCLK | _ID_8 | _UP;
    TA1CCTL0 = CCIE;
}

void init_pins(void) {
    P1DIR = RED_LED | GREEN_LED;

    P1OUT = BUTTON13;
    P1REN = BUTTON13;
}

