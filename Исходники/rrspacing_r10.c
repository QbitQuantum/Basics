GFC_REAL_10
rrspacing_r10 (GFC_REAL_10 s, int p)
{
  int e;
  GFC_REAL_10 x;
  x = fabsl (s);
  if (x == 0.)
    return 0.;
  frexpl (s, &e);
#if defined (HAVE_LDEXPL)
  return ldexpl (x, p - e);
#else
  return scalbnl (x, p - e);
#endif

}