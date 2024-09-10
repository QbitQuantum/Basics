/* Check the multibyte character s[0..n-1].  */
static void
check_character (const char *s, size_t n)
{
  wchar_t wc;
  char buf[64];
  int iret;
  size_t ret;

  wc = (wchar_t) 0xBADFACE;
  iret = mbtowc (&wc, s, n);
  ASSERT (iret == n);

  ret = wcrtomb (buf, wc, NULL);
  ASSERT (ret == n);
  ASSERT (memcmp (buf, s, n) == 0);

  /* Test special calling convention, passing a NULL pointer.  */
  ret = wcrtomb (NULL, wc, NULL);
  ASSERT (ret == 1);
}