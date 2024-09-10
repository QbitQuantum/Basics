double
significand(double x)
{
	return __ieee754_scalb(x,(double) -ilogb(x));
}