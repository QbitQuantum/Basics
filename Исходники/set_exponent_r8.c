GFC_REAL_8
set_exponent_r8 (GFC_REAL_8 s, GFC_INTEGER_4 i)
{
  int dummy_exp;
  return scalbn (frexp (s, &dummy_exp), i);
}