double
__ieee754_atanh (double x)
{
  double xa = fabs (x);
  double t;
  if (isless (xa, 0.5))
    {
      if (__builtin_expect (xa < 0x1.0p-28, 0))
	{
	  math_force_eval (huge + x);
	  return x;
	}

      t = xa + xa;
      t = 0.5 * __log1p (t + t * xa / (1.0 - xa));
    }
  else if (__builtin_expect (isless (xa, 1.0), 1))
    t = 0.5 * __log1p ((xa + xa) / (1.0 - xa));
  else
    {
      if (isgreater (xa, 1.0))
	return (x - x) / (x - x);

      return x / 0.0;
    }

  return __copysign (t, x);
}