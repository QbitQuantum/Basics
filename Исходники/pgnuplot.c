int
main (int argc, char *argv[])
{
    char    psBuffer[BUFFER_SIZE];
    char    psGnuplotCommandLine[MAX_PATH] = PROGNAME;
    LPTSTR  psCmdLine;
    BOOL    bSuccess;
    BOOL    bPersist = FALSE;
    int	i;

#if !defined(_O_BINARY) && defined(O_BINARY)
# define _O_BINARY O_BINARY
# define _setmode setmode /* this is for BC4.5 ... */
#endif
    _setmode(fileno(stdout), _O_BINARY);

    for (i = 1; i < argc; i++) {
	if (!argv[i])
	    continue;
	if (!strcmp(argv[i], "-V") || !strcmp(argv[i], "--version")) {
	    printf("gnuplot %s patchlevel %s\n",
		   gnuplot_version, gnuplot_patchlevel);
	    return 0;
	} else if ((!stricmp(argv[i], "-noend")) || (!stricmp(argv[i], "/noend")) || 
		   (!stricmp(argv[i], "-persist"))) {
	    bPersist = TRUE;
	} else if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
	    printf("Usage: gnuplot [OPTION] [FILE] [-]\n"
		    "  -V, --version   show gnuplot version\n"
		    "  -h, --help      show this help\n"
		    "  -persist        don't close the plot after executing FILE\n"
		    "  -noend, /noend  like -persist (non-portable Windows-only options)\n"
		    "  -               allow work in interactive mode after executing FILE\n"
		    "Only on Windows, -persist and - have the same effect.\n"
		    "This is gnuplot %s patchlevel %s\n"
		    "Report bugs to <*****@*****.**>\n",
		    gnuplot_version, gnuplot_patchlevel);
	    return 0;
	}
    } /* for(argc) */

    /* CRS: create the new command line, passing all of the command
     * line options to wgnuplot so that it can process them:
     * first, get the command line,
     * then move past the name of the program (e.g., 'pgnuplot'),
     * finally, add what's left of the line onto the gnuplot command line. */
    psCmdLine = GetCommandLine();

#ifdef SHOWCMDLINE
    fprintf(stderr,"CmdLine: %s\n", psCmdLine);
    fprintf(stderr,"argv[0]: %s\n",argv[0]);
#endif

    /* CRS 30061999: Search for the first unquoted space. This should
       separate the program name from the arguments. */
    psCmdLine = FindUnquotedSpace(psCmdLine);

    strncat(psGnuplotCommandLine, psCmdLine, MAX_PATH - strlen(psGnuplotCommandLine));

#ifdef SHOWCMDLINE
    fprintf(stderr,"Arguments: %s\n", psCmdLine);
    fprintf(stderr,"GnuplotCommandLine: %s\n",psGnuplotCommandLine);
#endif

    /* CRS: if stdin isn't redirected then just launch wgnuplot normally
     * and exit. */
    if (isatty(fileno(stdin))) {
	if (WinExec(psGnuplotCommandLine, SW_SHOWDEFAULT) > 31) {
	    exit(EXIT_SUCCESS);
	}
	fprintf(stderr,"ERROR %u: Couldn't execute: \"%s\"\n",
		GetLastError(), psGnuplotCommandLine);
	exit(EXIT_FAILURE);
    }

    /* CRS: initialize the STARTUPINFO and call CreateProcess(). */
    siStartInfo.cb = sizeof(STARTUPINFO);
    siStartInfo.lpReserved = NULL;
    siStartInfo.lpReserved2 = NULL;
    siStartInfo.cbReserved2 = 0;
    siStartInfo.lpDesktop = NULL;
    siStartInfo.dwFlags = STARTF_USESHOWWINDOW;
    siStartInfo.wShowWindow = SW_SHOWMINIMIZED;

    bSuccess = CreateProcess(
			     NULL,                   /* pointer to name of executable module   */
			     psGnuplotCommandLine,   /* pointer to command line string         */
			     NULL,                   /* pointer to process security attributes */
			     NULL,                   /* pointer to thread security attributes  */
			     FALSE,                  /* handle inheritance flag                */
			     0,                      /* creation flags                         */
			     NULL,                   /* pointer to new environment block       */
			     NULL,                   /* pointer to current directory name      */
			     &siStartInfo,           /* pointer to STARTUPINFO                 */
			     &piProcInfo             /* pointer to PROCESS_INFORMATION         */
			     );

    /* if CreateProcess() failed, print a warning and exit. */
    if (! bSuccess) {
	fprintf(stderr,"ERROR %u: Couldn't execute: \"%s\"\n",
		GetLastError(), psGnuplotCommandLine);
	exit(EXIT_FAILURE);
    }

    /* CRS: give gnuplot enough time to start (1 sec.) */
    if (WaitForInputIdle(piProcInfo.hProcess, 1000)) {
	fprintf(stderr, "Timeout: gnuplot is not ready\n");
	exit(EXIT_FAILURE);
    }

    /* CRS: get the HWND of the parent window and text windows */
    EnumThreadWindows(piProcInfo.dwThreadId, cbGetTextWindow, 0);

    /* CRS: free the process and thread handles */
    CloseHandle(piProcInfo.hProcess);
    CloseHandle(piProcInfo.hThread);

    if (! hwndParent || ! hwndText) {
	/* Still no gnuplot window? Problem! */
	fprintf(stderr, "Can't find the gnuplot window");
	exit(EXIT_FAILURE);
    }

    /* wait for commands on stdin, and pass them on to the wgnuplot text
     * window */
    while (fgets(psBuffer, BUFFER_SIZE, stdin) != NULL) {
	PostString(hwndText, psBuffer);
    }

    /* exit gracefully, unless -persist is requested */
    if (!bPersist) {
	/* CRS: Add a test to see if gnuplot is still running? */
	PostString(hwndText, "\nexit\n");
    }

    return EXIT_SUCCESS;
}