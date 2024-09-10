static int
do_test (void)
{
  unsigned char buf[7] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
  const unsigned char bufcheck[7] = { 0x25, 0xe2, 0x82, 0xac, 0xce, 0xbb, 0 };
  const wchar_t srcbuf[4] = { 0x25, 0x20ac, 0x03bb, 0 };
  mbstate_t state;
  const wchar_t *src;
  char *dst;
  int result = 0;
  const char *used_locale;

  setlocale (LC_CTYPE, "de_DE.UTF-8");
  /* Double check.  */
  used_locale = setlocale (LC_CTYPE, NULL);
  printf ("used locale: \"%s\"\n", used_locale);
  result = strcmp (used_locale, "de_DE.UTF-8");

  memset (&state, '\0', sizeof (state));

  src = srcbuf;
  dst = (char *) buf;
  show (wcrtomb (dst, *src++, &state), 1, buf + 1);
  show (wcrtomb (dst, *src++, &state), 3, buf + 4);
  show (wcrtomb (dst, *src++, &state), 2, buf + 6);
  show (wcrtomb (dst, *src, &state), 1, buf + 7);

  if (memcmp (buf, bufcheck, 7))
    {
      puts ("wrong results");
      result = 1;
    }

  return result;
}