//#include <msp430g2553.h>
#include <msp430.h>

//void main(void)
main()
{
    char a = 0b10101101;
    char b = 0b11110000;

    char c = 0b01111111;
    char d = 0b10000000;

    char e = 0b10101101;
    char f = 0b00000000;

    char g = 0b00000000;
    char h = 0b00000000;

    char u, v, w, x, y, z, s, t;

    //u = a & b;
    //v = a && b;
    u = a | b;
    v = a || b;

    //w = c & d;
    //x = c && d;
    w = c | d;
    x = c || d;

    //y = e & f;
    //z = e && f;
    y = e | f;
    z = e || f;

    s = g | h;
    t = g || h;

    //WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    while(1);
}

