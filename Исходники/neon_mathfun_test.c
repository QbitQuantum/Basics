float cephes_expf(float xx) {
float x, z;
int n;

x = xx;


if( x > MAXLOGF)
	{
    //mtherr( "expf", OVERFLOW );
	return( MAXNUMF );
	}

if( x < MINLOGF )
	{
    //mtherr( "expf", UNDERFLOW );
	return(0.0);
	}

/* Express e**x = e**g 2**n
 *   = e**g e**( n loge(2) )
 *   = e**( g + n loge(2) )
 */
z = floorf( LOG2EF * x + 0.5 ); /* floor() truncates toward -infinity. */

x -= z * C1;
x -= z * C2;
n = z;

z = x * x;
/* Theoretical peak relative error in [-0.5, +0.5] is 4.2e-9. */
z =
((((( 1.9875691500E-4f  * x
   + 1.3981999507E-3f) * x
   + 8.3334519073E-3f) * x
   + 4.1665795894E-2f) * x
   + 1.6666665459E-1f) * x
   + 5.0000001201E-1f) * z
   + x
   + 1.0;

/* multiply by power of 2 */
x = ldexpf( z, n );

return( x );
}