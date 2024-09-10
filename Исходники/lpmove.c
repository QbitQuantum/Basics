int
main(int  argc,				/* I - Number of command-line arguments */
     char *argv[])			/* I - Command-line arguments */
{
  int		i;			/* Looping var */
  http_t	*http;			/* Connection to server */
  const char	*job;			/* Job name */
  int		jobid;			/* Job ID */
  int		num_dests;		/* Number of destinations */
  cups_dest_t	*dests;			/* Destinations */
  const char	*src,			/* Original queue */
		*dest;			/* New destination */


  _cupsSetLocale(argv);

  dest      = NULL;
  dests     = NULL;
  job       = NULL;
  jobid     = 0;
  num_dests = 0;
  src       = NULL;

  for (i = 1; i < argc; i ++)
    if (argv[i][0] == '-')
      switch (argv[i][1])
      {
        case 'E' : /* Encrypt */
#ifdef HAVE_SSL
	    cupsSetEncryption(HTTP_ENCRYPT_REQUIRED);

#else
            _cupsLangPrintf(stderr,
	                    _("%s: Sorry, no encryption support."),
	                    argv[0]);
#endif /* HAVE_SSL */
	    break;

        case 'h' : /* Connect to host */
	    if (argv[i][2] != '\0')
	      cupsSetServer(argv[i] + 2);
	    else
	    {
	      i ++;

	      if (i >= argc)
	      {
	        _cupsLangPuts(stderr,
		              _("Error: need hostname after \"-h\" option."));
		return (1);
              }

	      cupsSetServer(argv[i]);
	    }
	    break;

	default :
	    _cupsLangPrintf(stderr, _("lpmove: Unknown option \"%c\"."),
	                    argv[i][1]);
	    return (1);
      }
    else if (!jobid && !src)
    {
      if (num_dests == 0)
        num_dests = cupsGetDests(&dests);

      if ((job = strrchr(argv[i], '-')) != NULL &&
          cupsGetDest(argv[i], NULL, num_dests, dests) == NULL)
        jobid = atoi(job + 1);
      else if (isdigit(argv[i][0] & 255) &&
               !cupsGetDest(argv[i], NULL, num_dests, dests))
        jobid = atoi(argv[i]);
      else
        src = argv[i];
    }
    else if (dest == NULL)
      dest = argv[i];
    else
    {
      _cupsLangPrintf(stderr, _("lpmove: Unknown argument \"%s\"."), argv[i]);
      return (1);
    }

  if ((!jobid && !src) || !dest)
  {
    _cupsLangPuts(stdout, _("Usage: lpmove job/src dest"));
    return (1);
  }

  http = httpConnectEncrypt(cupsServer(), ippPort(), cupsEncryption());

  if (http == NULL)
  {
    _cupsLangPrintf(stderr, _("lpmove: Unable to connect to server: %s"),
		    strerror(errno));
    return (1);
  }

  return (move_job(http, src, jobid, dest));
}