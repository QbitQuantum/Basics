GFC_REAL_10
spacing_r10 (GFC_REAL_10 s, int p, int emin, GFC_REAL_10 tiny)
{
  int e;
  if (s == 0.)
    return tiny;
  frexpl (s, &e);
  e = e - p;
  e = e > emin ? e : emin;
#if defined (HAVE_LDEXPL)
  return ldexpl (1., e);
#else
  return scalbnl (1., e);
#endif
}