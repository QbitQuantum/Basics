/// Parse command line.  Clobbers localbuf.
static bool read_cmdline(int argc, char *argv[])
{
  assert(argv[argc-1]);
  assert(!argv[argc]);

  for (int i=1; i<argc; ++i)
  {
    assert(argv[i]);
    const char *nextarg = NULL;

    if (argv[i][0] != '-' || !argv[i][1])
    {
      fprintf(stderr, "Illegal argument: %s\n", argv[i]);
      return false;
    }
    const char o = argv[i][1];
    const char *optname;
    if (o == '-')
    {
      // Long option name (starting with double dash)
      optname = argv[i]+2;
      if (!optname[0] || !isalpha(optname[0]))
      {
	fprintf(stderr, "Illegal argument: %s\n", argv[i]);
	return false;
      }
      const char *const eqsign = strchr(optname, '=');
      if (eqsign)
      {
	// Option in '--foo=bar' style
	const size_t optnamelen = eqsign - optname;
	if (optnamelen >= sizeof(localbuf))
	{
	  fprintf(stderr, "Option name too long\n");
	  return false;
	}
	strncpy(localbuf, optname, optnamelen);
	localbuf[optnamelen] = '\0';
	optname = localbuf;
	nextarg = eqsign + 1;
      }
    }
    else
    {
      // Short option name (starting with single dash)
      int j;
      for (j=0;
	   j<sizeof(options)/sizeof(*options) && options[j].shortopt != o;
	   ++j);
      if (j == sizeof(options)/sizeof(*options))
      {
	fprintf(stderr, "Illegal option: -%c\n", o);
	return false;
      }
      optname = options[j].name;

      if (argv[i][2]) nextarg = argv[i] + 2;
    }

    if (!nextarg && argv[i+1] && (argv[i+1][0]!='-'||isdigit(argv[i+1][1])))
    {
      ++i;
      nextarg = argv[i];
    }
    if (!handle_configitem(optname, nextarg)) return false;
  }
  return true;
}