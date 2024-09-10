long double
__ieee754_exp10l (long double arg)
{
  union ibm_extended_long_double u;
  long double arg_high, arg_low;
  long double exp_high, exp_low;

  if (!__finitel (arg))
    return __ieee754_expl (arg);
  if (arg < LDBL_MIN_10_EXP - LDBL_DIG - 10)
    return LDBL_MIN * LDBL_MIN;
  else if (arg > LDBL_MAX_10_EXP + 1)
    return LDBL_MAX * LDBL_MAX;
  else if (fabsl (arg) < 0x1p-109L)
    return 1.0L;

  u.ld = arg;
  arg_high = u.d[0].d;
  arg_low = u.d[1].d;
  exp_high = arg_high * log10_high;
  exp_low = arg_high * log10_low + arg_low * M_LN10l;
  return __ieee754_expl (exp_high) * __ieee754_expl (exp_low);
}