long double
__logbl (long double x)
{
  int32_t es, lx, ix;

  GET_LDOUBLE_WORDS (es, ix, lx, x);
  es &= 0x7fff;			/* exponent */
  if ((es | ix | lx) == 0)
    return -1.0 / fabsl (x);
  if (es == 0x7fff)
    return x * x;
  if (es == 0)			/* IEEE 754 logb */
    {
      /* POSIX specifies that denormal number is treated as
         though it were normalized.  */
      if (ix == 0)
	es = -(__builtin_clz (lx) + 32);
      else
	es = -__builtin_clz (ix);
    }
  return (long double) (es - 16383);
}