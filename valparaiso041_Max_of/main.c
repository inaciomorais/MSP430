signed int max_of (signed int, signed int);

main()
{
	signed int a, b, first, second, output;

	a = 5;
	b = -2;

	first = -4;
	second = 13219;

	output = max_of(first, second);
	
	while(1);
}

signed int max_of(signed int a, signed int b) {
    if (a > b) {
        return a;
    }

    return b;
}
