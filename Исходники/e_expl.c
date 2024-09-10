long double
expl(long double x)
{
long double px, xx;
int n;

if( isnan(x) )
	return(x);
if( x > MAXLOGL)
	return( INFINITY );

if( x < MINLOGL )
	return(0.0L);

/* Express e**x = e**g 2**n
 *   = e**g e**( n loge(2) )
 *   = e**( g + n loge(2) )
 */
px = floorl( LOG2EL * x + 0.5L ); /* floor() truncates toward -infinity. */
n = px;
x -= px * C1;
x -= px * C2;


/* rational approximation for exponential
 * of the fractional part:
 * e**x =  1 + 2x P(x**2)/( Q(x**2) - P(x**2) )
 */
xx = x * x;
px = x * __polevll( xx, P, 2 );
x =  px/( __polevll( xx, Q, 3 ) - px );
x = 1.0L + ldexpl( x, 1 );

x = ldexpl( x, n );
return(x);
}