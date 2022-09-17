#include <msp430.h> 

main()
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	signed char count_up    = +120;
	signed char count_down  = -120;

	while(1) {
	    count_up    = count_up      + 1;
	    count_down  = count_down    - 1;
	}
}
