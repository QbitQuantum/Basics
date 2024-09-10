static int
do_test (void)
{
  wctype_t wct;
  wchar_t buf[1000];
  int result = 1;

  setlocale (LC_ALL, "");
  wprintf (L"locale = %s\n", setlocale (LC_CTYPE, NULL));

  wct = wctype ("jhira");
  if (wct == 0)
    error (EXIT_FAILURE, 0, "jhira: no such character class");

  if (fgetws (buf, sizeof (buf) / sizeof (buf[0]), stdin) != NULL)
    {
      int n;

      wprintf (L"buf[] = \"%ls\"\n", buf);

      result = 0;

      for (n = 0; buf[n] != L'\0'; ++n)
	{
	  wprintf (L"jhira(U%04lx = %lc) = %d\n", (long) buf[n], buf[n],
		   iswctype (buf[n], wct));
	  result |= ((buf[n] < 0xff && iswctype (buf[n], wct))
		     || (buf[n] > 0xff && !iswctype (buf[n], wct)));
	}
    }

  wct = wctype ("jkata");
  if (wct == 0)
    error (EXIT_FAILURE, 0, "jkata: no such character class");

  if (fgetws (buf, sizeof (buf) / sizeof (buf[0]), stdin) != NULL)
    {
      int n;

      wprintf (L"buf[] = \"%ls\"\n", buf);

      result = 0;

      for (n = 0; buf[n] != L'\0'; ++n)
	{
	  wprintf (L"jkata(U%04lx = %lc) = %d\n", (long) buf[n], buf[n],
		   iswctype (buf[n], wct));
	  result |= ((buf[n] < 0xff && iswctype (buf[n], wct))
		     || (buf[n] > 0xff && !iswctype (buf[n], wct)));
	}
    }

  wct = wctype ("jdigit");
  if (wct == 0)
    error (EXIT_FAILURE, 0, "jdigit: no such character class");

  if (fgetws (buf, sizeof (buf) / sizeof (buf[0]), stdin) != NULL)
    {
      int n;

      wprintf (L"buf[] = \"%ls\"\n", buf);

      result = 0;

      for (n = 0; buf[n] != L'\0'; ++n)
	{
	  wprintf (L"jdigit(U%04lx = %lc) = %d\n", (long) buf[n], buf[n],
		   iswctype (buf[n], wct));
	  result |= ((buf[n] < 0xff && iswctype (buf[n], wct))
		     || (buf[n] > 0xff && !iswctype (buf[n], wct)));
	}
    }

  wct = wctype ("jspace");
  if (wct == 0)
    error (EXIT_FAILURE, 0, "jspace: no such character class");

  if (fgetws (buf, sizeof (buf) / sizeof (buf[0]), stdin) != NULL)
    {
      int n;

      wprintf (L"buf[] = \"%ls\"\n", buf);

      result = 0;

      for (n = 0; buf[n] != L'\0'; ++n)
	{
	  wprintf (L"jspace(U%04lx = %lc) = %d\n", (long) buf[n], buf[n],
		   iswctype (buf[n], wct));
	  result |= ((buf[n] < 0xff && iswctype (buf[n], wct))
		     || (buf[n] > 0xff && !iswctype (buf[n], wct)));
	}
    }

  wct = wctype ("jkanji");
  if (wct == 0)
    error (EXIT_FAILURE, 0, "jkanji: no such character class");

  if (fgetws (buf, sizeof (buf) / sizeof (buf[0]), stdin) != NULL)
    {
      int n;

      wprintf (L"buf[] = \"%ls\"\n", buf);

      result = 0;

      for (n = 0; buf[n] != L'\0'; ++n)
	{
	  wprintf (L"jkanji(U%04lx = %lc) = %d\n", (long) buf[n], buf[n],
		   iswctype (buf[n], wct));
	  result |= ((buf[n] < 0xff && iswctype (buf[n], wct))
		     || (buf[n] > 0xff && !iswctype (buf[n], wct)));
	}
    }

  return result;
}