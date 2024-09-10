static int
do_test (void)
{
  wchar_t dummy[10];
  int ret = 0;
  FILE *fp;
  int result = 0;

  fp = fdopen (fd, "w+");
  if (fp == NULL)
    {
      puts ("fopen(""testfile"", ""w+"") returned NULL.");
      return 1;
    }
  else
    {
      fwprintf (fp, L"abcd");
      printf ("current pos = %ld\n", ftell (fp));
      if (ftell (fp) != 4)
	result = 1;

      rewind (fp);
      ret = fwscanf (fp, L"%c", dummy);

      printf ("current pos = %ld\n", ftell (fp));
      if (ftell (fp) != 1)
	result = 1;

      rewind (fp);
      printf ("current pos = %ld\n", ftell (fp));
      if (ftell (fp) != 0)
	result = 1;

      fclose (fp);
    }

  return result;
}