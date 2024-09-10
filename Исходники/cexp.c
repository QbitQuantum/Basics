__complex__ long double cexpl(__complex__ long double z)
{
	__complex__ long double ret;
	long double r_exponent = expl(__real__ z);

	__real__ ret = r_exponent * cosl(__imag__ z);
	__imag__ ret = r_exponent * sinl(__imag__ z);

	return ret;
}