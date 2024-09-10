static void
ParseOptions (CfgData cfgdata[], TCHAR * s, int clean_up)
{
  TCHAR *cp, *n;
  TCHAR *section;
  int count;
  int i;

  if (clean_up)
    for (i = 0; i < sizeof (attrs) / sizeof (attrs[0]); i++)
      {
	if (cfgdata[i].data)
	  free (cfgdata[i].data);
	cfgdata[i].data = NULL;
	cfgdata[i].supplied = FALSE;
      }

  if (s == NULL)
    return;

  for (count = 0; *s; count++)
    {
      for (cp = s; *cp && *cp != ';'; cp++)
	;
      if (*cp)
	{
	  *cp = 0;
	  n = cp + 1;
	}
      else
	n = cp;
      for (cp = s; *cp && *cp != '='; cp++)
	;
      if (*cp)
	{
	  *cp++ = 0;
	  if (_tcsicmp (s, attrs[oDATABASE].shortName) || _tcsicmp (cp, DEFAULT_DATABASE_PER_USER))
	    for (i = 0; i < sizeof (attrs) / sizeof (attrs[0]); i++)
	      {
		if (attrs[i].shortName && !_tcsicmp (attrs[i].shortName, s))
		  {
		    cfgdata[i].data = _tcsdup (cp);
		    cfgdata[i].supplied = TRUE;
		    break;
		  }
	      }
	}
      /*
       *  Handle missing DSN=... from the beginning:
       *  'dsn_ora7;UID=scott;PWD=tiger'
       */
      else if (count == 0)
	{
	  cfgdata[oDSN].data = _tcsdup (s);
	  cfgdata[oDSN].supplied = TRUE;
	}
      s = n;
    }

  section = cfgdata[oDSN].data;

  if (section == NULL || !section[0])
    section = _T ("Default");

#if defined (DSN_TRANSLATION) && !defined (WIN32)
  {
    PCONFIG pConfig, cfg_odbc_sys, cfg_odbc_usr;
    char *odbcini_sys, *odbcini_usr, *ptr;
    char path[1024];
    char *long_name, *section_narrow;
    TCHAR *valueW;

    /*
     *  1a. Find out where system odbc.ini resides
     */
    if ((odbcini_sys = getenv ("ODBCINI")) == NULL || access (odbcini_sys, R_OK))
      odbcini_sys = "/etc/odbc.ini";

    /*
     *  1b. The default system odbc.ini on Mac OS X is located in
     *      /Library/ODBC/odbc.ini
     */
#ifdef __APPLE__
    if (access (odbcini_sys, R_OK) != 0)
      odbcini_sys = "/Library/ODBC/odbc.ini";
#endif

    /*
     *  1c. Open system odbc.ini
     */
    cfg_init (&cfg_odbc_sys, odbcini_sys);


    /*
     *  2a. Find out where user odbc.ini resides
     */
    if ((ptr = getenv ("HOME")) == NULL)
      {
	ptr = (char *) getpwuid (getuid ());

	if (ptr != NULL)
	  ptr = ((struct passwd *) ptr)->pw_dir;
      }

    if (ptr != NULL)
      snprintf (path, sizeof (path), "%.200s/.odbc.ini", ptr);
    else
      snprintf (path, sizeof (path), ".odbc.ini");

    /*
     *  2b. The default user odbc.ini on Mac OS X is located in
     *      ~/Library/ODBC/odbc.ini
     */
#ifdef __APPLE__
    if (access (path, R_OK) != 0)
      {
	snprintf (path, sizeof (path), "%.200s/Library/ODBC/odbc.ini", ptr ? ptr : "");
      }
#endif

    /*
     *  2c. Open user odbc.ini
     */
    odbcini_usr = path;
    cfg_init (&cfg_odbc_usr, odbcini_usr);

    cli_dbg_printf (("USING %s\n", odbcini_usr));

    section_narrow = virt_wide_to_ansi (section);

    /*
     *  Check where DSN is registered
     */
    if (cfg_find (cfg_odbc_usr, section_narrow, NULL) == 0)
      pConfig = cfg_odbc_usr;
    else
      pConfig = cfg_odbc_sys;
#endif

    for (i = 0; i < sizeof (attrs) / sizeof (attrs[0]); i++)
      if (!cfgdata[i].supplied && attrs[i].longName)
	{
	  if ((cfgdata[i].data = (TCHAR *) malloc ((attrs[i].maxLength + 1) * sizeof (TCHAR))) == NULL)
	    break;
#ifdef DSN_TRANSLATION
# ifdef WIN32
	  SQLGetPrivateProfileString (section, attrs[i].longName, _T (""), cfgdata[i].data, attrs[i].maxLength, _T ("odbc.ini"));
# else
	  valueW = NULL;
	  long_name = virt_wide_to_ansi (attrs[i].longName);
	  if (cfg_find (pConfig, section_narrow, long_name) == -1)
	    valueW = attrs[i].defVal;
	  else
	    valueW = virt_ansi_to_wide (pConfig->value);
	  free_wide_buffer (long_name);
	  _tcsncpy (cfgdata[i].data, valueW, attrs[i].maxLength);
	  cfgdata[i].data[attrs[i].maxLength] = 0;
	  if (valueW != attrs[i].defVal)
	    free_wide_buffer (valueW);
# endif
#else
	  _tcsncpy (cfgdata[i].data, _T (""), attrs[i].maxLength);
#endif
	}

#if defined (DSN_TRANSLATION) && !defined (WIN32)
    cfg_done (cfg_odbc_usr);
    cfg_done (cfg_odbc_sys);
    free_wide_buffer (section_narrow);
  }
#endif
}