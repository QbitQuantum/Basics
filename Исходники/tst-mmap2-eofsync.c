static int
do_test (void)
{
  const size_t pagesize = getpagesize ();
  FILE *f;
  char buf[pagesize];
  int result = 0;
  int c;

  f = fopen (temp_file, "rm");
  if (f == NULL)
    {
      perror (temp_file);
      return 1;
    }

  if (fread (buf, pagesize, 1, f) != 1)
    {
      perror ("fread");
      return 1;
    }

  if (memcmp (buf, pages, pagesize))
    {
      puts ("data mismatch in page 1");
      result = 1;
    }

  printf ("feof = %d, ferror = %d immediately after fread\n",
	  feof (f), ferror (f));

  c = fgetc (f);
  if (c == EOF)
    printf ("fgetc -> EOF (feof = %d, ferror = %d)\n",
	    feof (f), ferror (f));
  else
    {
      printf ("fgetc returned %o (feof = %d, ferror = %d)\n",
	      c, feof (f), ferror (f));
      result = 1;
    }

  c = write (temp_fd, pages + pagesize, pagesize);
  if (c == (ssize_t) pagesize)
    printf ("wrote more to file\n");
  else
    {
      printf ("wrote %d != %zd (%m)\n", c, pagesize);
      result = 1;
    }

  if (fread (buf, pagesize, 1, f) != 1)
    {
      printf ("second fread fails: feof = %d, ferror = %d (%m)\n",
	      feof (f), ferror (f));
      clearerr (f);
      if (fread (buf, pagesize, 1, f) != 1)
	{
	  printf ("retry fread fails: feof = %d, ferror = %d (%m)\n",
		  feof (f), ferror (f));
	  result = 1;
	}
    }
  if (result == 0 && memcmp (buf, pages + pagesize, pagesize))
    {
      puts ("data mismatch in page 2");
      result = 1;
    }

  fseek (f, pagesize - 1, SEEK_SET);
  c = fgetc (f);
  if (c != 'a')
    {
      printf ("fgetc at end of page 1 read '%c' (%m)\n", c);
      result = 1;
    }

  if (ftruncate (temp_fd, pagesize) < 0)
    {
      printf ("ftruncate failed: %m\n");
      result = 1;
    }

  fflush (f);

  c = fgetc (f);
  if (c == EOF)
    printf ("after truncate fgetc -> EOF (feof = %d, ferror = %d)\n",
	    feof (f), ferror (f));
  else
    {
      printf ("after truncate fgetc returned '%c' (feof = %d, ferror = %d)\n",
	      c, feof (f), ferror (f));
      result = 1;
    }

  fclose (f);

  return result;
}