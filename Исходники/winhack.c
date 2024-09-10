int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	INITCOMMONCONTROLSEX InitCtrls;
	int argc;
	char* argv[MAX_CMDLINE_PARAM];
	size_t len;
	TCHAR *p;
	TCHAR wbuf[BUFSZ];
	char buf[BUFSZ];
    DWORD major, minor;


	/* ensure that we don't access violate on a panic() */
	windowprocs.win_raw_print = mswin_raw_print;
	windowprocs.win_raw_print_bold = mswin_raw_print_bold;

	/* init applicatio structure */
	_nethack_app.hApp = hInstance;
	_nethack_app.hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_NETHACKW);
	_nethack_app.hMainWnd = NULL;
	_nethack_app.hPopupWnd = NULL;
	_nethack_app.bmpTiles = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_TILES));
	if( _nethack_app.bmpTiles==NULL ) panic("cannot load tiles bitmap");
	_nethack_app.bmpPetMark = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_PETMARK));
	if( _nethack_app.bmpPetMark==NULL ) panic("cannot load pet mark bitmap");
	_nethack_app.bmpRip = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_RIP));
	if ( _nethack_app.bmpRip == NULL ) panic("cannot load rip bitmap");
	_nethack_app.bmpSplash = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_SPLASH));
	if ( _nethack_app.bmpSplash == NULL ) panic("cannot load splash bitmap");
	_nethack_app.bmpMapTiles = _nethack_app.bmpTiles;
	_nethack_app.mapTile_X = TILE_X;
	_nethack_app.mapTile_Y = TILE_Y;
	_nethack_app.mapTilesPerLine = TILES_PER_LINE;

	_nethack_app.bNoHScroll = FALSE;
	_nethack_app.bNoVScroll = FALSE;
	_nethack_app.saved_text = strdup("");

    // init controls
    if (FAILED(GetComCtlVersion(&major, &minor)))
    {
        char buf[TBUFSZ];
        Sprintf(buf, "Cannot load common control library.\n%s\n%s",
              "For further information, refer to the installation notes at",
		INSTALL_NOTES);
        panic(buf);
    }
    if (major < MIN_COMCTLMAJOR
        || (major == MIN_COMCTLMAJOR && minor < MIN_COMCTLMINOR))
    {
        char buf[TBUFSZ];
        Sprintf(buf, "Common control library is outdated.\n%s %d.%d\n%s\n%s",
              "NetHack requires at least version ",
	      MIN_COMCTLMAJOR, MIN_COMCTLMINOR,
	      "For further information, refer to the installation notes at",
		INSTALL_NOTES);
        panic(buf);
    }
	ZeroMemory(&InitCtrls, sizeof(InitCtrls));
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_LISTVIEW_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	
	/* get command line parameters */	
	p = _get_cmd_arg(GetCommandLine());
	p = _get_cmd_arg(NULL); /* skip first paramter - command name */
	for( argc = 1; p && argc<MAX_CMDLINE_PARAM; argc++ ) {
		len = _tcslen(p);
		if( len>0 ) {
			argv[argc] = _strdup( NH_W2A(p, buf, BUFSZ) );
		} else {
			argv[argc] = "";
		}
		p = _get_cmd_arg(NULL);
	}
	GetModuleFileName(NULL, wbuf, BUFSZ);
	argv[0] = _strdup(NH_W2A(wbuf, buf, BUFSZ));

    if (argc == 2) {
	    TCHAR *savefile = strdup(argv[1]);
	    TCHAR *plname;
        for (p = savefile; *p && *p != '-'; p++)
            ;
        if (*p) {
            /* we found a '-' */
            plname = p + 1;
            for (p = plname; *p && *p != '.'; p++)
                ;
            if (*p) {
                if (strcmp(p + 1, "NetHack-saved-game") == 0) {
                    *p = '\0';
                    argv[1] = "-u";
                    argv[2] = _strdup(plname);
                    argc = 3;
                }
            }
        }
        free(savefile);
    }
	pcmain(argc,argv);

	moveloop();

	return 0;
}