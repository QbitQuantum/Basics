__complex__ double
__ctanh (__complex__ double x)
{
  __complex__ double res;

  if (__glibc_unlikely (!isfinite (__real__ x) || !isfinite (__imag__ x)))
    {
      if (isinf (__real__ x))
	{
	  __real__ res = __copysign (1.0, __real__ x);
	  if (isfinite (__imag__ x) && fabs (__imag__ x) > 1.0)
	    {
	      double sinix, cosix;
	      __sincos (__imag__ x, &sinix, &cosix);
	      __imag__ res = __copysign (0.0, sinix * cosix);
	    }
	  else
	    __imag__ res = __copysign (0.0, __imag__ x);
	}
      else if (__imag__ x == 0.0)
	{
	  res = x;
	}
      else
	{
	  __real__ res = __nan ("");
	  __imag__ res = __nan ("");

	  if (isinf (__imag__ x))
	    feraiseexcept (FE_INVALID);
	}
    }
  else
    {
      double sinix, cosix;
      double den;
      const int t = (int) ((DBL_MAX_EXP - 1) * M_LN2 / 2);

      /* tanh(x+iy) = (sinh(2x) + i*sin(2y))/(cosh(2x) + cos(2y))
	 = (sinh(x)*cosh(x) + i*sin(y)*cos(y))/(sinh(x)^2 + cos(y)^2).  */

      if (__glibc_likely (fabs (__imag__ x) > DBL_MIN))
	{
	  __sincos (__imag__ x, &sinix, &cosix);
	}
      else
	{
	  sinix = __imag__ x;
	  cosix = 1.0;
	}

      if (fabs (__real__ x) > t)
	{
	  /* Avoid intermediate overflow when the imaginary part of
	     the result may be subnormal.  Ignoring negligible terms,
	     the real part is +/- 1, the imaginary part is
	     sin(y)*cos(y)/sinh(x)^2 = 4*sin(y)*cos(y)/exp(2x).  */
	  double exp_2t = __ieee754_exp (2 * t);

	  __real__ res = __copysign (1.0, __real__ x);
	  __imag__ res = 4 * sinix * cosix;
	  __real__ x = fabs (__real__ x);
	  __real__ x -= t;
	  __imag__ res /= exp_2t;
	  if (__real__ x > t)
	    {
	      /* Underflow (original real part of x has absolute value
		 > 2t).  */
	      __imag__ res /= exp_2t;
	    }
	  else
	    __imag__ res /= __ieee754_exp (2 * __real__ x);
	}
      else
	{
	  double sinhrx, coshrx;
	  if (fabs (__real__ x) > DBL_MIN)
	    {
	      sinhrx = __ieee754_sinh (__real__ x);
	      coshrx = __ieee754_cosh (__real__ x);
	    }
	  else
	    {
	      sinhrx = __real__ x;
	      coshrx = 1.0;
	    }

	  if (fabs (sinhrx) > fabs (cosix) * DBL_EPSILON)
	    den = sinhrx * sinhrx + cosix * cosix;
	  else
	    den = cosix * cosix;
	  __real__ res = sinhrx * coshrx / den;
	  __imag__ res = sinix * cosix / den;
	}
      math_check_force_underflow_complex (res);
    }

  return res;
}