int
main (int argc, char **argv)
{
  int i;

  progname = argv[0];

  /* If first two args are -o FILE, output to FILE.  */
  i = 1;
  if (argc > i + 1 && !strcmp (argv[i], "-o"))
    {
      if (! freopen (argv[i + 1], "w", stdout))
	{
	  perror (argv[i + 1]);
	  return EXIT_FAILURE;
	}
      i += 2;
    }
  if (argc > i + 1 && !strcmp (argv[i], "-a"))
    {
      if (! freopen (argv[i + 1], "a", stdout))
	{
	  perror (argv[i + 1]);
	  return EXIT_FAILURE;
	}
      i += 2;
    }
  if (argc > i + 1 && !strcmp (argv[i], "-d"))
    {
      if (chdir (argv[i + 1]) != 0)
	{
	  perror (argv[i + 1]);
	  return EXIT_FAILURE;
	}
      i += 2;
    }
  if (argc > i && !strcmp (argv[i], "-g"))
    {
      generate_globals = true;
      ++i;
    }

  set_binary_mode (fileno (stdout), O_BINARY);

  if (generate_globals)
    start_globals ();

  if (argc <= i)
    scan_c_stream (stdin);
  else
    {
      int first_infile = i;
      for (; i < argc; i++)
	{
	  int j;
	  /* Don't process one file twice.  */
	  for (j = first_infile; j < i; j++)
	    if (strcmp (argv[i], argv[j]) == 0)
	      break;
	  if (j == i)
	    scan_file (argv[i]);
	}
    }

  if (generate_globals)
    write_globals ();

  if (ferror (stdout) || fclose (stdout) != 0)
    fatal ("write error");

  return EXIT_SUCCESS;
}