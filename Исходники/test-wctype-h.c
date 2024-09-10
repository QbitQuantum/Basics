int
main (void)
{
  /* Check that the isw* functions exist as functions or as macros.  */
  (void) iswalnum (0);
  (void) iswalpha (0);
  (void) iswcntrl (0);
  (void) iswdigit (0);
  (void) iswgraph (0);
  (void) iswlower (0);
  (void) iswprint (0);
  (void) iswpunct (0);
  (void) iswspace (0);
  (void) iswupper (0);
  (void) iswxdigit (0);

  /* Check that the isw* functions map WEOF to 0.  */
  ASSERT (!iswalnum (e));
  ASSERT (!iswalpha (e));
  ASSERT (!iswcntrl (e));
  ASSERT (!iswdigit (e));
  ASSERT (!iswgraph (e));
  ASSERT (!iswlower (e));
  ASSERT (!iswprint (e));
  ASSERT (!iswpunct (e));
  ASSERT (!iswspace (e));
  ASSERT (!iswupper (e));
  ASSERT (!iswxdigit (e));

  /* Check that the tow* functions exist as functions or as macros.  */
  (void) towlower (0);
  (void) towupper (0);

  /* Check that the tow* functions map WEOF to WEOF.  */
  ASSERT (towlower (e) == e);
  ASSERT (towupper (e) == e);

  return 0;
}