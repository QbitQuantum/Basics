int
main (int argc, char *argv[])
{
  int result = 0;
  bool nocache = false;
  size_t nstrings, nstrings_max;
  struct lines *strings;
  char *line = NULL;
  size_t len = 0;
  size_t n;

  if (argc < 2)
    error (1, 0, "usage: %s <random seed> [-nocache]", argv[0]);

  if (argc == 3)
    {
      if (strcmp (argv[2], "-nocache") == 0)
	nocache = true;
      else
	{
	  printf ("Unknown option %s!\n", argv[2]);
	  exit (1);
	}
    }

  setlocale (LC_ALL, "");

  nstrings_max = 100;
  nstrings = 0;
  strings = (struct lines *) malloc (nstrings_max * sizeof (struct lines));
  if (strings == NULL)
    {
      perror (argv[0]);
      exit (1);
    }

  while (1)
    {
      char saved, *word, *newp;
      size_t l, line_len, needed;

      if (getline (&line, &len, stdin) < 0)
	break;

      if (nstrings == nstrings_max)
	{
	  strings = (struct lines *) realloc (strings,
					      (nstrings_max *= 2)
					       * sizeof (*strings));
	  if (strings == NULL)
	    {
	      perror (argv[0]);
	      exit (1);
	    }
	}
      strings[nstrings].line = strdup (line);
      l = strcspn (line, ":(;");
      while (l > 0 && isspace (line[l - 1]))
	--l;

      saved = line[l];
      line[l] = '\0';

      if (nocache)
	{
	  line_len = strlen (line);
	  word = malloc (line_len + SMALL_STR_SIZE + 1);
	  if (word == NULL)
	    {
	      printf ("malloc failed: %m\n");
	      exit (1);
	    }
	  memset (word, ' ', SMALL_STR_SIZE);
	  memcpy (word + SMALL_STR_SIZE, line, line_len);
	  word[line_len + SMALL_STR_SIZE] = '\0';
	}
      else
        word = line;

      needed = strxfrm (NULL, word, 0);
      newp = malloc (needed + 1);
      if (newp == NULL)
	{
	  printf ("malloc failed: %m\n");
	  exit (1);
	}
      strxfrm (newp, word, needed + 1);
      strings[nstrings].xfrm = newp;

      if (nocache)
	free (word);
      line[l] = saved;
      ++nstrings;
    }
  free (line);

  /* First shuffle.  */
  srandom (atoi (argv[1]));
  for (n = 0; n < 10 * nstrings; ++n)
    {
      int r1, r2, r;
      size_t idx1 = random () % nstrings;
      size_t idx2 = random () % nstrings;
      struct lines tmp = strings[idx1];
      strings[idx1] = strings[idx2];
      strings[idx2] = tmp;

      /* While we are at it a first little test.  */
      r1 = strcmp (strings[idx1].xfrm, strings[idx2].xfrm);
      r2 = strcmp (strings[idx2].xfrm, strings[idx1].xfrm);
      r = -(r1 ^ r2);
      if (r)
	r /= abs (r1 ^ r2);

      if (r < 0 || (r == 0 && (r1 != 0 || r2 != 0))
	  || (r > 0 && (r1 ^ r2) >= 0))
	printf ("collate wrong: %d vs. %d\n", r1, r2);
    }

  /* Now sort.  */
  qsort (strings, nstrings, sizeof (struct lines), xstrcmp);

  /* Print the result.  */
  for (n = 0; n < nstrings; ++n)
    {
      fputs (strings[n].line, stdout);
      free (strings[n].line);
      free (strings[n].xfrm);
    }
  free (strings);

  return result;
}