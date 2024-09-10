int
main (void)
{
  unsigned char buf[6] = { 0x25,  0xe2, 0x82, 0xac,  0xce, 0xbb };
  mbstate_t state;
  const char *src;
  wchar_t wc = 42;
  size_t n;
  int result = 0;
  const char *used_locale;

  setlocale (LC_CTYPE,"de_DE.UTF-8");
  /* Double check.  */
  used_locale = setlocale (LC_CTYPE, NULL);
  printf ("used locale: \"%s\"\n", used_locale);
  result = strcmp (used_locale, "de_DE.UTF-8");

  memset (&state, '\0', sizeof (state));

  src = (const char *) buf;
  show (mbsrtowcs (&wc, &src, 1, &state), 1, 37, buf + 1);
  show (mbsrtowcs (&wc, &src, 1, &state), 1, 8364, buf + 4);
  show (mbsrtowcs (&wc, &src, 1, &state), 1, 955, buf + 6);

  return result;
}