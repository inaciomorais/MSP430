#include <msp430g2553.h>

void main(void)
{
    long count = 0;

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    while(count < 20)
    {
        count = count + 1;
    }

    while(1);
}
