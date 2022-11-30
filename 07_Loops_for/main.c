#include <msp430.h> 

main()
{
	int x, y;

	y = 0;

	for (x = 0; x < 10; x = x +1){
	    y = y + x;
	}
	
	while(1);
}
