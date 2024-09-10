long double
__lgammal_r(long double x, int *signgamp)
{
	long double y = __ieee754_lgammal_r(x,signgamp);
	if(__builtin_expect(!isfinite(y), 0)
	   && isfinite(x) && _LIB_VERSION != _IEEE_)
		return __kernel_standard(x, x,
					 floorl(x)==x&&x<=0.0
					 ? 215 /* lgamma pole */
					 : 214); /* lgamma overflow */

	return y;
}