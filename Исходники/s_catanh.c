__complex__ double
__catanh (__complex__ double x)
{
  __complex__ double res;
  int rcls = fpclassify (__real__ x);
  int icls = fpclassify (__imag__ x);

  if (__glibc_unlikely (rcls <= FP_INFINITE || icls <= FP_INFINITE))
    {
      if (icls == FP_INFINITE)
	{
	  __real__ res = __copysign (0.0, __real__ x);
	  __imag__ res = __copysign (M_PI_2, __imag__ x);
	}
      else if (rcls == FP_INFINITE || rcls == FP_ZERO)
	{
	  __real__ res = __copysign (0.0, __real__ x);
	  if (icls >= FP_ZERO)
	    __imag__ res = __copysign (M_PI_2, __imag__ x);
	  else
	    __imag__ res = __nan ("");
	}
      else
	{
	  __real__ res = __nan ("");
	  __imag__ res = __nan ("");
	}
    }
  else if (__glibc_unlikely (rcls == FP_ZERO && icls == FP_ZERO))
    {
      res = x;
    }
  else
    {
      if (fabs (__real__ x) >= 16.0 / DBL_EPSILON
	  || fabs (__imag__ x) >= 16.0 / DBL_EPSILON)
	{
	  __imag__ res = __copysign (M_PI_2, __imag__ x);
	  if (fabs (__imag__ x) <= 1.0)
	    __real__ res = 1.0 / __real__ x;
	  else if (fabs (__real__ x) <= 1.0)
	    __real__ res = __real__ x / __imag__ x / __imag__ x;
	  else
	    {
	      double h = __ieee754_hypot (__real__ x / 2.0, __imag__ x / 2.0);
	      __real__ res = __real__ x / h / h / 4.0;
	    }
	}
      else
	{
	  if (fabs (__real__ x) == 1.0
	      && fabs (__imag__ x) < DBL_EPSILON * DBL_EPSILON)
	    __real__ res = (__copysign (0.5, __real__ x)
			    * (M_LN2 - __ieee754_log (fabs (__imag__ x))));
	  else
	    {
	      double i2 = 0.0;
	      if (fabs (__imag__ x) >= DBL_EPSILON * DBL_EPSILON)
		i2 = __imag__ x * __imag__ x;

	      double num = 1.0 + __real__ x;
	      num = i2 + num * num;

	      double den = 1.0 - __real__ x;
	      den = i2 + den * den;

	      double f = num / den;
	      if (f < 0.5)
		__real__ res = 0.25 * __ieee754_log (f);
	      else
		{
		  num = 4.0 * __real__ x;
		  __real__ res = 0.25 * __log1p (num / den);
		}
	    }

	  double absx, absy, den;

	  absx = fabs (__real__ x);
	  absy = fabs (__imag__ x);
	  if (absx < absy)
	    {
	      double t = absx;
	      absx = absy;
	      absy = t;
	    }

	  if (absy < DBL_EPSILON / 2.0)
	    {
	      den = (1.0 - absx) * (1.0 + absx);
	      if (den == -0.0)
		den = 0.0;
	    }
	  else if (absx >= 1.0)
	    den = (1.0 - absx) * (1.0 + absx) - absy * absy;
	  else if (absx >= 0.75 || absy >= 0.5)
	    den = -__x2y2m1 (absx, absy);
	  else
	    den = (1.0 - absx) * (1.0 + absx) - absy * absy;

	  __imag__ res = 0.5 * __ieee754_atan2 (2.0 * __imag__ x, den);
	}

      math_check_force_underflow_complex (res);
    }

  return res;
}