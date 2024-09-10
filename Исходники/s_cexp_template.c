CFLOAT
M_DECL_FUNC (__cexp) (CFLOAT x)
{
  CFLOAT retval;
  int rcls = fpclassify (__real__ x);
  int icls = fpclassify (__imag__ x);

  if (__glibc_likely (rcls >= FP_ZERO))
    {
      /* Real part is finite.  */
      if (__glibc_likely (icls >= FP_ZERO))
	{
	  /* Imaginary part is finite.  */
	  const int t = (int) ((M_MAX_EXP - 1) * M_MLIT (M_LN2));
	  FLOAT sinix, cosix;

	  if (__glibc_likely (M_FABS (__imag__ x) > M_MIN))
	    {
	      M_SINCOS (__imag__ x, &sinix, &cosix);
	    }
	  else
	    {
	      sinix = __imag__ x;
	      cosix = 1;
	    }

	  if (__real__ x > t)
	    {
	      FLOAT exp_t = M_EXP (t);
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
	      __real__ retval = M_MAX * cosix;
	      __imag__ retval = M_MAX * sinix;
	    }
	  else
	    {
	      FLOAT exp_val = M_EXP (__real__ x);
	      __real__ retval = exp_val * cosix;
	      __imag__ retval = exp_val * sinix;
	    }
	  math_check_force_underflow_complex (retval);
	}
      else
	{
	  /* If the imaginary part is +-inf or NaN and the real part
	     is not +-inf the result is NaN + iNaN.  */
	  __real__ retval = M_NAN;
	  __imag__ retval = M_NAN;

	  feraiseexcept (FE_INVALID);
	}
    }
  else if (__glibc_likely (rcls == FP_INFINITE))
    {
      /* Real part is infinite.  */
      if (__glibc_likely (icls >= FP_ZERO))
	{
	  /* Imaginary part is finite.  */
	  FLOAT value = signbit (__real__ x) ? 0 : M_HUGE_VAL;

	  if (icls == FP_ZERO)
	    {
	      /* Imaginary part is 0.0.  */
	      __real__ retval = value;
	      __imag__ retval = __imag__ x;
	    }
	  else
	    {
	      FLOAT sinix, cosix;

	      if (__glibc_likely (M_FABS (__imag__ x) > M_MIN))
		{
		  M_SINCOS (__imag__ x, &sinix, &cosix);
		}
	      else
		{
		  sinix = __imag__ x;
		  cosix = 1;
		}

	      __real__ retval = M_COPYSIGN (value, cosix);
	      __imag__ retval = M_COPYSIGN (value, sinix);
	    }
	}
      else if (signbit (__real__ x) == 0)
	{
	  __real__ retval = M_HUGE_VAL;
	  __imag__ retval = __imag__ x - __imag__ x;
	}
      else
	{
	  __real__ retval = 0;
	  __imag__ retval = M_COPYSIGN (0, __imag__ x);
	}
    }
  else
    {
      /* If the real part is NaN the result is NaN + iNaN unless the
	 imaginary part is zero.  */
      __real__ retval = M_NAN;
      if (icls == FP_ZERO)
	__imag__ retval = __imag__ x;
      else
	{
	  __imag__ retval = M_NAN;

	  if (rcls != FP_NAN || icls != FP_NAN)
	    feraiseexcept (FE_INVALID);
	}
    }

  return retval;
}