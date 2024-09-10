static int
do_test (const char *loc)
{
  char buf[100];
  size_t n;
  mbstate_t state;
  const char *nloc;
  int res;

  nloc = setlocale (LC_ALL, loc);
  if (nloc == NULL)
    {
      printf ("could not set locale \"%s\"\n", loc);
      return 1;
    }
  printf ("new locale: %s\n", nloc);

  memset (&state, '\0', sizeof (state));
  errno = 0;
  n = wcrtomb (buf, (wchar_t) -15l, &state);

  printf ("n = %zd, errno = %d (%s)\n", n, errno, strerror (errno));

  res = n != (size_t) -1 || errno != EILSEQ;
  if (res)
    puts ("*** FAIL");
  putchar ('\n');

  return res;
}