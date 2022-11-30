#include <msp430.h> 

main()
{
	char a, b, c, d, e;

	a = 2;
	b = 0;
	c = 0;
	d = 0;
	e = 0;

	b = ++a;

	c = a++;

	d = --a;

	e = a--;
	
	while(1);
}
