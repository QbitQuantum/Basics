static int
do_test (void)
{
  char name[] = "/tmp/tst-freopen.XXXXXX";
  const char * const test = "Let's test freopen.\n";
  char temp[strlen (test) + 1];
  int fd = mkstemp (name);
  FILE *f;

  if (fd == -1)
    {
      printf ("%u: cannot open temporary file: %m\n", __LINE__);
      exit (1);
    }

  f = fdopen (fd, "w");
  if (f == NULL)
    {
      printf ("%u: cannot fdopen temporary file: %m\n", __LINE__);
      exit (1);
    }

  fputs (test, f);
  fclose (f);

  f = fopen (name, "r");
  if (f == NULL)
    {
      printf ("%u: cannot fopen temporary file: %m\n", __LINE__);
      exit (1);
    }

  if (fread (temp, 1, strlen (test), f) != strlen (test))
    {
      printf ("%u: couldn't read the file back: %m\n", __LINE__);
      exit (1);
    }
  temp [strlen (test)] = '\0';

  if (strcmp (test, temp))
    {
      printf ("%u: read different string than was written:\n%s%s",
	      __LINE__, test, temp);
      exit (1);
    }

  f = freopen (name, "r+", f);
  if (f == NULL)
    {
      printf ("%u: cannot freopen temporary file: %m\n", __LINE__);
      exit (1);
    }

  if (fseek (f, 0, SEEK_SET) != 0)
    {
      printf ("%u: couldn't fseek to start: %m\n", __LINE__);
      exit (1);
    }

  if (fread (temp, 1, strlen (test), f) != strlen (test))
    {
      printf ("%u: couldn't read the file back: %m\n", __LINE__);
      exit (1);
    }
  temp [strlen (test)] = '\0';

  if (strcmp (test, temp))
    {
      printf ("%u: read different string than was written:\n%s%s",
	      __LINE__, test, temp);
      exit (1);
    }

  fclose (f);

  unlink (name);
  exit (0);
}