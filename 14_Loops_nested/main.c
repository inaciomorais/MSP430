#include <msp430.h> 

main()
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	int ones = 0;
	int tens = 0;
	int km = 0;

	for (tens=0; tens<10; tens++) {
	    for (ones=0; ones<10; ones++) {
	        km = 10*tens + ones;
	    }
	}

	while(1);
}
