GFC_REAL_8
rrspacing_r8 (GFC_REAL_8 s, int p)
{
  int e;
  GFC_REAL_8 x;
  x = fabs (s);
  if (x == 0.)
    return 0.;
  frexp (s, &e);
#if defined (HAVE_LDEXP)
  return ldexp (x, p - e);
#else
  return scalbn (x, p - e);
#endif

}