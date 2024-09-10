__complex__ float
__csqrtf (__complex__ float x)
{
  __complex__ float res;
  int rcls = fpclassify (__real__ x);
  int icls = fpclassify (__imag__ x);

  if (__glibc_unlikely (rcls <= FP_INFINITE || icls <= FP_INFINITE))
    {
      if (icls == FP_INFINITE)
	{
	  __real__ res = HUGE_VALF;
	  __imag__ res = __imag__ x;
	}
      else if (rcls == FP_INFINITE)
	{
	  if (__real__ x < 0.0)
	    {
	      __real__ res = icls == FP_NAN ? __nanf ("") : 0;
	      __imag__ res = __copysignf (HUGE_VALF, __imag__ x);
	    }
	  else
	    {
	      __real__ res = __real__ x;
	      __imag__ res = (icls == FP_NAN
			      ? __nanf ("") : __copysignf (0.0, __imag__ x));
	    }
	}
      else
	{
	  __real__ res = __nanf ("");
	  __imag__ res = __nanf ("");
	}
    }
  else
    {
      if (__glibc_unlikely (icls == FP_ZERO))
	{
	  if (__real__ x < 0.0)
	    {
	      __real__ res = 0.0;
	      __imag__ res = __copysignf (__ieee754_sqrtf (-__real__ x),
					  __imag__ x);
	    }
	  else
	    {
	      __real__ res = fabsf (__ieee754_sqrtf (__real__ x));
	      __imag__ res = __copysignf (0.0, __imag__ x);
	    }
	}
      else if (__glibc_unlikely (rcls == FP_ZERO))
	{
	  float r;
	  if (fabsf (__imag__ x) >= 2.0f * FLT_MIN)
	    r = __ieee754_sqrtf (0.5f * fabsf (__imag__ x));
	  else
	    r = 0.5f * __ieee754_sqrtf (2.0f * fabsf (__imag__ x));

	  __real__ res = r;
	  __imag__ res = __copysignf (r, __imag__ x);
	}
      else
	{
	  float d, r, s;
	  int scale = 0;

	  if (fabsf (__real__ x) > FLT_MAX / 4.0f)
	    {
	      scale = 1;
	      __real__ x = __scalbnf (__real__ x, -2 * scale);
	      __imag__ x = __scalbnf (__imag__ x, -2 * scale);
	    }
	  else if (fabsf (__imag__ x) > FLT_MAX / 4.0f)
	    {
	      scale = 1;
	      if (fabsf (__real__ x) >= 4.0f * FLT_MIN)
		__real__ x = __scalbnf (__real__ x, -2 * scale);
	      else
		__real__ x = 0.0f;
	      __imag__ x = __scalbnf (__imag__ x, -2 * scale);
	    }
	  else if (fabsf (__real__ x) < FLT_MIN
		   && fabsf (__imag__ x) < FLT_MIN)
	    {
	      scale = -(FLT_MANT_DIG / 2);
	      __real__ x = __scalbnf (__real__ x, -2 * scale);
	      __imag__ x = __scalbnf (__imag__ x, -2 * scale);
	    }

	  d = __ieee754_hypotf (__real__ x, __imag__ x);
	  /* Use the identity   2  Re res  Im res = Im x
	     to avoid cancellation error in  d +/- Re x.  */
	  if (__real__ x > 0)
	    {
	      r = __ieee754_sqrtf (0.5f * (d + __real__ x));
	      if (scale == 1 && fabsf (__imag__ x) < 1.0f)
		{
		  /* Avoid possible intermediate underflow.  */
		  s = __imag__ x / r;
		  r = __scalbnf (r, scale);
		  scale = 0;
		}
	      else
		s = 0.5f * (__imag__ x / r);
	    }
	  else
	    {
	      s = __ieee754_sqrtf (0.5f * (d - __real__ x));
	      if (scale == 1 && fabsf (__imag__ x) < 1.0f)
		{
		  /* Avoid possible intermediate underflow.  */
		  r = fabsf (__imag__ x / s);
		  s = __scalbnf (s, scale);
		  scale = 0;
		}
	      else
		r = fabsf (0.5f * (__imag__ x / s));
	    }

	  if (scale)
	    {
	      r = __scalbnf (r, scale);
	      s = __scalbnf (s, scale);
	    }

	  __real__ res = r;
	  __imag__ res = __copysignf (s, __imag__ x);
	}
    }

  return res;
}