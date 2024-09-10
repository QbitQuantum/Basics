GFC_INTEGER_4
exponent_r16 (GFC_REAL_16 s)
{
  int ret;
  frexpl (s, &ret);
  return ret;
}