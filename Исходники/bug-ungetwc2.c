static int
do_test (void)
{
  size_t i;
  wint_t wc;
  FILE *fp;
  int fd;

  fname = (char *) malloc (strlen (test_dir) + sizeof "/bug-ungetwc2.XXXXXX");
  if (fname == NULL)
    {
      puts ("no memory");
      return 1;
    }
  strcpy (stpcpy (fname, test_dir), "/bug-ungetwc2.XXXXXX");
  fd = mkstemp (fname);
  if (fd == -1)
    {
      printf ("cannot open temporary file: %m\n");
      return 1;
    }
  add_temp_file (fname);

  printf ("\nNote: This program runs on %s locale.\n\n", test_locale);

  if (setlocale (LC_ALL, test_locale) == NULL)
    {
      fprintf (stderr, "Cannot use `%s' locale.\n", test_locale);
      exit (EXIT_FAILURE);
    }

  /* Output to the file. */
  if ((fp = fdopen (fd, "w")) == NULL)
    {
      setlocale (LC_ALL, "C");
      fprintf (stderr, "Cannot make `%s' file.\n", fname);
      exit (EXIT_FAILURE);
    }
  fprintf (fp, "%ls", write_wchars);
  fclose (fp);

  /* Read from the file. */
  fp = fopen (fname, "r");
  if (fp == NULL)
    {
      setlocale (LC_ALL, "C");
      error (EXIT_FAILURE, errno, "cannot open %s", fname);
    }

  printf ("%s is opened.\n", fname);

  for (i = 0; i < last_pos; i++)
    {
      wc = getwc (fp);
      printf ("> `%lc' is gotten.\n", wc);
    }

  /* Unget a wide character. */
  ungetwc (unget_wchar, fp);
  printf ("< `%lc' is ungotten.\n", unget_wchar);

  /* Reget the wide character. */
  wc = getwc (fp);
  printf ("> `%lc' is regotten.\n", wc);

  fflush (stdout);
  fclose (fp);

  return 0;
}