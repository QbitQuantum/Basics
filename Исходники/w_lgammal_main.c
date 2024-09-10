long double
LGFUNC (__lgammal) (long double x)
{
	long double y = CALL_LGAMMA (long double, __ieee754_lgammal_r, x);
	if(__builtin_expect(!isfinite(y), 0)
	   && isfinite(x) && _LIB_VERSION != _IEEE_)
		return __kernel_standard_l(x, x,
					   floorl(x)==x&&x<=0.0L
					   ? 215 /* lgamma pole */
					   : 214); /* lgamma overflow */

	return y;
}