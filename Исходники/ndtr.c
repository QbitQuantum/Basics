double ndtr(double a)
{
double x, y, z;

if (isnan(a)) {
  mtherr("ndtr", DOMAIN);
  return (NAN);
}

x = a * SQRTH;
z = fabs(x);

if( z < SQRTH )
	y = 0.5 + 0.5 * erf(x);

else
	{
	y = 0.5 * erfc(z);

	if( x > 0 )
		y = 1.0 - y;
	}

return(y);
}