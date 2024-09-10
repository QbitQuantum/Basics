int main(int argc, char **argv)
{
    /* For select(2). */
    struct timeval tv;
    fd_set in;
    /* For parsing arguments. */
    char *cp;
    /* The key read in. */
    char c;

    get_options();
    /*
     * Parse arguments.
     */
    argv++;
    while (*argv) {
	cp = *argv++;
	while (*cp) {
	    switch (*cp) {
	      case 'd':
	        if (cp[1]) {
		    if (sscanf(++cp, "%f", &Sleeptime) != 1) {
			fprintf(stderr, PROGNAME ": Bad delay time `%s'\n", cp);
			exit(1);
		    }
		    goto breakargv;
		} else if (*argv) { /* last char in an argv, use next as arg */
		    if (sscanf(cp = *argv++, "%f", &Sleeptime) != 1) {
			fprintf(stderr, PROGNAME ": Bad delay time `%s'\n", cp);
			exit(1);
		    }
		    goto breakargv;
		} else {
		    fprintf(stderr, "-d requires an argument\n");
		    exit(1);
		}
		break;
	      case 'q':
		if (!getuid())
		    /* set priority to -10 in order to stay above kswapd */
		    if (setpriority(PRIO_PROCESS, getpid(), -10)) {
			/* We check this just for paranoia.  It's not
			   fatal, and shouldn't happen. */
			perror(PROGNAME ": setpriority() failed");
		    }
		Sleeptime = 0;
		break;
	      case 'c':
	        show_cmd = !show_cmd;
		break;
	      case 'S':
		Cumulative = 1;
		break;
	      case 'i':
		Noidle = 1;
		break;
	      case 's':
		Secure = 1;
		break;
	      case '-':
		break;		/* Just ignore it */
#if defined (SHOWFLAG)
              case '/': showall++;
#endif
	      default:
		fprintf(stderr, PROGNAME ": Unknown argument `%c'\n", *cp);
		exit(1);
	    }
	    cp++;
	}
    breakargv:
    }
    
    /* set to PCPU sorting */
    register_sort_function( -1, (cmp_t)pcpu_sort);
    
    /* for correct handling of some fields, we have to do distinguish 
  * between kernel versions */
    set_linux_version();
    /* get kernel symbol table, if needed */
    if (!CL_wchan_nout) {
	if (open_psdb()) {
	    CL_wchan_nout = 1;
	} else {
	    psdbsucc = 1;
	}
    }

    setup_terminal();
    window_size();
    /*
     * calculate header size, length of cmdline field ...
     */
    Numfields = make_header();
    /*
     * Set up signal handlers.
     */
    signal(SIGHUP, (void *) (int) end);
    signal(SIGINT, (void *) (int) end);
    signal(SIGQUIT, (void *) (int) end);
    signal(SIGTSTP, (void *) (int) stop);
    signal(SIGWINCH, (void *) (int) window_size);

    /* loop, collecting process info and sleeping */
    while (1) {
	if (setjmp(redraw_jmp))
	    clear_screen();

	/* display the tasks */
	show_procs();
	/* sleep & wait for keyboard input */
	tv.tv_sec = Sleeptime;
	tv.tv_usec = (Sleeptime - (int) Sleeptime) * 1000000;
	FD_ZERO(&in);
	FD_SET(0, &in);
	if (select(16, &in, 0, 0, &tv) > 0 && read(0, &c, 1) == 1)
	    do_key(c);
    }
}

/*#######################################################################
 *#### Signal handled routines: error_end, end, stop, window_size     ###
 *#### Small utilities: make_header, getstr, getint, getfloat, getsig ###
 *#######################################################################
 */


	/*
	 *  end when exiting with an error.
	 */
void error_end(int rno)
{
    if (psdbsucc)
        close_psdb();
    ioctl(0, TCSETAF, &Savetty);
    PUTP(tgoto(cm, 0, Lines - 1));
    fputs("\r\n", stdout);
    exit(rno);
}
/*
	 * Normal end of execution.
	 */
void end(void)
{
    if (psdbsucc)
	close_psdb();
    ioctl(0, TCSETAF, &Savetty);
    PUTP(tgoto(cm, 0, Lines - 1));
    fputs("\r\n", stdout);
    exit(0);
}

/*
	 * SIGTSTP catcher.
	 */
void stop(void)
{
    /* Reset terminal. */
    if (psdbsucc)
	close_psdb();
    ioctl(0, TCSETAF, &Savetty);
    PUTP(tgoto(cm, 0, Lines - 3));
    fflush(stdout);
    raise(SIGTSTP);
    /* Later... */
    ioctl(0, TCSETAF, &Rawtty);
    signal(SIGTSTP, (void *) (int) stop);
    longjmp(redraw_jmp, 1);
}

/*
       * Reads the window size and clear the window.  This is called on setup,
       * and also catches SIGWINCHs, and adjusts Maxlines.  Basically, this is
       * the central place for window size stuff.
       */
void window_size(void)
{
    struct winsize ws;

    if (ioctl(1, TIOCGWINSZ, &ws) != -1) {
	Cols = ws.ws_col;
	Lines = ws.ws_row;
    } else {
	Cols = tgetnum("co");
	Lines = tgetnum("li");
    }
    clear_screen();
}
/*
       * this adjusts the lines needed for the header to the current value
       */
int make_header(void)
{
    int i, j;

    j = 0;
    for (i = 0; i < strlen(Fields); i++) {
	if (isupper(Fields[i])) {
	    pflags[j++] = Fields[i] - 'A';
	}
    }
    strcpy(Header, "");
    for (i = 0; i < j; i++)
	strcat(Header, headers[pflags[i]]);
    /* readjust window size ... */
    Maxcmd = Cols - strlen(Header) + 7;
    Maxlines = Display_procs ? Display_procs : Lines - header_lines;
    if (Maxlines > Lines - header_lines)
	Maxlines = Lines - header_lines;
    return (j);
}