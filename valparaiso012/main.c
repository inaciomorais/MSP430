#include <msp430.h> 

main()
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	unsigned char count = 250;

	while(1) {
	    count = count + 1;
	}
}
