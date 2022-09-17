#include <msp430.h> 

signed int cubed(signed char);

main()
{
    signed char q = 6;

    signed int answer = 0;

    WDTCTL = WDTPW | WDTHOLD;

    answer = cubed(q);

    while(1);
}

signed int cubed (signed char abc) {
    return abc * abc * abc;
}
