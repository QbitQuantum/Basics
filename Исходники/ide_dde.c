BOOL StartUpDDE ( HWND hWnd )
  {
	extern FARPROC lpDDEProc;
	extern HSZ hSZService;
	extern HSZ hSZItem;
	extern DWORD idInst;
	extern HCONV hConv;

	HMENU hMenu = GetMenu ( hWnd );
	BOOL RtnValue = TRUE;
	UINT Flags = ( MF_BYCOMMAND | MF_ENABLED );

	/*--------------------------------+
	| Setup Client Editor Application |
	+--------------------------------*/

	lpDDEProc = (FARPROC) DDECallBack;

	if ( DdeInitialize ((LPDWORD) &idInst,
							  (PFNCALLBACK)lpDDEProc,
							  APPCMD_CLIENTONLY,0L) )
	  {
		Flags = ( MF_BYCOMMAND | MF_GRAYED);
		RtnValue = FALSE;
		MessageBeep ( 0 );
		MessageBox (NULL,"Can not Initialize DDEML",
		"DDEML ERROR", MB_ICONSTOP | MB_TASKMODAL );
	  }

	else
	  {
		/*----------------------------+
		| Check if CLIPS is available |
		+----------------------------*/

		HSZ hSZTopic = DdeCreateStringHandle ( idInst, "LOAD",    CP_WINANSI );
		hSZItem      = DdeCreateStringHandle ( idInst, "DDEData", CP_WINANSI );
		hSZService   = DdeCreateStringHandle ( idInst, "CLIPS",   CP_WINANSI );

		hConv = DdeConnect ( idInst, hSZService, hSZTopic, (PCONVCONTEXT)NULL);
		if ( hConv == NULL )
		  {
			Flags = ( MF_BYCOMMAND | MF_GRAYED);
			RtnValue = FALSE;
		  }
		else
		  { DdeDisconnect ( hConv ); }
		DdeFreeStringHandle ( idInst, hSZTopic );
	  }

	EnableMenuItem( hMenu, IDM_EDIT_COMPLETE, Flags);
	EnableMenuItem( hMenu, IDM_HELP_COMPLETE, Flags);
	EnableMenuItem( hMenu, IDM_BUFFER_LOAD,   Flags);
	EnableMenuItem( hMenu, IDM_BUFFER_LBUF,   Flags);
	EnableMenuItem( hMenu, IDM_BUFFER_BATCH,  Flags);

	return ( RtnValue );
  }