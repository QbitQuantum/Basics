long double
log1pl(long double xm1)
{
  long double x, y, z, r, s;
  ieee_quad_shape_type u;
  int32_t hx;
  int e;

  /* Test for NaN or infinity input. */
  u.value = xm1;
  hx = u.parts32.mswhi;
  if (hx >= 0x7fff0000)
    return xm1;

  /* log1p(+- 0) = +- 0.  */
  if (((hx & 0x7fffffff) == 0)
      && (u.parts32.mswlo | u.parts32.lswhi | u.parts32.lswlo) == 0)
    return xm1;

  x = xm1 + 1.0L;

  /* log1p(-1) = -inf */
  if (x <= 0.0L)
    {
      if (x == 0.0L)
	return (-1.0L / (x - x));
      else
	return (zero / (x - x));
    }

  /* Separate mantissa from exponent.  */

  /* Use frexp used so that denormal numbers will be handled properly.  */
  x = frexpl (x, &e);

  /* Logarithm using log(x) = z + z^3 P(z^2)/Q(z^2),
     where z = 2(x-1)/x+1).  */
  if ((e > 2) || (e < -2))
    {
      if (x < sqrth)
	{			/* 2( 2x-1 )/( 2x+1 ) */
	  e -= 1;
	  z = x - 0.5L;
	  y = 0.5L * z + 0.5L;
	}
      else
	{			/*  2 (x-1)/(x+1)   */
	  z = x - 0.5L;
	  z -= 0.5L;
	  y = 0.5L * x + 0.5L;
	}
      x = z / y;
      z = x * x;
      r = ((((R5 * z
	      + R4) * z
	     + R3) * z
	    + R2) * z
	   + R1) * z
	+ R0;
      s = (((((z
	       + S5) * z
	      + S4) * z
	     + S3) * z
	    + S2) * z
	   + S1) * z
	+ S0;
      z = x * (z * r / s);
      z = z + e * C2;
      z = z + x;
      z = z + e * C1;
      return (z);
    }


  /* Logarithm using log(1+x) = x - .5x^2 + x^3 P(x)/Q(x). */

  if (x < sqrth)
    {
      e -= 1;
      if (e != 0)
	x = 2.0L * x - 1.0L;	/*  2x - 1  */
      else
	x = xm1;
    }
  else
    {
      if (e != 0)
	x = x - 1.0L;
      else
	x = xm1;
    }
  z = x * x;
  r = (((((((((((P12 * x
		 + P11) * x
		+ P10) * x
	       + P9) * x
	      + P8) * x
	     + P7) * x
	    + P6) * x
	   + P5) * x
	  + P4) * x
	 + P3) * x
	+ P2) * x
       + P1) * x
    + P0;
  s = (((((((((((x
		 + Q11) * x
		+ Q10) * x
	       + Q9) * x
	      + Q8) * x
	     + Q7) * x
	    + Q6) * x
	   + Q5) * x
	  + Q4) * x
	 + Q3) * x
	+ Q2) * x
       + Q1) * x
    + Q0;
  y = x * (z * r / s);
  y = y + e * C2;
  z = y - 0.5L * z;
  z = z + x;
  z = z + e * C1;
  return (z);
}