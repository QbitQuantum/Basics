int
main(int argc, char **argv)
#endif
{
    int i;

#ifdef LINUXVGA
    LINUX_setup();		/* setup VGA before dropping privilege DBT 4/5/99 */
    drop_privilege();
#endif
/* make sure that we really have revoked root access, this might happen if
   gnuplot is compiled without vga support but is installed suid by mistake */
#ifdef __linux__
    setuid(getuid());
#endif

#if defined(MSDOS) && !defined(_Windows) && !defined(__GNUC__)
    PC_setup();
#endif /* MSDOS !Windows */

/* HBB: Seems this isn't needed any more for DJGPP V2? */
/* HBB: disable all floating point exceptions, just keep running... */
#if defined(DJGPP) && (DJGPP!=2)
    _control87(MCW_EM, MCW_EM);
#endif

#if defined(OS2)
    int rc;
#ifdef OS2_IPC
    char semInputReadyName[40];
    sprintf( semInputReadyName, "\\SEM32\\GP%i_Input_Ready", getpid() );
    rc = DosCreateEventSem(semInputReadyName,&semInputReady,0,0);
    if (rc != 0)
      fputs("DosCreateEventSem error\n",stderr);
#endif
    rc = RexxRegisterSubcomExe("GNUPLOT", (PFN) RexxInterface, NULL);
#endif

/* malloc large blocks, otherwise problems with fragmented mem */
#ifdef OSK
    _mallocmin(102400);
#endif

#ifdef MALLOCDEBUG
    malloc_debug(7);
#endif

/* get helpfile from home directory */
#ifndef DOSX286
# ifndef _Windows
#  if defined (__TURBOC__) && (defined (MSDOS) || defined(DOS386))
    strcpy(HelpFile, argv[0]);
    strcpy(strrchr(HelpFile, DIRSEP1), "\\gnuplot.gih");
#  endif			/*   - DJL */
# endif				/* !_Windows */
#endif /* !DOSX286 */
#ifdef __DJGPP__
    {
	char *s;
	strcpy(HelpFile, argv[0]);
	for (s = HelpFile; *s; s++)
	    if (*s == DIRSEP1)
		*s = DIRSEP2;	/* '\\' to '/' */
	strcpy(strrchr(HelpFile, DIRSEP2), "/gnuplot.gih");
    }			/* Add also some "paranoid" tests for '\\':  AP */
#endif /* DJGPP */

#ifdef VMS
    unsigned int status[2] = { 1, 0 };
#endif

#if defined(HAVE_LIBEDITLINE)
    rl_getc_function = getc_wrapper;
#endif
#if defined(HAVE_LIBREADLINE) || defined(HAVE_LIBEDITLINE)
    using_history();
    /* T.Walter 1999-06-24: 'rl_readline_name' must be this fix name.
     * It is used to parse a 'gnuplot' specific section in '~/.inputrc' */
    rl_readline_name = "Gnuplot";
    rl_terminal_name = getenv("TERM");
#endif
#if defined(HAVE_LIBREADLINE)
    rl_complete_with_tilde_expansion = 1;
#endif

    for (i = 1; i < argc; i++) {
	if (!argv[i])
	    continue;

	if (!strcmp(argv[i], "-V") || !strcmp(argv[i], "--version")) {
	    printf("gnuplot %s patchlevel %s\n",
		    gnuplot_version, gnuplot_patchlevel);
	    return 0;

	} else if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
	    printf( "Usage: gnuplot [OPTION]... [FILE]\n"
#ifdef X11
		    "for X11 options see 'help X11->command-line-options'\n"
#endif
		    "  -V, --version\n"
		    "  -h, --help\n"
		    "  -p  --persist\n"
		    "  -e  \"command1; command2; ...\"\n"
		    "gnuplot %s patchlevel %s\n"
#ifdef DIST_CONTACT
		    "Report bugs to "DIST_CONTACT"\n"
		    "            or %s\n",
#else
		    "Report bugs to %s\n",
#endif
		    gnuplot_version, gnuplot_patchlevel, bug_report);
	    return 0;

	} else if (!strncmp(argv[i], "-persist", 2) || !strcmp(argv[i], "--persist")) {
	    persist_cl = TRUE;
	}
    }

#ifdef X11
    /* the X11 terminal removes tokens that it recognizes from argv. */
    {
	int n = X11_args(argc, argv);
	argv += n;
	argc -= n;
    }
#endif

#ifdef APOLLO
    apollo_pfm_catch();
#endif

    setbuf(stderr, (char *) NULL);

#ifdef HAVE_SETVBUF
    /* this was once setlinebuf(). Docs say this is
     * identical to setvbuf(,NULL,_IOLBF,0), but MS C
     * faults this (size out of range), so we try with
     * size of 1024 instead. [SAS/C does that, too. -lh]
     * Failing this, I propose we just make the call and
     * ignore the return : its probably not a big deal
     */
    if (setvbuf(stdout, (char *) NULL, _IOLBF, (size_t) 1024) != 0)
	(void) fputs("Could not linebuffer stdout\n", stderr);

#ifdef X11
    /* This call used to be in x11.trm, with the following comment:
     *   Multi-character inputs like escape sequences but also mouse-pasted
     *   text got buffered and therefore didn't trigger the select() function
     *   in X11_waitforinput(). Switching to unbuffered input solved this.
     *   23 Jan 2002 (joze)
     * But switching to unbuffered mode causes all characters in the input
     * buffer to be lost. So the only safe time to do it is on program entry.
     * The #ifdef X11 is probably unnecessary, but makes the change minimal.
     * Do any non-X platforms suffer from the same problem?
     * EAM - Jan 2004.
     */
    setvbuf(stdin, (char *) NULL, _IONBF, 0);
#endif

#endif

    gpoutfile = stdout;

    /* Initialize pre-loaded user variables */
    (void) Gcomplex(&udv_pi.udv_value, M_PI, 0.0);
#ifdef HAVE_ISNAN
    udv_NaN = add_udv_by_name("NaN");
    (void) Gcomplex(&(udv_NaN->udv_value), not_a_number(), 0.0);
    udv_NaN->udv_undef = FALSE;
#endif

    init_memory();

    interactive = FALSE;
    init_terminal();		/* can set term type if it likes */
    push_terminal(0);		/* remember the default terminal */

    /* reset the terminal when exiting */
    /* this is done through gp_atexit so that other terminal functions
     * can be registered to be executed before the terminal is reset. */
    GP_ATEXIT(term_reset);

#ifdef AMIGA_SC_6_1
    if (IsInteractive(Input()) == DOSTRUE)
	interactive = TRUE;
    else
	interactive = FALSE;
#else
# if ((defined(__MSC__) && defined(_Windows)) || defined(__WIN32__)) && ! defined(WGP_CONSOLE)
    interactive = TRUE;
# else
    interactive = isatty(fileno(stdin));
# endif
#endif /* !AMIGA_SC_6_1 */

    if (argc > 1)
	interactive = noinputfiles = FALSE;
    else
	noinputfiles = TRUE;

    /* Need this before show_version is called for the first time */

#ifdef HAVE_SYS_UTSNAME_H
    {
	struct utsname uts;

	/* something is fundamentally wrong if this fails ... */
	if (uname(&uts) > -1) {
# ifdef _AIX
	    strcpy(os_name, uts.sysname);
	    sprintf(os_name, "%s.%s", uts.version, uts.release);
# elif defined(SCO)
	    strcpy(os_name, "SCO");
	    strcpy(os_rel, uts.release);
# elif defined(DJGPP)
	    if (!strncmp(uts.sysname, "??Un", 4)) /* don't print ??Unknow" */
		strcpy(os_name, "Unknown");
	    else {
		strcpy(os_name, uts.sysname);
		strcpy(os_rel, uts.release);
	    }
# else
	    strcpy(os_name, uts.sysname);
	    strcpy(os_rel, uts.release);
# ifdef OS2
	    if (!strchr(os_rel,'.'))
		/* write either "2.40" or "4.0", or empty -- don't print "OS/2 1" */
		strcpy(os_rel, "");
# endif

# endif
	}
    }
#else /* ! HAVE_SYS_UTSNAME_H */

    strcpy(os_name, OS);
    strcpy(os_rel, "");

#endif /* HAVE_SYS_UTSNAME_H */

    if (interactive)
	show_version(stderr);
    else
	show_version(NULL); /* Only load GPVAL_COMPILE_OPTIONS */

    update_gpval_variables(3);  /* update GPVAL_ variables available to user */

#ifdef VMS
    /* initialise screen management routines for command recall */
    if (status[1] = smg$create_virtual_keyboard(&vms_vkid) != SS$_NORMAL)
	done(status[1]);
    if (status[1] = smg$create_key_table(&vms_ktid) != SS$_NORMAL)
	done(status[1]);
#endif /* VMS */

    if (!SETJMP(command_line_env, 1)) {
	/* first time */
	interrupt_setup();
	/* should move this stuff another initialisation routine,
	 * something like init_set() maybe */
	get_user_env();
	init_loadpath();
	init_locale();
	/* HBB: make sure all variables start in the same mode 'reset'
	 * would set them to. Since the axis variables aren't in
	 * initialized arrays any more, this is now necessary... */
	reset_command();
	init_color();  /*  Initialization of color  */
	load_rcfile();
	init_fit();		/* Initialization of fitting module */

	if (interactive && term != 0) {		/* not unknown */
#ifdef GNUPLOT_HISTORY
	    FPRINTF((stderr, "Before read_history\n"));
#if defined(HAVE_LIBREADLINE) || defined(HAVE_LIBEDITLINE)
	    expanded_history_filename = tilde_expand(GNUPLOT_HISTORY_FILE);
#else
	    expanded_history_filename = gp_strdup(GNUPLOT_HISTORY_FILE);
	    gp_expand_tilde(&expanded_history_filename);
#endif
	    FPRINTF((stderr, "expanded_history_filename = %s\n", expanded_history_filename));
	    read_history(expanded_history_filename);
	    {
		/* BEGIN: Go local to get environment variable */
		const char *temp_env = getenv ("GNUPLOT_HISTORY_SIZE");
		if (temp_env)
		    gnuplot_history_size = strtol (temp_env, (char **) NULL, 10);
	    } /* END: Go local to get environment variable */

	    /*
	     * It is safe to ignore the return values of 'atexit()' and
	     * 'on_exit()'. In the worst case, there is no history of your
	     * currrent session and you have to type all again in your next
	     * session.
	     * This is the default behaviour (traditional reasons), too.
	     * In case you don't have one of these functions, or you don't
	     * want to use them, 'write_history()' is called directly.
	     */
	    GP_ATEXIT(wrapper_for_write_history);
#endif /* GNUPLOT_HISTORY */

	    fprintf(stderr, "\nTerminal type set to '%s'\n", term->name);
	}			/* if (interactive && term != 0) */
    } else {
	/* come back here from int_error() */
	if (interactive == FALSE)
	    exit_status = EXIT_FAILURE;
#ifdef HAVE_LIBREADLINE
	else
	{
	    /* reset properly readline after a SIGINT+longjmp */
	    rl_reset_after_signal ();
	}
#endif

#ifdef AMIGA_SC_6_1
	(void) rawcon(0);
#endif
	load_file_error();	/* if we were in load_file(), cleanup */
	reset_eval_depth();     /* reset evaluate command recursion counter */
	SET_CURSOR_ARROW;

#ifdef VMS
	/* after catching interrupt */
	/* VAX stuffs up stdout on SIGINT while writing to stdout,
	   so reopen stdout. */
	if (gpoutfile == stdout) {
	    if ((stdout = freopen("SYS$OUTPUT", "w", stdout)) == NULL) {
		/* couldn't reopen it so try opening it instead */
		if ((stdout = fopen("SYS$OUTPUT", "w")) == NULL) {
		    /* don't use int_error here - causes infinite loop! */
		    fputs("Error opening SYS$OUTPUT as stdout\n", stderr);
		}
	    }
	    gpoutfile = stdout;
	}
#endif /* VMS */
	if (!interactive && !noinputfiles) {
	    term_reset();
	    exit(EXIT_FAILURE);	/* exit on non-interactive error */
	}
    }

    if (argc > 1) {
#ifdef _Windows
	TBOOLEAN noend = persist_cl;
#endif

	/* load filenames given as arguments */
	while (--argc > 0) {
	    ++argv;
	    c_token = NO_CARET;	/* in case of file not found */
#ifdef _Windows
	    if (stricmp(*argv, "-noend") == 0 || stricmp(*argv, "/noend") == 0
	       	|| stricmp(*argv, "-persist") == 0)
		noend = TRUE;
	    else
#endif
	    if (!strncmp(*argv, "-persist", 2) || !strcmp(*argv, "--persist")) {
		FPRINTF((stderr,"'persist' command line option recognized\n"));

	    } else if (strcmp(*argv, "-") == 0) {
		/* DBT 10-7-98  go interactive if "-" on command line */

		interactive = TRUE;
		/* will this work on all platforms? */

		while (!com_line());

		interactive = FALSE;

	    } else if (strcmp(*argv, "-e") == 0) {
		--argc; ++argv;
		if (argc <= 0) {
		    fprintf(stderr, "syntax:  gnuplot -e \"commands\"\n");
		    return 0;
		}
		do_string(*argv, FALSE);

	    } else
		load_file(loadpath_fopen(*argv, "r"), gp_strdup(*argv), FALSE);
	}
#ifdef _Windows
	if (noend) {
	    interactive = TRUE;
	    while (!com_line());
	}
#endif
    } else {
	/* take commands from stdin */
	while (!com_line());
    }

#if (defined(HAVE_LIBREADLINE) || defined(HAVE_LIBEDITLINE)) && defined(GNUPLOT_HISTORY)
#if !defined(HAVE_ATEXIT) && !defined(HAVE_ON_EXIT)
    /* You should be here if you neither have 'atexit()' nor 'on_exit()' */
    wrapper_for_write_history();
#endif /* !HAVE_ATEXIT && !HAVE_ON_EXIT */
#endif /* (HAVE_LIBREADLINE || HAVE_LIBEDITLINE) && GNUPLOT_HISTORY */

#ifdef OS2
    RexxDeregisterSubcom("GNUPLOT", NULL);
#endif

    /* HBB 20040223: Not all compilers like exit() to end main() */
    /* exit(exit_status); */
    return exit_status;
}