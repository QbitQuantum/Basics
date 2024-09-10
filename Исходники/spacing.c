/*
 *  Return a real with the same type parameter as X whose value is the
 *  absolute spacing of the model number near X, that is, b**(e-p).
 */
_f_real16
_SPACING_16(_f_real16 a)
{
	_f_int4		e;
	_f_real16	f;
	if (a == 0) {
		e = -916;
	} else {
		(void) _get_frac_and_exp(a,&e);
	}
	e	= e - DBL_DBL_MANT_BITS;

	/* Unfortunately, (in Fortran) -1021 is too small.  The
	 * constant -916 is hard-wired to maintain full precision.
	 */
	if (e < -916)
		e	= -916;
	/* use ldexpl routine in libc prototyped in math.h */
	f	= ldexpl(1.0L,e);
	return(f);
}