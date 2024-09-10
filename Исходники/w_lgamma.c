double
__lgamma(double x)
{
	int local_signgam = 0;
	double y = __ieee754_lgamma_r(x,
				      _LIB_VERSION != _ISOC_
				      /* ISO C99 does not define the
					 global variable.  */
				      ? &signgam
				      : &local_signgam);
	if(__builtin_expect(!__finite(y), 0)
	   && __finite(x) && _LIB_VERSION != _IEEE_)
		return __kernel_standard(x, x,
					 __floor(x)==x&&x<=0.0
					 ? 15 /* lgamma pole */
					 : 14); /* lgamma overflow */

	return y;
}