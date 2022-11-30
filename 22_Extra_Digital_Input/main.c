#include <msp430.h> 

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop Watchdog Timer ('DEVELOPMENT')

    P2DIR = BIT5;

    P2REN = BIT4;
    P2OUT = BIT4;

    while(1)
    {
        if((BIT4 & P2IN) == 0) {
            P2OUT = P2OUT | BIT5;
        }
        else {
            P2OUT = BIT4;
        }
    }
}
