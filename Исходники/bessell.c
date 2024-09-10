    D_TYPE _CALLTYPE1 _j1( D_TYPE x )
#endif
{
D_TYPE	z, P1, Q1;
int	sign;

     /* if the argument is negative, take the absolute value and set sign */

     sign = 1;
     if( x < 0.0 ){
	x = -x;
	sign = -1;
	}

     /* if x <= 7.5  use Hart JONE 6047 */

     if ( x <= 7.5 )
	return( sign*x*evaluate( x*x, J1p, 10, J1q, 4) );


    /* else if x > 7.5	use Hart PONE 6749 and QONE 7149, the high range
       approximation */

    else {
	z = 8.0/x;
	P1 = evaluate( z*z, P1p, 5, P1q, 5);
	Q1 = z*evaluate( z*z, Q1p, 5, Q1q, 5);
	return( sign*sqrtl(2.0/(PI*x))*
			   ( P1*cosl(x-3.0*PI/4.0) - Q1*sinl(x-3.0*PI/4.0) )  );
	}
}