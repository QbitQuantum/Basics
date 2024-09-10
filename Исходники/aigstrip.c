int
main (int argc, char **argv)
{
  const char *name, *error;
  char *renamed;
  aiger *aiger;
  int i, res;

  name = 0;
  for (i = 1; i < argc; i++)
    {
      if (!strcmp (argv[i], "-h"))
	{
	  fprintf (stderr, "usage: aigstrip [-h][<file>]\n");
	  return 0;
	}
      else if (argv[i][0] == '-')
	{
	  fprintf (stderr, "*** [aigstrip] invalid option '%s'\n", argv[i]);
	  return 1;
	}
      else if (name)
	{
	  fprintf (stderr, "*** [aigstrip] multiple files\n");
	  return 1;
	}
      else
	name = argv[i];
    }

  res = 0;

  aiger = aiger_init ();
  if (!name) 
    {
      if((error = aiger_read_from_file (aiger, stdin))) goto PARSE_ERROR;
      (void) aiger_strip_symbols_and_comments (aiger);
      if (!aiger_write_to_file (aiger,
             (isatty (1) ? aiger_ascii_mode : aiger_binary_mode), stdout))
	{
	  fprintf (stderr, "*** [aigstrip] write error\n");
	  res = 1;
	}
    }
  else if ((error = aiger_open_and_read_from_file (aiger, name)))
    {
PARSE_ERROR:
      fprintf (stderr, "*** [aigstrip] read error: %s\n", error);
      res = 1;
    }
  else 
    {
      (void) aiger_strip_symbols_and_comments (aiger);
      renamed = malloc (strlen (name) + 2);
      sprintf (renamed, "%s~", name);

      if (rename (name, renamed))
	{
	  fprintf (stderr, "*** [aigstrip] failed to rename '%s'\n", name);
	  res = 1;
	}
      else if (aiger_open_and_write_to_file (aiger, name))
	{
	  if (unlink (renamed))
	    {
	      fprintf (stderr,
		       "*** [aigstrip] failed to remove '%s'\n", renamed);

	      res = 0;		/* !!! */
	    }
	}
      else
	{

	  fprintf (stderr, "*** [aigstrip] failed to write '%s'\n", name);
	  res = 1;

	  if (rename (renamed, name))
	    fprintf (stderr, "*** [aigstrip] backup in '%s'\n", renamed);
	  else
	    fprintf (stderr, "*** [aigstrip] original file restored\n");
	}

      free (renamed);
    }

  aiger_reset (aiger);

  return res;
}