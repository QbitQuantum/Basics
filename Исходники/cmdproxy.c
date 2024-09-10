int
main (int argc, char ** argv)
{
  int rc;
  int need_shell;
  char * cmdline;
  char * progname;
  int envsize;
  char **pass_through_args;
  int num_pass_through_args;
  char modname[MAX_PATH];
  char path[MAX_PATH];
  char dir[MAX_PATH];
  int status;

  interactive = TRUE;

  SetConsoleCtrlHandler ((PHANDLER_ROUTINE) console_event_handler, TRUE);

  if (!GetCurrentDirectory (sizeof (dir), dir))
    fail ("error: GetCurrentDirectory failed\n");

  /* We serve double duty: we can be called either as a proxy for the
     real shell (that is, because we are defined to be the user shell),
     or in our role as a helper application for running DOS programs.
     In the former case, we interpret the command line options as if we
     were a Unix shell, but in the latter case we simply pass our
     command line to CreateProcess.  We know which case we are dealing
     with by whether argv[0] refers to ourself or to some other program.
     (This relies on an arcane feature of CreateProcess, where we can
     specify cmdproxy as the module to run, but specify a different
     program in the command line - the MSVC startup code sets argv[0]
     from the command line.)  */

  if (!GetModuleFileName (NULL, modname, sizeof (modname)))
    fail ("error: GetModuleFileName failed\n");

  /* Change directory to location of .exe so startup directory can be
     deleted.  */
  progname = strrchr (modname, '\\');
  *progname = '\0';
  SetCurrentDirectory (modname);
  *progname = '\\';

  /* Due to problems with interaction between API functions that use "OEM"
     codepage vs API functions that use the "ANSI" codepage, we need to
     make things consistent by choosing one and sticking with it.  */
  SetConsoleCP (GetACP ());
  SetConsoleOutputCP (GetACP ());

  /* Although Emacs always sets argv[0] to an absolute pathname, we
     might get run in other ways as well, so convert argv[0] to an
     absolute name before comparing to the module name.  */
  path[0] = '\0';
  /* The call to SearchPath will find argv[0] in the current
     directory, append ".exe" to it if needed, and also canonicalize
     it, to resolve references to ".", "..", etc.  */
  status = SearchPath (NULL, argv[0], ".exe", sizeof (path), path,
				  &progname);
  if (!(status > 0 && stricmp (modname, path) == 0))
    {
      if (status <= 0)
	{
	  char *s;

	  /* Make sure we have argv[0] in path[], as the failed
	     SearchPath might not have copied it there.  */
	  strcpy (path, argv[0]);
	  /* argv[0] could include forward slashes; convert them all
	     to backslashes, for strrchr calls below to DTRT.  */
	  for (s = path; *s; s++)
	    if (*s == '/')
	      *s = '\\';
	}
      /* Perhaps MODNAME and PATH use mixed short and long file names.  */
      if (!(GetShortPathName (modname, modname, sizeof (modname))
	    && GetShortPathName (path, path, sizeof (path))
	    && stricmp (modname, path) == 0))
	{
	  /* Sometimes GetShortPathName fails because one or more
	     directories leading to argv[0] have issues with access
	     rights.  In that case, at least we can compare the
	     basenames.  Note: this disregards the improbable case of
	     invoking a program of the same name from another
	     directory, since the chances of that other executable to
	     be both our namesake and a 16-bit DOS application are nil.  */
	  char *p = strrchr (path, '\\');
	  char *q = strrchr (modname, '\\');
	  char *pdot, *qdot;

	  if (!p)
	    p = strchr (path, ':');
	  if (!p)
	    p = path;
	  else
	    p++;
	  if (!q)
	    q = strchr (modname, ':');
	  if (!q)
	    q = modname;
	  else
	    q++;

	  pdot = strrchr (p, '.');
	  if (!pdot || stricmp (pdot, ".exe") != 0)
	    pdot = p + strlen (p);
	  qdot = strrchr (q, '.');
	  if (!qdot || stricmp (qdot, ".exe") != 0)
	    qdot = q + strlen (q);
	  if (pdot - p != qdot - q || strnicmp (p, q, pdot - p) != 0)
	    {
	      /* We are being used as a helper to run a DOS app; just
		 pass command line to DOS app without change.  */
	      /* TODO: fill in progname.  */
	      if (spawn (NULL, GetCommandLine (), dir, &rc))
		return rc;
	      fail ("Could not run %s\n", GetCommandLine ());
	    }
	}
    }

  /* Process command line.  If running interactively (-c or /c not
     specified) then spawn a real command shell, passing it the command
     line arguments.

     If not running interactively, then attempt to execute the specified
     command directly.  If necessary, spawn a real shell to execute the
     command.

  */

  progname = NULL;
  cmdline = NULL;
  /* If no args, spawn real shell for interactive use.  */
  need_shell = TRUE;
  interactive = TRUE;
  /* Ask command.com to create an environment block with a reasonable
     amount of free space.  */
  envsize = get_env_size () + 300;
  pass_through_args = (char **) alloca (argc * sizeof (char *));
  num_pass_through_args = 0;

  while (--argc > 0)
    {
      ++argv;
      /* Act on switches we recognize (mostly single letter switches,
	 except for -e); all unrecognized switches and extra args are
	 passed on to real shell if used (only really of benefit for
	 interactive use, but allow for batch use as well).  Accept / as
	 switch char for compatibility with cmd.exe.  */
      if (((*argv)[0] == '-' || (*argv)[0] == '/') && (*argv)[1] != '\0')
	{
	  if (((*argv)[1] == 'c' || (*argv)[1] == 'C') && ((*argv)[2] == '\0'))
	    {
	      if (--argc == 0)
		fail ("error: expecting arg for %s\n", *argv);
	      cmdline = *(++argv);
	      interactive = FALSE;
	    }
	  else if (((*argv)[1] == 'i' || (*argv)[1] == 'I') && ((*argv)[2] == '\0'))
	    {
	      if (cmdline)
		warn ("warning: %s ignored because of -c\n", *argv);
	    }
	  else if (((*argv)[1] == 'e' || (*argv)[1] == 'E') && ((*argv)[2] == ':'))
	    {
	      int requested_envsize = atoi (*argv + 3);
	      /* Enforce a reasonable minimum size, as above.  */
	      if (requested_envsize > envsize)
		envsize = requested_envsize;
	      /* For sanity, enforce a reasonable maximum.  */
	      if (envsize > 32768)
		envsize = 32768;
	    }
	  else
	    {
	      /* warn ("warning: unknown option %s ignored", *argv); */
	      pass_through_args[num_pass_through_args++] = *argv;
	    }
	}
      else
	break;
    }

#if 0
  /* I think this is probably not useful - cmd.exe ignores extra
     (non-switch) args in interactive mode, and they cannot be passed on
     when -c was given.  */

  /* Collect any remaining args after (initial) switches.  */
  while (argc-- > 0)
    {
      pass_through_args[num_pass_through_args++] = *argv++;
    }
#else
  /* Probably a mistake for there to be extra args; not fatal.  */
  if (argc > 0)
    warn ("warning: extra args ignored after '%s'\n", argv[-1]);
#endif

  pass_through_args[num_pass_through_args] = NULL;

  /* If -c option, determine if we must spawn a real shell, or if we can
     execute the command directly ourself.  */
  if (cmdline)
    {
      const char *args;

      /* The program name is the first token of cmdline.  Since
         filenames cannot legally contain embedded quotes, the value
         of escape_char doesn't matter.  */
      args = cmdline;
      if (!get_next_token (path, &args))
        fail ("error: no program name specified.\n");

      canon_filename (path);
      progname = make_absolute (path);

      /* If we found the program and the rest of the command line does
         not contain unquoted shell metacharacters, run the program
         directly (if not found it might be an internal shell command,
         so don't fail).  */
      if (progname != NULL && try_dequote_cmdline (cmdline))
        need_shell = FALSE;
      else
        progname = NULL;
    }

 pass_to_shell:
  if (need_shell)
    {
      char * p;
      int    extra_arg_space = 0;
      int    maxlen, remlen;
      int    run_command_dot_com;

      progname = getenv ("COMSPEC");
      if (!progname)
	fail ("error: COMSPEC is not set\n");

      canon_filename (progname);
      progname = make_absolute (progname);

      if (progname == NULL || strchr (progname, '\\') == NULL)
	fail ("error: the program %s could not be found.\n", getenv ("COMSPEC"));

      /* Need to set environment size when running command.com.  */
      run_command_dot_com =
	(stricmp (strrchr (progname, '\\'), "command.com") == 0);

      /* Work out how much extra space is required for
         pass_through_args.  */
      for (argv = pass_through_args; *argv != NULL; ++argv)
	/* We don't expect to have to quote switches.  */
	extra_arg_space += strlen (*argv) + 2;

      if (cmdline)
	{
	  char * buf;

	  /* Convert to syntax expected by cmd.exe/command.com for
	     running non-interactively.  Always quote program name in
	     case path contains spaces (fortunately it can't contain
	     quotes, since they are illegal in path names).  */

	  remlen = maxlen =
	    strlen (progname) + extra_arg_space + strlen (cmdline) + 16 + 2;
	  buf = p = alloca (maxlen + 1);

	  /* Quote progname in case it contains spaces.  */
	  p += _snprintf (p, remlen, "\"%s\"", progname);
	  remlen = maxlen - (p - buf);

	  /* Include pass_through_args verbatim; these are just switches
             so should not need quoting.  */
	  for (argv = pass_through_args; *argv != NULL; ++argv)
	    {
	      p += _snprintf (p, remlen, " %s", *argv);
	      remlen = maxlen - (p - buf);
	    }

	  /* Now that we know we will be invoking the shell, quote the
	     command line after the "/c" switch as the shell expects:
	     a single pair of quotes enclosing the entire command
	     tail, no matter whether quotes are used in the command
	     line, and how many of them are there.  See the output of
	     "cmd /?" for how cmd.exe treats quotes.  */
	  if (run_command_dot_com)
	    _snprintf (p, remlen, " /e:%d /c \"%s\"", envsize, cmdline);
	  else
	    _snprintf (p, remlen, " /c \"%s\"", cmdline);
	  cmdline = buf;
	}
      else
	{
	  if (run_command_dot_com)
	    {
	      /* Provide dir arg expected by command.com when first
		 started interactively (the "command search path").  To
		 avoid potential problems with spaces in command dir
		 (which cannot be quoted - command.com doesn't like it),
		 we always use the 8.3 form.  */
	      GetShortPathName (progname, path, sizeof (path));
	      p = strrchr (path, '\\');
	      /* Trailing slash is acceptable, so always leave it.  */
	      *(++p) = '\0';
	    }
	  else
	    path[0] = '\0';

	  remlen = maxlen =
	    strlen (progname) + extra_arg_space + strlen (path) + 13;
	  cmdline = p = alloca (maxlen + 1);

	  /* Quote progname in case it contains spaces.  */
	  p += _snprintf (p, remlen, "\"%s\" %s", progname, path);
	  remlen = maxlen - (p - cmdline);

	  /* Include pass_through_args verbatim; these are just switches
             so should not need quoting.  */
	  for (argv = pass_through_args; *argv != NULL; ++argv)
	    {
	      p += _snprintf (p, remlen, " %s", *argv);
	      remlen = maxlen - (p - cmdline);
	    }

	  if (run_command_dot_com)
	    _snprintf (p, remlen, " /e:%d", envsize);
	}
    }

  if (!progname)
    fail ("Internal error: program name not defined\n");

  if (!cmdline)
    cmdline = progname;

  if (spawn (progname, cmdline, dir, &rc))
    return rc;

  if (!need_shell)
    {
      need_shell = TRUE;
      goto pass_to_shell;
    }

  fail ("Could not run %s\n", progname);

  return 0;
}