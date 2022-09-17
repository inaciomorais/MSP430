//#include <msp430g2553.h>
#include <msp430.h>

//void main(void)
main()
{
    char a = 0b10101101;
    char b = 0b01111111;
    char c = 0b00000000;

    char u, v, w, x, y, z;

    u = ~a;
    v = !a;

    w = ~b;
    x = !b;

    y = ~c;
    z = !c;

    //WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    while(1);
}
