__complex__ float
__cexpf (__complex__ float x)
{
  __complex__ float retval;
  int rcls = fpclassify (__real__ x);
  int icls = fpclassify (__imag__ x);

  if (__glibc_likely (rcls >= FP_ZERO))
    {
      /* Real part is finite.  */
      if (__glibc_likely (icls >= FP_ZERO))
	{
	  /* Imaginary part is finite.  */
	  const int t = (int) ((FLT_MAX_EXP - 1) * M_LN2);
	  float sinix, cosix;

	  if (__glibc_likely (icls != FP_SUBNORMAL))
	    {
	      __sincosf (__imag__ x, &sinix, &cosix);
	    }
	  else
	    {
	      sinix = __imag__ x;
	      cosix = 1.0f;
	    }

	  if (__real__ x > t)
	    {
	      float exp_t = __ieee754_expf (t);
	      __real__ x -= t;
	      sinix *= exp_t;
	      cosix *= exp_t;
	      if (__real__ x > t)
		{
		  __real__ x -= t;
		  sinix *= exp_t;
		  cosix *= exp_t;
		}
	    }
	  if (__real__ x > t)
	    {
	      /* Overflow (original real part of x > 3t).  */
	      __real__ retval = FLT_MAX * cosix;
	      __imag__ retval = FLT_MAX * sinix;
	    }
	  else
	    {
	      float exp_val = __ieee754_expf (__real__ x);
	      __real__ retval = exp_val * cosix;
	      __imag__ retval = exp_val * sinix;
	    }
	  if (fabsf (__real__ retval) < FLT_MIN)
	    {
	      volatile float force_underflow
		= __real__ retval * __real__ retval;
	      (void) force_underflow;
	    }
	  if (fabsf (__imag__ retval) < FLT_MIN)
	    {
	      volatile float force_underflow
		= __imag__ retval * __imag__ retval;
	      (void) force_underflow;
	    }
	}
      else
	{
	  /* If the imaginary part is +-inf or NaN and the real part
	     is not +-inf the result is NaN + iNaN.  */
	  __real__ retval = __nanf ("");
	  __imag__ retval = __nanf ("");

	  feraiseexcept (FE_INVALID);
	}
    }
  else if (__glibc_likely (rcls == FP_INFINITE))
    {
      /* Real part is infinite.  */
      if (__glibc_likely (icls >= FP_ZERO))
	{
	  /* Imaginary part is finite.  */
	  float value = signbit (__real__ x) ? 0.0 : HUGE_VALF;

	  if (icls == FP_ZERO)
	    {
	      /* Imaginary part is 0.0.  */
	      __real__ retval = value;
	      __imag__ retval = __imag__ x;
	    }
	  else
	    {
	      float sinix, cosix;

	      if (__glibc_likely (icls != FP_SUBNORMAL))
		{
		  __sincosf (__imag__ x, &sinix, &cosix);
		}
	      else
		{
		  sinix = __imag__ x;
		  cosix = 1.0f;
		}

	      __real__ retval = __copysignf (value, cosix);
	      __imag__ retval = __copysignf (value, sinix);
	    }
	}
      else if (signbit (__real__ x) == 0)
	{
	  __real__ retval = HUGE_VALF;
	  __imag__ retval = __nanf ("");

	  if (icls == FP_INFINITE)
	    feraiseexcept (FE_INVALID);
	}
      else
	{
	  __real__ retval = 0.0;
	  __imag__ retval = __copysignf (0.0, __imag__ x);
	}
    }
  else
    {
      /* If the real part is NaN the result is NaN + iNaN unless the
	 imaginary part is zero.  */
      __real__ retval = __nanf ("");
      if (icls == FP_ZERO)
	__imag__ retval = __imag__ x;
      else
	{
	  __imag__ retval = __nanf ("");

	  if (rcls != FP_NAN || icls != FP_NAN)
	    feraiseexcept (FE_INVALID);
	}
    }

  return retval;
}