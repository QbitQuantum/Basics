int
main ()
{
	int i;
	for (i = 0; i < 256; i++)
		if (XOR (islower (i), ISLOWER (i)) || toupper (i) != TOUPPER (i))
			exit(1);
	exit (0);
}