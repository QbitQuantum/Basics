static char *
findHome(const char *symbols, int argc, const char **argv)
{ const char *home = NULL;
  char envbuf[MAXPATHLEN];
  char plp[MAXPATHLEN];
  const char *val;

  if ( (val=longopt("home", argc, argv)) )
  { if ( (home=PrologPath(val, plp, sizeof(plp))) )
      return store_string(home);
    return NULL;
  }

  if ( (val  = exec_var("homevar")) &&
       (home = Getenv(val, envbuf, sizeof(envbuf))) &&
       (home = PrologPath(home, plp, sizeof(plp))) )
    return store_string(home);
  if ( (val = exec_var("home")) &&
       (home = PrologPath(val, plp, sizeof(plp))) )
    return store_string(home);

#ifdef PLHOMEVAR_1
  if ( !(home = Getenv(PLHOMEVAR_1, envbuf, sizeof(envbuf))) )
  {
#ifdef PLHOMEVAR_2
    home = Getenv(PLHOMEVAR_2, envbuf, sizeof(envbuf));
#endif
  }
  if ( home &&
       (home = PrologPath(home, plp, sizeof(plp))) &&
       ExistsDirectory(home) )
    return store_string(home);
#endif

#ifdef PLHOMEFILE
  if ( (home = symbols) )
  { char buf[MAXPATHLEN];
    char parent[MAXPATHLEN];
    IOSTREAM *fd;

    strcpy(parent, DirName(DirName(AbsoluteFile(home, buf), buf), buf));
    Ssprintf(buf, "%s/" PLHOMEFILE, parent);

    if ( (fd = Sopen_file(buf, "r")) )
    { if ( Sfgets(buf, sizeof(buf), fd) )
      { size_t l = strlen(buf);

	while(l > 0 && buf[l-1] <= ' ')
	  l--;
	buf[l] = EOS;

#if O_XOS
      { char buf2[MAXPATHLEN];
	_xos_canonical_filename(buf, buf2, MAXPATHLEN, 0);
	strcpy(buf, buf2);
      }
#endif

	if ( !IsAbsolutePath(buf) )
	{ char buf2[MAXPATHLEN];

	  Ssprintf(buf2, "%s/%s", parent, buf);
	  home = AbsoluteFile(buf2, plp);
	} else
	  home = AbsoluteFile(buf, plp);

	if ( ExistsDirectory(home) )
	{ Sclose(fd);
	  return store_string(home);
	}
      }
      Sclose(fd);
    }
  }
#endif /*PLHOMEFILE*/

  if ( (home = PrologPath(PLHOME, plp, sizeof(plp))) &&
       ExistsDirectory(home) )
    return store_string(home);

  return NULL;
}