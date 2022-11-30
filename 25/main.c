#include <msp430.h> 

//#define GREEN_LED_ON 0x40        // P1.6 is the GREEN LED
//#define GREEN_LED_OFF 0xBF  // Used to turn off the GREEN LED
#define RED_LED_ON 0x01        // P1.0 is the RED LED
#define RED_LED_OFF 0xFE  // Used to turn off the RED LED
#define BUTTON13 0x08       // P1.3 is the button

void main(void)
{
    long x = 0;

    WDTCTL = WDTPW | WDTHOLD;   // Stop Watchdog Timer ('DEVELOPMENT')

    P1DIR = RED_LED_ON;

    P1OUT = BUTTON13 | RED_LED_ON;
    P1REN = BUTTON13;

    while(x < 200000)
    {
        if((BUTTON13 & P1IN) == 0){
            continue;
        }

        x = x + 1;
    }

    P1OUT = BUTTON13;
    while(1);
}
