	float acosf(float x)		/* wrapper acosf */
{
#ifdef _IEEE_LIBM
	return __ieee754_acosf(x);
#else
	float z;
	z = __ieee754_acosf(x);
	if(_LIB_VERSION == _IEEE_ || isnan(x)) return z;
	if(fabsf(x)>1.0f) {
	    /* acosf(|x|>1) */
	    errno = EDOM;
	    return nanf("");
	} else
	    return z;
#endif
}