GFC_REAL_10
set_exponent_r10 (GFC_REAL_10 s, GFC_INTEGER_4 i)
{
  int dummy_exp;
  return scalbnl (frexpl (s, &dummy_exp), i);
}