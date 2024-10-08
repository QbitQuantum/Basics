static int
test (const char *locale)
{
  size_t bufsize;
  size_t r;
  size_t l;
  char *buf;
  locale_t loc;
  int result = 0;

  if (setlocale (LC_COLLATE, locale) == NULL)
    {
      printf ("cannot set locale \"%s\"\n", locale);
      return 1;
    }
  bufsize = strxfrm (NULL, string, 0) + 1;
  buf = malloc (bufsize);
  if (buf == NULL)
    {
      printf ("cannot allocate %zd bytes\n", bufsize);
      return 1;
    }
  r = strxfrm (buf, string, bufsize);
  l = strlen (buf);
  if (r != l)
    {
       printf ("locale \"%s\": strxfrm returned %zu, strlen returned %zu\n",
	       locale, r, l);
       result = 1;
    }

  loc = newlocale (1 << LC_ALL, locale, NULL);

  r = strxfrm_l (buf, string, bufsize, loc);
  l = strlen (buf);
  if (r != l)
    {
       printf ("locale \"%s\": strxfrm_l returned %zu, strlen returned %zu\n",
	       locale, r, l);
       result = 1;
    }

  freelocale (loc);

  free (buf);

  return result;
}