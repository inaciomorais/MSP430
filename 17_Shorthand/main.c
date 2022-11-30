#include <msp430.h> 

main()
{
    int a = 0x9D;
    int b = 10;

    int t = 0xAA;
    int u = 0xAA;
    int v = 0xAA;

    int w = 20;
    int x = 20;
    int y = 20;
    int z = 20;

    t &= a;
    u |= a;
    v ^= a;
    w += b;
    x -= b;
    y *= b;
    z /= b;

    while(1);
}
