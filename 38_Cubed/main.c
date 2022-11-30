#include <msp430.h> 

signed int cubed(signed char);

main()
{
	signed int answer = 0;

    WDTCTL = WDTPW | WDTHOLD;

	answer = cubed(6);
	
	while(1);
}

signed int cubed (signed char x) {
    signed int result = 0;

    result = x * x *x;

    return result;
}
