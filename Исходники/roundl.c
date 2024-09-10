long double
roundl (long double x)
{
  long double res = 0.0L;
  if (x >= 0.0L)
    {
      res = ceill (x);
      if (res - x > 0.5L)
	res -= 1.0L;
    }
  else
    {
      res = ceill (-x);
      if (res + x > 0.5L)
	res -= 1.0L;
      res = -res;
    }
  return res;
}