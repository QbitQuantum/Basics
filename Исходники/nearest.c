_f_real16
_NEAREST_16(_f_real16 a, _f_real16 s)
{
	_f_real16	d;
	_f_real16	result;
	if ( a == 0 || s == 0 ) {
		if ( s < 0 ) {
			result	= -_SPACING_16(a);
		} else {
			result	= _SPACING_16(a);
		}
	} else {
		if (a < 0) {
			d	= a * (-2);
		} else {
			d	= a * 2;
		}
		if (s < 0)
			d	= -d;
		/* use nextafterl routine in libc prototyped in math.h */
		result	= nextafterl(a,d);
	}
	return result;
}