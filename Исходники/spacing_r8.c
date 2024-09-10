GFC_REAL_8
spacing_r8 (GFC_REAL_8 s, int p, int emin, GFC_REAL_8 tiny)
{
  int e;
  if (s == 0.)
    return tiny;
  frexp (s, &e);
  e = e - p;
  e = e > emin ? e : emin;
#if defined (HAVE_LDEXP)
  return ldexp (1., e);
#else
  return scalbn (1., e);
#endif
}