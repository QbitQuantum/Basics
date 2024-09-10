long double logbl(long double x)
{
	int i = ilogbl(x);

	if (i == FP_ILOGB0)
		return -1.0/fabsl(x);
	if (i == FP_ILOGBNAN || i == INT_MAX)
		return x * x;
	return i;
}