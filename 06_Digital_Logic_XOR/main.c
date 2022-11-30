//#include <msp430g2553.h>
#include <msp430.h>

//void main(void)
main()
{
    char a = 0b00000000;
    char b = 0b11111111;

    char c = 0b00000001;
    char d = 0b00000010;

    char e = 0b10000000;
    char f = 0b11110000;


    char s, t, u, v, w, x, y, z;

    s = a ^ c;
    t = b ^ c;

    u = a ^ d;
    v = b ^ d;

    w = a ^ e;
    x = b ^ e;

    y = a ^ f;
    z = b ^ f;

    //WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    while(1);
}

