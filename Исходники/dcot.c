/*
 * DCOT  - real(kind=16) - pass by value
 * 128-bit float cotangent
 */
_f_real16
_DCOT( _f_real16 x )
{
	return ( ((_f_real16) 1.0) / tanl(x) );
}