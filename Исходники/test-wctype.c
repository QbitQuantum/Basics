int
main ()
{
  /* Check that the isw* functions exist as functions or as macros.  */
  iswalnum (0);
  iswalpha (0);
#if 0 /* not portable: missing on mingw */
  iswblank (0);
#endif
  iswcntrl (0);
  iswdigit (0);
  iswgraph (0);
  iswlower (0);
  iswprint (0);
  iswpunct (0);
  iswspace (0);
  iswupper (0);
  iswxdigit (0);

  return 0;
}