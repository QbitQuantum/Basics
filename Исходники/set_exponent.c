/* use ldexpl routine in libc prototyped in math.h */
_f_real16
_SET_EXPONENT_16(_f_real16 a, _f_int4 i)
{
	_f_int4		dummy;
	_f_real16	aa;
	if (a == 0.0) {
		aa	= 0.0;
	} else {
		aa	= ldexpl(_get_frac_and_exp(a,&dummy),i);
	}
	return (aa);
}  