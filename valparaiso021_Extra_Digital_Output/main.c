#include <msp430.h> 

void main(void)
{
    long x = 0;

    WDTCTL = WDTPW | WDTHOLD;   // Stop Watchdog Timer ('DEVELOPMENT')

    P2DIR = BIT5;

    while(1)
    {
        for(x = 0; x < 30000; x++){
            P2OUT = BIT5;
        }
        for(x = 0; x < 30000; x++){
            P2OUT = 0x00;
        }
    }
}
