float
significandf(float x)
{
	return __ieee754_scalbf(x,(float) -ilogbf(x));
}