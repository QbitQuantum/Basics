float
LGFUNC (__lgammaf) (float x)
{
	float y = CALL_LGAMMA (float, __ieee754_lgammaf_r, x);
	if(__builtin_expect(!isfinite(y), 0)
	   && isfinite(x) && _LIB_VERSION != _IEEE_)
		return __kernel_standard_f(x, x,
					   __floorf(x)==x&&x<=0.0f
					   ? 115 /* lgamma pole */
					   : 114); /* lgamma overflow */

	return y;
}