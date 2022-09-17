#include <msp430.h> 

#define _SMCLK  0x0200
#define _UP     0x0010
#define _ID_8   0xC0        // Input divider - /8
#define _DIV_8  0x06        // Divider for SMCLK - /8
//_ID_8 and _DIV_8 = 0.00005818182 s

void init_pins(void);
void setup_timer0(void);
void setup_timer1(void);
unsigned char button_pushed(void);

main()
{
    BCSCTL2 = _DIV_8; //Basic Clock System Control Register 2

    setup_timer0();

    setup_timer1();

    init_pins();

    _BIS_SR(GIE);

    while(1) {
        while(button_pushed()){
            P1OUT = BIT6;
        }

        P1OUT = P1OUT & 0xBF;
    }
}

#pragma vector=TIMER0_A0_VECTOR

__interrupt void Timer0_ISR (void)
{
    P1OUT = P1OUT ^ BIT0;
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
    P1DIR = BIT0 | BIT6;

    P1OUT = BIT3;
    P1REN = BIT3;
}

unsigned char button_pushed(void) {
    return !(BIT3 & P1IN);
}
