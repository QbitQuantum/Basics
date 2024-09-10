void GetCallingAppVerInfo( char *AppTitle, char *AppVer, char *AppIni,
			  BOOL *VSflag)
{
	char CallerFilename[_MAX_PATH];
	LONG *lpLangInfo;
	DWORD hVersionInfoID, size;
	GLOBALHANDLE hVersionInfo;
	LPSTR lpVersionInfo;
	int dumint, retval;
	char *cp;
	char *revAppTitle;
	char szVerQ[90];
	LPBYTE locAppTitle;
	LPBYTE locAppVer;
	char locAppIni[_MAX_PATH];
#ifndef _WIN32
	WORD wStackSeg;
#endif /* !_WIN32 */

	/* first we need to get the calling module's filename */
#ifndef _WIN32
	_asm {
		mov wStackSeg, ss
	};
	retval = GetModuleFileName((HMODULE)wStackSeg, CallerFilename,
		_MAX_PATH);
#else
	/*
	 * Note: this may only work for single threaded applications,
	 * we'll live and learn ...
	 */
        retval = GetModuleFileName( NULL, CallerFilename, _MAX_PATH);
#endif

	if ( retval == 0 ) {
		VSflag = FALSE;
		return;
	}

	size = GetFileVersionInfoSize( CallerFilename, &hVersionInfoID);

	if( size == 0 ) {
		/*
		 * hey , I bet we don't have a version resource, let's
		 * punt
		 */
#if 0
		/* let's see what we have? (1813 means no resource) */
		size = GetLastError(); 		/*  WIN32 only */
#endif
		*VSflag = FALSE;
		return;
	}

	hVersionInfo = GlobalAlloc(GHND, size);
	lpVersionInfo = GlobalLock(hVersionInfo);

	retval = GetFileVersionInfo( CallerFilename, hVersionInfoID, size,
				    lpVersionInfo);

	retval = VerQueryValue(lpVersionInfo, "\\VarFileInfo\\Translation",
			       (LPSTR *)&lpLangInfo, &dumint);
	wsprintf(szVerQ,
		 "\\StringFileInfo\\%04x%04x\\",
		 LOWORD(*lpLangInfo), HIWORD(*lpLangInfo));
	
	cp = szVerQ + lstrlen(szVerQ);

	lstrcpy(cp, "ProductName");


	/* try a localAppTitle and then a strcpy 4/2/97 */

	locAppTitle = 0;
	locAppVer = 0;

	retval = VerQueryValue(lpVersionInfo, szVerQ, &locAppTitle,
			       &dumint);

	lstrcpy(cp, "ProductVersion");


	retval = VerQueryValue(lpVersionInfo, szVerQ, &locAppVer,
			       &dumint);

	if (!locAppTitle || !locAppVer) {
	  	/* Punt, we don't have the right version resource records */
		*VSflag = FALSE;
		return;
	}

	/*
	 * We don't have a way to determine that INI file of the
	 * application at the moment so let's just use krb5.ini
	 */
	strncpy( locAppIni, KERBEROS_INI, sizeof(locAppIni) - 1 );
	locAppIni[ sizeof(locAppIni) - 1 ] = '\0';

	strncpy( AppTitle, locAppTitle, APPVERINFO_SIZE);
	AppTitle[APPVERINFO_SIZE - 1] = '\0';
	strncpy( AppVer, locAppVer, APPVERINFO_SIZE);
	AppVer[APPVERINFO_SIZE - 1] = '\0';
	strncpy( AppIni, locAppIni, APPVERINFO_SIZE);
	AppIni[APPVERINFO_SIZE - 1] = '\0';

	/*
	 * We also need to determine if we want to suppress version
	 * checking of this application.  Does the tail of the
	 * AppTitle end in a "-v" ?
	 */
	revAppTitle = _strrev( _strdup(AppTitle));
	if( revAppTitle[0] == 'v' || revAppTitle[0] == 'V'  &&
	   revAppTitle[1] == '-' ) {
		VSflag = FALSE;
	}
	return;
}