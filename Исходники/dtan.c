/*
 * DTAN: TAN of real(kind=16) - pass by address
 * 128-bit float tangent
 */
_f_real16
_DTAN_( _f_real16 *x )
{
	_f_real16 tanl(_f_real16 x);
	return ( (_f_real16) tanl((_f_real16) *x));
}