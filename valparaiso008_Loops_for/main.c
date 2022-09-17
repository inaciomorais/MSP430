#include <msp430.h> 

#define RED_ON  0x0001
#define RED_OFF 0x0000

main()
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P1DIR = RED_ON;             //P1DIR = P1DIR | 0x01;       // P1.0 is an output
	P1OUT = RED_OFF;

	long x;

	for(x=0; x<30000; x=x+1){
	    P1OUT = P1OUT ^ RED_ON;     //P1OUT = P1OUT ^ 0x01;   // Toggle P1.0
	}

	P1OUT = RED_OFF;

	while(1);
}
