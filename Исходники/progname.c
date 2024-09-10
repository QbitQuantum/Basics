void
kpathsea_set_program_name (kpathsea kpse,  const_string argv0,
                           const_string progname)
{
  string ext, sdir, sdir_parent, sdir_grandparent;
  string s = getenv ("KPATHSEA_DEBUG");
#ifdef WIN32
  string debug_output = getenv("KPATHSEA_DEBUG_OUTPUT");
  string append_debug_output = getenv("KPATHSEA_DEBUG_APPEND");
  int err, olderr;
#endif

  /* Set debugging stuff first, in case we end up doing debuggable stuff
     during this initialization.  */
  if (s) {
    kpse->debug |= atoi (s);
  }

#if defined(WIN32)
  /* Set various info about user. Among many things,
     ensure that HOME is set.  */
  init_user_info();

  /* redirect stderr to debug_output. Easier to send logfiles. */
  if (debug_output) {
    int flags =  _O_CREAT | _O_TRUNC | _O_RDWR;
    err = -1;
    if (_stricmp(debug_output, "con") == 0
       || _stricmp(debug_output, "con:") == 0) {
      err = _fileno(stdout);
    } else {
      if (append_debug_output) {
        flags =  _O_CREAT | _O_APPEND | _O_WRONLY;
      } else {
        flags =  _O_CREAT | _O_TRUNC | _O_WRONLY;
        kpathsea_xputenv(kpse, "KPATHSEA_DEBUG_APPEND", "yes");
      }
    }

    if ((err < 0)
        && (err = _open(debug_output, flags, _S_IREAD | _S_IWRITE)) == -1)
    {
      WARNING1("Can't open %s for stderr redirection!\n", debug_output);
      perror(debug_output);
    } else if ((olderr = _dup(fileno(stderr))) == -1) {
      WARNING("Can't dup() stderr!\n");
      close(err);
    } else if (_dup2(err, fileno(stderr)) == -1) {
      WARNING1("Can't redirect stderr to %s!\n", debug_output);
      close(olderr);
      close(err);
    } else {
      close(err);
    }
  }
  /* Win95 always gives the short filename for argv0, not the long one.
     There is only this way to catch it. It makes all the kpse_selfdir
     stuff useless for win32. */
  {
    char short_path[PATH_MAX], path[PATH_MAX], *fp;

    /* SearchPath() always gives back an absolute directory */
    if (SearchPath(NULL, argv0, ".exe", PATH_MAX, short_path, &fp) == 0)
        LIB_FATAL1("Can't determine where the executable %s is.\n", argv0);
    if (!win32_get_long_filename(short_path, path, sizeof(path))) {
        LIB_FATAL1("This path points to an invalid file : %s\n", short_path);
    }
    /* slashify the dirname */
    for (fp = path; fp && *fp; fp++)
        if (IS_DIR_SEP(*fp)) *fp = DIR_SEP;
    /* sdir will be the directory of the executable, ie: c:/TeX/bin */
    sdir = xdirname(path);
    kpse->invocation_name = xstrdup(xbasename(path));
  }

#elif defined(__DJGPP__)

  /* DJGPP programs support long filenames on Windows 95, but ARGV0 there
     is always made with the short 8+3 aliases of all the pathname elements.
     If long names are supported, we need to convert that to a long name.

     All we really need is to call `_truename', but most of the code
     below is required to deal with the special case of networked drives.  */
  if (pathconf (argv0, _PC_NAME_MAX) > 12) {
    char long_progname[PATH_MAX];

    if (_truename (argv0, long_progname)) {
      char *fp;

      if (long_progname[1] != ':') {
        /* A complication: `_truename' returns network-specific string at
           the beginning of `long_progname' when the program resides on a
           networked drive, and DOS calls cannot grok such pathnames.  We
           need to convert the filesystem name back to a drive letter.  */
        char rootname[PATH_MAX], rootdir[4];

        if (argv0[0] && argv0[1] == ':')
          rootdir[0] = argv0[0]; /* explicit drive in `argv0' */
        else
          rootdir[0] = getdisk () + 'A';
        rootdir[1] = ':';
        rootdir[2] = '\\';
        rootdir[3] = '\0';
        if (_truename (rootdir, rootname)) {
          /* Find out where `rootname' ends in `long_progname' and replace
             it with the drive letter.  */
          int root_len = strlen (rootname);

          if (IS_DIR_SEP (rootname[root_len - 1]))
            root_len--; /* keep the trailing slash */
          long_progname[0] = rootdir[0];
          long_progname[1] = ':';
          memmove (long_progname + 2, long_progname + root_len,
                   strlen (long_progname + root_len) + 1);
        }
      }

      /* Convert everything to canonical form.  */
      if (long_progname[0] >= 'A' && long_progname[0] <= 'Z')
        long_progname[0] += 'a' - 'A'; /* make drive lower case, for beauty */
      for (fp = long_progname; *fp; fp++)
        if (IS_DIR_SEP (*fp))
          *fp = DIR_SEP;

      kpse->invocation_name = xstrdup (long_progname);
    }
    else
      /* If `_truename' failed, God help them, because we won't...  */
      kpse->invocation_name = xstrdup (argv0);
  }
  else
    kpse->invocation_name = xstrdup (argv0);

#else /* !WIN32 && !__DJGPP__ */
  kpse->invocation_name = xstrdup (argv0);
#endif

  /* We need to find SELFAUTOLOC *before* removing the ".exe" suffix from
     the program_name, otherwise the PATH search inside kpse_selfdir will fail,
     since `prog' doesn't exists as a file, there's `prog.exe' instead.  */
#ifndef WIN32
  sdir = kpathsea_selfdir (kpse, kpse->invocation_name);
#endif
  /* SELFAUTODIR is actually the parent of the invocation directory,
     and SELFAUTOPARENT the grandparent.  This is how teTeX did it.  */
  kpathsea_xputenv (kpse, "SELFAUTOLOC", sdir);
  sdir_parent = xdirname (sdir);
  kpathsea_xputenv (kpse, "SELFAUTODIR", sdir_parent);
  sdir_grandparent = xdirname (sdir_parent);
  kpathsea_xputenv (kpse, "SELFAUTOPARENT", sdir_grandparent);

#if defined(WIN32) || defined(__MINGW32__) || defined(__CYGWIN__)
  mk_suffixlist(kpse);
#endif /* WIN32 || __MINGW32__ || __CYGWIN__ */

  free (sdir);
  free (sdir_parent);
  free (sdir_grandparent);

  kpse->invocation_short_name
    = xstrdup (xbasename (kpse->invocation_name));

  if (progname) {
    kpse->program_name = xstrdup (progname);
  } else {
    /* If configured --enable-shared and running from the build directory
       with the wrapper scripts (e.g., for make check), the binaries will
       be named foo.exe instead of foo.  Or possibly if we're running on a
       DOSISH system.  */
    ext = find_suffix (kpse->invocation_short_name);
    if (ext && FILESTRCASEEQ (ext, "exe")) {
      kpse->program_name = remove_suffix (kpse->invocation_short_name);
    } else {
      kpse->program_name = xstrdup (kpse->invocation_short_name);
    }
  }

  /* Some of the utility routines (like atou() and xfopen()) will use
     FATAL and variations thereof (see lib.h) if there is a problem.

     The next trick makes it possible for that message to report some useful
     name instead of (NULL), if the backward compatible is compiled in. */

#if defined (KPSE_COMPAT_API)
  if (kpse!=kpse_def) {
    kpse_def->invocation_name = xstrdup(kpse->invocation_name);
    kpse_def->invocation_short_name = xstrdup(kpse->invocation_short_name);
  }
#endif

  kpathsea_xputenv (kpse, "progname", kpse->program_name);
}