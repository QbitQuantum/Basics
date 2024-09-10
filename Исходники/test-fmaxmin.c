int
main(int argc, char *argv[])
{

	printf("1..12\n");

	testall(1, 1.0, 0.0);
	testall(2, 42.0, nextafterf(42.0, -INFINITY));
	testall(3, nextafterf(42.0, INFINITY), 42.0);
	testall(4, -5.0, -5.0);
	testall(5, -3.0, -4.0);
	testall(6, 1.0, NAN);
	testall(7, INFINITY, NAN);
	testall(8, INFINITY, 1.0);
	testall(9, -3.0, -INFINITY);
	testall(10, 3.0, -INFINITY);
	testall(11, NAN, NAN);

	/* This test isn't strictly required to work by C99. */
	testall(12, 0.0, -0.0);

	return (0);
}