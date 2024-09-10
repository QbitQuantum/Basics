__complex__ double
__clog10 (__complex__ double x)
{
  __complex__ double result;
  int rcls = fpclassify (__real__ x);
  int icls = fpclassify (__imag__ x);

  if (__builtin_expect (rcls == FP_ZERO && icls == FP_ZERO, 0))
    {
      /* Real and imaginary part are 0.0.  */
      __imag__ result = signbit (__real__ x) ? M_PI : 0.0;
      __imag__ result = __copysign (__imag__ result, __imag__ x);
      /* Yes, the following line raises an exception.  */
      __real__ result = -1.0 / fabs (__real__ x);
    }
  else if (__builtin_expect (rcls != FP_NAN && icls != FP_NAN, 1))
    {
      /* Neither real nor imaginary part is NaN.  */
      double absx = fabs (__real__ x), absy = fabs (__imag__ x);
      int scale = 0;

      if (absx < absy)
	{
	  double t = absx;
	  absx = absy;
	  absy = t;
	}

      if (absx > DBL_MAX / 2.0)
	{
	  scale = -1;
	  absx = __scalbn (absx, scale);
	  absy = (absy >= DBL_MIN * 2.0 ? __scalbn (absy, scale) : 0.0);
	}
      else if (absx < DBL_MIN && absy < DBL_MIN)
	{
	  scale = DBL_MANT_DIG;
	  absx = __scalbn (absx, scale);
	  absy = __scalbn (absy, scale);
	}

      if (absx == 1.0 && scale == 0)
	{
	  double absy2 = absy * absy;
	  if (absy2 <= DBL_MIN * 2.0 * M_LN10)
	    {
#if __FLT_EVAL_METHOD__ == 0
	      __real__ result = (absy2 / 2.0 - absy2 * absy2 / 4.0) * M_LOG10E;
#else
	      volatile double force_underflow = absy2 * absy2 / 4.0;
	      __real__ result = (absy2 / 2.0 - force_underflow) * M_LOG10E;
#endif
	    }
	  else
	    __real__ result = __log1p (absy2) * (M_LOG10E / 2.0);
	}
      else if (absx > 1.0 && absx < 2.0 && absy < 1.0 && scale == 0)
	{
	  double d2m1 = (absx - 1.0) * (absx + 1.0);
	  if (absy >= DBL_EPSILON)
	    d2m1 += absy * absy;
	  __real__ result = __log1p (d2m1) * (M_LOG10E / 2.0);
	}
      else if (absx < 1.0
	       && absx >= 0.75
	       && absy < DBL_EPSILON / 2.0
	       && scale == 0)
	{
	  double d2m1 = (absx - 1.0) * (absx + 1.0);
	  __real__ result = __log1p (d2m1) * (M_LOG10E / 2.0);
	}
      else if (absx < 1.0 && (absx >= 0.75 || absy >= 0.5) && scale == 0)
	{
	  double d2m1 = __x2y2m1 (absx, absy);
	  __real__ result = __log1p (d2m1) * (M_LOG10E / 2.0);
	}
      else
	{
	  double d = __ieee754_hypot (absx, absy);
	  __real__ result = __ieee754_log10 (d) - scale * M_LOG10_2;
	}

      __imag__ result = M_LOG10E * __ieee754_atan2 (__imag__ x, __real__ x);
    }
  else
    {
      __imag__ result = __nan ("");
      if (rcls == FP_INFINITE || icls == FP_INFINITE)
	/* Real or imaginary part is infinite.  */
	__real__ result = HUGE_VAL;
      else
	__real__ result = __nan ("");
    }

  return result;
}