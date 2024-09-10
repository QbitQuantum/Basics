int
main (int argc, char **argv)
{
  BOOL ret;
  HKEY hkey, skey;
  WCHAR keyname[256], stdname[256], std2name[256], country[10], *spc;
  GEOID geo;
  int opt, idx, gotit = -1;

  setlocale (LC_ALL, "");
  while ((opt = getopt_long (argc, argv, opts, longopts, NULL)) != EOF)
    switch (opt)
      {
      case 'h':
	usage (stdout);
	return 0;
      case 'V':
	print_version ();
	return 0;
      default:
	fprintf (stderr, "Try `%s --help' for more information.\n",
		 program_invocation_short_name);
	return 1;
      }
  if (optind < argc)
    {
	usage (stderr);
	return 1;
    }

  /* First fetch current timezone information from registry. */
  hkey = reg_open (HKEY_LOCAL_MACHINE, REG_TZINFO, "timezone information");
  if (!hkey)
    return 1;
  /* Vista introduced the TimeZoneKeyName value, which simplifies the
     job a lot. */
  if (!reg_query (hkey, L"TimeZoneKeyName", keyname, sizeof keyname, NULL))
    {
      /* Pre-Vista we have a lot more to do.  First fetch the name of the
	 Standard (non-DST) timezone.  If we can't get that, give up. */
      if (!reg_query (hkey, L"StandardName", stdname, sizeof stdname,
		      "timezone information"))
	{
	  reg_close (hkey);
	  return 1;
	}
      reg_close (hkey);
      /* Now open the timezone database registry key.  Every subkey is a
         timezone.  The key name is what we're after, but to find the right
	 one, we have to compare the name of the previously fetched
	 "StandardName" with the "Std" value in the timezone info... */
      hkey = reg_open (HKEY_LOCAL_MACHINE, REG_TZDB, "timezone database");
      if (!hkey)
	return 1;
      for (idx = 0; reg_enum (hkey, idx, keyname, sizeof keyname); ++idx)
	{
	  skey = reg_open (hkey, keyname, NULL);
	  if (skey)
	    {
	      /* ...however, on MUI-enabled machines, the names are not stored
		 directly in the above StandardName, rather it is a resource
		 pointer into tzres.dll.  This is stored in MUI_Std.
		 Fortunately it's easy to recognize this situation: If
		 StandardName starts with @, it's a resource pointer, otherwise
		 it's the cleartext value. */
	      ret = reg_query (skey, stdname[0] == L'@' ? L"MUI_Std" : L"Std",
			       std2name, sizeof std2name, NULL);
	      reg_close (skey);
	      if (ret && !wcscmp (stdname, std2name))
		break;
	    }
	}
    }
  reg_close (hkey);

  /* Fetch addresses of Geo functions.  As long as we support Windows 2000
     this is required, unfortunately. */
  getusergeoid = (GEOID (WINAPI *)())
	       GetProcAddress (GetModuleHandle ("kernel32.dll"), "GetUserGeoID");
  getgeoinfo = (int (WINAPI *)(GEOID, GEOTYPE, LPWSTR, int, LANGID))
	       GetProcAddress (GetModuleHandle ("kernel32.dll"), "GetGeoInfoW");
  *country = L'\0';
  /* Post-W2K we fetch the current Geo-location of the user and convert it
     to a ISO 3166-1 compatible nation code. */
  if (getusergeoid && getgeoinfo)
    {
      geo = getusergeoid (GEOCLASS_NATION);
      if (geo != GEOID_NOT_AVAILABLE)
	getgeoinfo (geo, GEO_ISO2, country, sizeof country, 0);
    }
  /* On W2K, or if the Geo-location isn't available, we use the locale
     setting instead. */
  if (!*country)
    GetLocaleInfoW (LOCALE_USER_DEFAULT, LOCALE_SISO3166CTRYNAME,
		    country, sizeof country);

  /* Now iterate over the mapping table and find the right entry. */
  for (idx = 0; idx < TZMAP_SIZE; ++idx)
    {
      if (!wcscmp (keyname, tzmap[idx].win_tzkey))
	{
	  if (gotit < 0)
	    gotit = idx;
	  if (!wcscmp (country, tzmap[idx].country))
	    break;
	}
      else if (gotit >= 0)
	{
	  idx = gotit;
	  break;
	}
    }
  if (idx >= TZMAP_SIZE)
    {
      if (gotit < 0)
	{
	  fprintf (stderr,
		   "%s: can't find matching POSIX timezone for "
		   "Windows timezone \"%ls\"\n",
		   program_invocation_short_name, keyname);
	  return 1;
	}
      idx = gotit;
    }
  /* Got one.  Print it.
     Note: The tzmap array is in the R/O data section on x86_64.  Don't
           try to overwrite the space, as the code did originally. */
  spc = wcschr (tzmap[idx].posix_tzid, L' ');
  if (!spc)
    spc = wcschr (tzmap[idx].posix_tzid, L'\0');
  printf ("%.*ls\n", (int) (spc - tzmap[idx].posix_tzid), tzmap[idx].posix_tzid);
  return 0;
}