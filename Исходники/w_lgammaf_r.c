float
__lgammaf_r(float x, int *signgamp)
{
	float y = __ieee754_lgammaf_r(x,signgamp);
	if(__builtin_expect(!__finitef(y), 0)
	   && __finitef(x) && _LIB_VERSION != _IEEE_)
		return __kernel_standard_f(x, x,
					   __floorf(x)==x&&x<=0.0f
					   ? 115 /* lgamma pole */
					   : 114); /* lgamma overflow */

	return y;
}