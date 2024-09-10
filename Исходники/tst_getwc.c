int
main (void)
{
  wchar_t buf[100];
  size_t n = 0;

  wmemset (buf, L'\0', sizeof (buf) / sizeof (buf[0]));
  while (! feof (stdin) && n < sizeof (buf) - 1)
    {
      buf[n] = getwc (stdin);
      if (buf[n] == WEOF)
	break;
      ++n;
    }
  buf[n] = L'\0';

  return wcscmp (buf, L"This is a test of getwc\n") != 0;
}