float
__ieee754_gammaf_r (float x, int *signgamp)
{
  int32_t hx;
  float ret;

  GET_FLOAT_WORD (hx, x);

  if (__glibc_unlikely ((hx & 0x7fffffff) == 0))
    {
      /* Return value for x == 0 is Inf with divide by zero exception.  */
      *signgamp = 0;
      return 1.0 / x;
    }
  if (__builtin_expect (hx < 0, 0)
      && (u_int32_t) hx < 0xff800000 && __rintf (x) == x)
    {
      /* Return value for integer x < 0 is NaN with invalid exception.  */
      *signgamp = 0;
      return (x - x) / (x - x);
    }
  if (__glibc_unlikely (hx == 0xff800000))
    {
      /* x == -Inf.  According to ISO this is NaN.  */
      *signgamp = 0;
      return x - x;
    }
  if (__glibc_unlikely ((hx & 0x7f800000) == 0x7f800000))
    {
      /* Positive infinity (return positive infinity) or NaN (return
	 NaN).  */
      *signgamp = 0;
      return x + x;
    }

  if (x >= 36.0f)
    {
      /* Overflow.  */
      *signgamp = 0;
      ret = math_narrow_eval (FLT_MAX * FLT_MAX);
      return ret;
    }
  else
    {
      SET_RESTORE_ROUNDF (FE_TONEAREST);
      if (x > 0.0f)
	{
	  *signgamp = 0;
	  int exp2_adj;
	  float tret = gammaf_positive (x, &exp2_adj);
	  ret = __scalbnf (tret, exp2_adj);
	}
      else if (x >= -FLT_EPSILON / 4.0f)
	{
	  *signgamp = 0;
	  ret = 1.0f / x;
	}
      else
	{
	  float tx = __truncf (x);
	  *signgamp = (tx == 2.0f * __truncf (tx / 2.0f)) ? -1 : 1;
	  if (x <= -42.0f)
	    /* Underflow.  */
	    ret = FLT_MIN * FLT_MIN;
	  else
	    {
	      float frac = tx - x;
	      if (frac > 0.5f)
		frac = 1.0f - frac;
	      float sinpix = (frac <= 0.25f
			      ? __sinf ((float) M_PI * frac)
			      : __cosf ((float) M_PI * (0.5f - frac)));
	      int exp2_adj;
	      float tret = (float) M_PI / (-x * sinpix
					   * gammaf_positive (-x, &exp2_adj));
	      ret = __scalbnf (tret, -exp2_adj);
	      math_check_force_underflow_nonneg (ret);
	    }
	}
      ret = math_narrow_eval (ret);
    }
  if (isinf (ret) && x != 0)
    {
      if (*signgamp < 0)
	{
	  ret = math_narrow_eval (-__copysignf (FLT_MAX, ret) * FLT_MAX);
	  ret = -ret;
	}
      else
	ret = math_narrow_eval (__copysignf (FLT_MAX, ret) * FLT_MAX);
      return ret;
    }
  else if (ret == 0)
    {
      if (*signgamp < 0)
	{
	  ret = math_narrow_eval (-__copysignf (FLT_MIN, ret) * FLT_MIN);
	  ret = -ret;
	}
      else
	ret = math_narrow_eval (__copysignf (FLT_MIN, ret) * FLT_MIN);
      return ret;
    }
  else
    return ret;
}