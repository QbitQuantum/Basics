/* Runs the host editor.  Another big use for this is to open sites
 * that are in your host list.
 */
int HostWindow(void)
{
	int c;
	char cmd[256];
	volatile BookmarkPtr toOpen;
	vsigproc_t si;
	int maxy, maxx;
	int lmaxy;

	si = (sigproc_t) (-1);
	if (gWinInit) {
		gHostListWin = NULL;
		gHostWin = NULL;

		gHostWin = newwin(LINES, COLS, 0, 0);
		if (gHostWin == NULL)
			return (-1);

		curs_set(0);
		cbreak();
		
		/* Set the clear flag for the first update. */
		wclear(gHostWin);
		keypad(gHostWin, TRUE);		/* For arrow keys. */
#ifdef HAVE_NOTIMEOUT
		notimeout(gHostWin, TRUE);
#endif

#ifdef HAVE_SIGSETJMP
		if (sigsetjmp(gHostWinJmp, 1) == 0) {
#else	/* HAVE_SIGSETJMP */
		if (setjmp(gHostWinJmp) == 0) {
#endif	/* HAVE_SIGSETJMP */
			/* Gracefully cleanup the screen if the user ^C's. */
			si = NcSignal(SIGINT, SigIntHostWin);
			
			/* Initialize the page start and select a host to be
			 * the current one.
			 */
			gHostListWinStart = 0;
			gHilitedHost = 0;
			if (gNumBookmarks == 0)
				gCurHostListItem = NULL;
			else
				gCurHostListItem = &gBookmarkTable[gHilitedHost];
			
			/* Initially, we don't want to connect to any site in
			 * the host list.
			 */
			toOpen = NULL;
	
			getmaxyx(gHostWin, maxy, maxx);
			WAttr(gHostWin, kBold, 1);
			WAddCenteredStr(gHostWin, 0, "NcFTP Bookmark Editor");
			WAttr(gHostWin, kBold, 0);
			
			DrawStrAt(gHostWin, 3, 2, "Open selected site:       <enter>");
			DrawStrAt(gHostWin, 4, 2, "Edit selected site:       /ed");
			DrawStrAt(gHostWin, 5, 2, "Delete selected site:     /del");
			DrawStrAt(gHostWin, 6, 2, "Duplicate selected site:  /dup");
			DrawStrAt(gHostWin, 7, 2, "Add a new site:           /new");
			DrawStrAt(gHostWin, 9, 2, "Up one:                   <u>");
			DrawStrAt(gHostWin, 10, 2, "Down one:                 <d>");
			DrawStrAt(gHostWin, 11, 2, "Previous page:            <p>");
			DrawStrAt(gHostWin, 12, 2, "Next page:                <n>");
			DrawStrAt(gHostWin, 14, 2, "Capital letters selects first");
			DrawStrAt(gHostWin, 15, 2, "  site starting with the letter.");
			DrawStrAt(gHostWin, 17, 2, "Exit the bookmark editor: <x>");
		
			/* Initialize the scrolling host list window. */
			if (maxx < 110) {
				gHostListWinWide = 0;
				gHostListWin = subwin(
					gHostWin,
					LINES - 7,
					40,
					3,
					COLS - 40 - 2
				);
			} else {
				gHostListWinWide = COLS - 42;
				gHostListWin = subwin(
					gHostWin,
					LINES - 7,
					gHostListWinWide,
					3,
					38	
				);
			}

			if (gHostListWin == NULL)
				return (-1);
			lmaxy = getmaxy(gHostListWin);
			gHostListPageSize = lmaxy;
			DrawHostList();
			wmove(gHostWin, maxy - 1, 0);
			UpdateHostWindows(1);

			for (;;) {
				c = HostWinGetKey();
				if (gNeedToClearMsg) {
					wmove(gHostWin, maxy - 2, 0);
					wclrtoeol(gHostWin);
					wrefresh(gHostWin);
				}
				if ((c >= 'A') && (c <= 'Z')) {
					/* isupper can coredump if wgetch returns a meta key. */
					HostWinZoomTo(c);
				} else if (c == '/') {
					/* Get an "extended" command.  Sort of like vi's
					 * :colon commands.
					 */
					HostWinGetStr(cmd, sizeof(cmd));
	
					if (ISTREQ(cmd, "ed"))
						HostWinEdit();
					else if (ISTREQ(cmd, "dup"))
						HostWinDup();
					else if (ISTREQ(cmd, "del"))
						HostWinDelete();
					else if (ISTREQ(cmd, "new"))
						HostWinNew();
					else
						HostWinMsg("Invalid bookmark editor command.");
				} else switch(c) {
					case 10:	/* ^J == newline */
						goto enter;
					case 13:	/* ^M == carriage return */
						goto enter;
#ifdef KEY_ENTER
					case KEY_ENTER:
						Trace(1, "  [0x%04X, %s]\n", c, "ENTER");
#endif
enter:
						if (gCurHostListItem == NULL)
							HostWinMsg("Nothing to open.  Try 'open sitename' from the main screen.");
						else {
							toOpen = (BookmarkPtr) gCurHostListItem;
							goto done;
						}
						break;
	
					case kControl_L:
						UpdateHostWindows(1);
						break;
	
					case 'u':
					case 'k':	/* vi up key */
					case 'h':	/* vi left key */
						HostListLineUp();
						break;
#ifdef KEY_UP
					case KEY_UP:
						Trace(1, "  [0x%04X, %s]\n", c, "UP");
						HostListLineUp();
						break;
#endif

#ifdef KEY_LEFT
					case KEY_LEFT:
						Trace(1, "  [0x%04X, %s]\n", c, "LEFT");
						HostListLineUp();
						break;
#endif
					
					case 'd':
					case 'j':	/* vi down key */
					case 'l':	/* vi right key */
						HostListLineDown();
						break;

#ifdef KEY_DOWN
					case KEY_DOWN:
						Trace(1, "  [0x%04X, %s]\n", c, "DOWN");
						HostListLineDown();
						break;
#endif

#ifdef KEY_RIGHT
					case KEY_RIGHT:
						Trace(1, "  [0x%04X, %s]\n", c, "RIGHT");
						HostListLineDown();
						break;
#endif
						
					case 'p':
						HostListPageUp();
						break;

#ifdef KEY_PPAGE
					case KEY_PPAGE:
						Trace(1, "  [0x%04X, %s]\n", c, "PPAGE");
						HostListPageUp();
						break;
#endif

					case 'n':
						HostListPageDown();
						break;

#ifdef KEY_NPAGE
					case KEY_NPAGE:
						Trace(1, "  [0x%04X, %s]\n", c, "NPAGE");
						HostListPageDown();
						break;
#endif

					case 'x':
					case 'q':
						goto done;
	
					default:
						HostWinMsg("Invalid key.");
						Trace(1, "  [0x%04X, %s]\n", c, "<invalid>");
						break;
				}
			}
		}
		NcSignal(SIGINT, (FTPSigProc) SIG_IGN);
done:
		if (gHostListWin != NULL)
			delwin(gHostListWin);
		if (gHostWin != NULL)
			delwin(gHostWin);
		gHostListWin = gHostWin = NULL;
		if (si != (sigproc_t) (-1))
			NcSignal(SIGINT, si);
		if (toOpen != (BookmarkPtr) 0) {
			/* If the user selected a site to open, connect to it now. */
			if (gStandAlone != 0) {
				LaunchNcFTP(toOpen->bookmarkName);
				/*NOTREACHED*/
				Exit(0);
			} else if (gBookmarkSelectionFile != NULL) {
				WriteSelectedBMToFile(toOpen->bookmarkName);
			}
			return (kNoErr);
		}
	}
	return (kNoErr);
}	/* HostWindow */




main_void_return_t
main(int argc, const char **argv)
{
	int result;
	int argi;

	gStandAlone = 1;
	gBookmarkSelectionFile = NULL;

	InitUserInfo();
	if (LoadBookmarkTable() < 0) {
		exit(7);
	}
	if (argc > 1) {
		/* The following hack is used by NcFTP
		 * to get the number of columns without
		 * having to link with curses/termcap.
		 * This simplifies things since the
		 * system may or may not have a good
		 * curses implementation, and we don't
		 * want to complicate NcFTP itself with
		 * that.
		 */
		argi = 1;
		if (strcmp(argv[1], "--dimensions") == 0) {
			result = PrintDimensions(0);
			exit((result == 0) ? 0 : 1);
		} else if (strcmp(argv[1], "--dimensions-terse") == 0) {
			result = PrintDimensions(1);
			exit((result == 0) ? 0 : 1);
		} else if (strcmp(argv[1], "--debug") == 0) {
			SetDebug(1);
			argi++;
		}
		/* Requested that we were run from ncftp. */
		gStandAlone = 0;
		if ((argc > argi) && (argv[argi][0] == '/'))
			gBookmarkSelectionFile = (const char *) argv[argi];
		if (gNumBookmarks < 1)
			exit(7);
	}

	result = FTPInitLibrary(&gLib);
	if (result < 0) {
		(void) fprintf(stderr, "ncftp: init library error %d (%s).\n", result, FTPStrError(result));
		exit(1);
	}

	result = FTPInitConnectionInfo(&gLib, &gConn, kDefaultFTPBufSize);
	if (result < 0) {
		(void) fprintf(stderr, "ncftp: init connection info error %d (%s).\n", result, FTPStrError(result));
		exit(1);
	}

	if (gDebug > 0)
		OpenTrace();
	InitPrefs();
	LoadFirewallPrefs(0);
	LoadPrefs();

	InitWindows();
	Trace(1, "Terminal size is %d columns by %d rows.\n", gScreenWidth, gScreenHeight);
	HostWindow();
	if (gDebug > 0)
		CloseTrace();
	EndWin();
	exit(0);
}	/* main */