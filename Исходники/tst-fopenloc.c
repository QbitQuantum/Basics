int
main (void)
{
  FILE *fp;

  mtrace ();

  setlocale (LC_ALL, "de_DE.UTF-8");

  fp = fopen (inputfile, "r,ccs=ISO-8859-1");
  if (fp == NULL)
    {
      printf ("cannot open \"%s\": %s\n", inputfile, strerror (errno));
      exit (1);
    }

  while (! feof_unlocked (fp))
    {
      wchar_t buf[200];

      if (fgetws_unlocked (buf, sizeof (buf) / sizeof (buf[0]), fp) == NULL)
	break;

      fputws (buf, stdout);
    }

  fclose (fp);

  return 0;
}