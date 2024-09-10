long double
log10l(long double x)
{
long double y;
volatile long double z;
int e;

if( isnan(x) )
	return(x);
/* Test for domain */
if( x <= 0.0L )
	{
	if( x == 0.0L )
		return (-1.0L / (x - x));
	else
		return (x - x) / (x - x);
	}
if( x == INFINITY )
	return(INFINITY);
/* separate mantissa from exponent */

/* Note, frexp is used so that denormal numbers
 * will be handled properly.
 */
x = frexpl( x, &e );


/* logarithm using log(x) = z + z**3 P(z)/Q(z),
 * where z = 2(x-1)/x+1)
 */
if( (e > 2) || (e < -2) )
{
if( x < SQRTH )
	{ /* 2( 2x-1 )/( 2x+1 ) */
	e -= 1;
	z = x - 0.5L;
	y = 0.5L * z + 0.5L;
	}	
else
	{ /*  2 (x-1)/(x+1)   */
	z = x - 0.5L;
	z -= 0.5L;
	y = 0.5L * x  + 0.5L;
	}
x = z / y;
z = x*x;
y = x * ( z * __polevll( z, R, 3 ) / __p1evll( z, S, 3 ) );
goto done;
}


/* logarithm using log(1+x) = x - .5x**2 + x**3 P(x)/Q(x) */

if( x < SQRTH )
	{
	e -= 1;
	x = ldexpl( x, 1 ) - 1.0L; /*  2x - 1  */
	}	
else
	{
	x = x - 1.0L;
	}
z = x*x;
y = x * ( z * __polevll( x, P, 6 ) / __p1evll( x, Q, 7 ) );
y = y - ldexpl( z, -1 );   /* -0.5x^2 + ... */

done:

/* Multiply log of fraction by log10(e)
 * and base 2 exponent by log10(2).
 *
 * ***CAUTION***
 *
 * This sequence of operations is critical and it may
 * be horribly defeated by some compiler optimizers.
 */
z = y * (L10EB);
z += x * (L10EB);
z += e * (L102B);
z += y * (L10EA);
z += x * (L10EA);
z += e * (L102A);

return( z );
}