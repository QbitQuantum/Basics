long long
llroundl (long double x)
{
  long double res;

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
  if (!isfinite (res)
      || res > (double) LONG_LONG_MAX
      || res < (double) LONG_LONG_MIN)
    {
      errno = ERANGE;
      /* Undefined behaviour, so we could return anything.  */
      /* return res > 0.0 ? LONG_LONG_MAX : LONG_LONG_MIN;  */
    }
  return (long long) res;
}