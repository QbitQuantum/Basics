int
ilogb(double x)
{
	if (x == 0)
		return FP_ILOGB0;
	if (x != x)
		return FP_ILOGBNAN;
	if (!finite(x))
		return INT_MAX;
	return (int)logb(x);
}