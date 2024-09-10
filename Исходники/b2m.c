int
main (int argc, char **argv)
{
  logical labels_saved, printing, header, first, last_was_blank_line;
  time_t ltoday;
  struct tm *tm;
  char *labels, *p, *today;
  struct linebuffer data;

#ifdef MSDOS
  _fmode = O_BINARY;		/* all of files are treated as binary files */
#if __DJGPP__ > 1
  if (!isatty (fileno (stdout)))
    setmode (fileno (stdout), O_BINARY);
  if (!isatty (fileno (stdin)))
    setmode (fileno (stdin), O_BINARY);
#else /* not __DJGPP__ > 1 */
  (stdout)->_flag &= ~_IOTEXT;
  (stdin)->_flag &= ~_IOTEXT;
#endif /* not __DJGPP__ > 1 */
#endif
  progname = argv[0];

  while (1)
    {
      int opt = getopt_long (argc, argv, "hV", longopts, 0);
      if (opt == EOF)
	break;

      switch (opt)
	{
	case 'V':
	  printf ("%s (GNU Emacs %s)\n", "b2m", VERSION);
	  puts ("b2m is in the public domain.");
	  exit (EXIT_SUCCESS);

	case 'h':
	  fprintf (stderr, "Usage: %s <babylmailbox >unixmailbox\n", progname);
	  exit (EXIT_SUCCESS);
	}
    }

  if (optind != argc)
    {
      fprintf (stderr, "Usage: %s <babylmailbox >unixmailbox\n", progname);
      exit (EXIT_SUCCESS);
    }

  labels_saved = printing = header = last_was_blank_line = FALSE;
  first = TRUE;
  ltoday = time (0);
  /* Convert to a string, checking for out-of-range time stamps.
     Don't use 'ctime', as that might dump core if the hardware clock
     is set to a bizarre value.  */
  tm = localtime (&ltoday);
  if (! (tm && TM_YEAR_IN_ASCTIME_RANGE (tm->tm_year)
	 && (today = asctime (tm))))
    fatal ("current time is out of range");
  data.size = 200;
  data.buffer = xnew (200, char);

  if (readline (&data, stdin) == 0
      || !strneq (data.buffer, "BABYL OPTIONS:", 14))
    fatal ("standard input is not a Babyl mailfile.");

  while (readline (&data, stdin) > 0)
    {
      if (streq (data.buffer, "*** EOOH ***") && !printing)
	{
	  printing = header = TRUE;
	  printf ("From \"Babyl to mail by %s\" %s", progname, today);
	  continue;
	}

      if (data.buffer[0] == '\037')
	{
	  if (data.buffer[1] == '\0')
	    continue;
	  else if (data.buffer[1] == '\f')
	    {
	      if (first)
		first = FALSE;
	      else if (! last_was_blank_line)
		puts("");
	      /* Save labels. */
	      readline (&data, stdin);
	      p = strtok (data.buffer, " ,\r\n\t");
	      labels = "X-Babyl-Labels: ";

	      while ((p = strtok (NULL, " ,\r\n\t")))
		labels = concat (labels, p, ", ");

	      p = &labels[strlen (labels) - 2];
	      if (*p == ',')
		*p = '\0';
	      printing = header = FALSE;
	      labels_saved = TRUE;
	      continue;
	    }
	}

      if ((data.buffer[0] == '\0') && header)
	{
	  header = FALSE;
	  if (labels_saved)
	    puts (labels);
	}

      if (printing)
	{
	  puts (data.buffer);
	  if (data.buffer[0] == '\0')
	    last_was_blank_line = TRUE;
	  else
	    last_was_blank_line = FALSE;
	}
    }

  return EXIT_SUCCESS;
}