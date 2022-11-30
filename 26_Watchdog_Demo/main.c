#include <msp430.h> 

#define RED_LED_ON 0x01        // P1.0 is the RED LED

void main(void)
{
    //WDTCTL = WDTPW | WDTHOLD;   // Stop Watchdog Timer

    P1DIR = RED_LED_ON;
    P1OUT = RED_LED_ON;

    while(1)
    {

    }

}

