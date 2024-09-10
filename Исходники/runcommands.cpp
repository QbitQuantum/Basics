bool RunCommands(CCommandArray& Commands, LPCTSTR pszOrigDocName)
{
	s_bRunsCommands = true;

	char szCurDir[MAX_PATH];
	_getcwd(szCurDir, MAX_PATH);

	procWnd.GetReady();

	// cut up document name into file and extension components.
	//  create two sets of buffers - one set with the long filename
	//  and one set with the 8.3 format.

	char szDocLongPath[MAX_PATH] = {0}, szDocLongName[MAX_PATH] = {0}, 
		szDocLongExt[MAX_PATH] = {0};
	char szDocShortPath[MAX_PATH] = {0}, szDocShortName[MAX_PATH] = {0}, 
		szDocShortExt[MAX_PATH] = {0};

	GetFullPathName(pszOrigDocName, MAX_PATH, szDocLongPath, NULL);
	GetShortPathName(pszOrigDocName, szDocShortPath, MAX_PATH);

	// split them up
	char *p = strrchr(szDocLongPath, '.');
	if(p && strrchr(szDocLongPath, '\\') < p && strrchr(szDocLongPath, '/') < p)
	{
		// got the extension
		strcpy(szDocLongExt, p+1);
		p[0] = 0;
	}

	p = strrchr(szDocLongPath, '\\');
	if(!p)
		p = strrchr(szDocLongPath, '/');
	if(p)
	{
		// got the filepart
		strcpy(szDocLongName, p+1);
		p[0] = 0;
	}

	// split the short part up
	p = strrchr(szDocShortPath, '.');
	if(p && strrchr(szDocShortPath, '\\') < p && strrchr(szDocShortPath, '/') < p)
	{
		// got the extension
		strcpy(szDocShortExt, p+1);
		p[0] = 0;
	}

	p = strrchr(szDocShortPath, '\\');
	if(!p)
		p = strrchr(szDocShortPath, '/');
	if(p)
	{
		// got the filepart
		strcpy(szDocShortName, p+1);
		p[0] = 0;
	}

	int iSize = Commands.GetSize(), i = 0;
	char *ppParms[32];
	while(iSize--)
	{
		CCOMMAND &cmd = Commands[i++];

		// anything there?
		if((!cmd.szRun[0] && !cmd.iSpecialCmd) || !cmd.bEnable)
			continue;

		// set name pointers for long filenames
		pszDocExt = szDocLongExt;
		pszDocName = szDocLongName;
		pszDocPath = szDocLongPath;
		
		char szNewParms[MAX_PATH*5], szNewRun[MAX_PATH*5];

		// HACK: force the spawnv call for launching the game
		if (!Q_stricmp(cmd.szRun, "$game_exe"))
		{
			cmd.bUseProcessWnd = FALSE;
		}

		FixGameVars(cmd.szRun, szNewRun, TRUE);
		FixGameVars(cmd.szParms, szNewParms, TRUE);

		CString strTmp;
		strTmp.Format("\r\n"
			"** Executing...\r\n"
			"** Command: %s\r\n"
			"** Parameters: %s\r\n\r\n", szNewRun, szNewParms);
		procWnd.Append(strTmp);
		
		// create a parameter list (not always required)
		if(!cmd.bUseProcessWnd || cmd.iSpecialCmd)
		{
			char *p = szNewParms;
			ppParms[0] = szNewRun;
			int iArg = 1;
			BOOL bDone = FALSE;
			while(p[0])
			{
				ppParms[iArg++] = p;
				while(p[0])
				{
					if(p[0] == ' ')
					{
						// found a space-separator
						p[0] = 0;

						p++;

						// skip remaining white space
						while (*p == ' ')
							p++;

						break;
					}

					// found the beginning of a quoted parameters
					if(p[0] == '\"')
					{
						while(1)
						{
							p++;
							if(p[0] == '\"')
							{
								// found the end
								if(p[1] == 0)
									bDone = TRUE;
								p[1] = 0;	// kick its ass
								p += 2;

								// skip remaining white space
								while (*p == ' ')
									p++;

								break;
							}
						}
						break;
					}

					// else advance p
					++p;
				}

				if(!p[0] || bDone)
					break;	// done.
			}

			ppParms[iArg] = NULL;

			if(cmd.iSpecialCmd)
			{
				BOOL bError = FALSE;
				LPCTSTR pszError = "";

				if(cmd.iSpecialCmd == CCCopyFile && iArg == 3)
				{
					RemoveQuotes(ppParms[1]);
					RemoveQuotes(ppParms[2]);
					
					// don't copy if we're already there
					if (stricmp(ppParms[1], ppParms[2]) && 					
							(!CopyFile(ppParms[1], ppParms[2], FALSE)))
					{
						bError = TRUE;
						pszError = GetErrorString();
					}
				}
				else if(cmd.iSpecialCmd == CCDelFile && iArg == 2)
				{
					RemoveQuotes(ppParms[1]);
					if(!DeleteFile(ppParms[1]))
					{
						bError = TRUE;
						pszError = GetErrorString();
					}
				}
				else if(cmd.iSpecialCmd == CCRenameFile && iArg == 3)
				{
					RemoveQuotes(ppParms[1]);
					RemoveQuotes(ppParms[2]);
					if(rename(ppParms[1], ppParms[2]))
					{
						bError = TRUE;
						pszError = strerror(errno);
					}
				}
				else if(cmd.iSpecialCmd == CCChangeDir && iArg == 2)
				{
					RemoveQuotes(ppParms[1]);
					if(mychdir(ppParms[1]) == -1)
					{
						bError = TRUE;
						pszError = strerror(errno);
					}
				}

				if(bError)
				{
					CString str;
					str.Format("The command failed. Windows reported the error:\r\n"
						"  \"%s\"\r\n", pszError);
					procWnd.Append(str);
					procWnd.SetForegroundWindow();
					str += "\r\nDo you want to continue?";
					if(AfxMessageBox(str, MB_YESNO) == IDNO)
						break;
				}
			}
			else
			{
				// Change to the game exe folder before spawning the engine.
				// This is necessary for Steam to find the correct Steam DLL (it
				// uses the current working directory to search).
				char szDir[MAX_PATH];
				Q_strncpy(szDir, szNewRun, sizeof(szDir));
				Q_StripFilename(szDir);

				mychdir(szDir);

				// YWB Force asynchronous operation so that engine doesn't hang on
				//  exit???  Seems to work.
				// spawnv doesn't like quotes
				RemoveQuotes(szNewRun);
				_spawnv(/*cmd.bNoWait ?*/ _P_NOWAIT /*: P_WAIT*/, szNewRun, 
					(const char *const *)ppParms);
			}
		}
		else
		{
			procWnd.Execute(szNewRun, szNewParms);
		}

		// check for existence?
		if(cmd.bEnsureCheck)
		{
			char szFile[MAX_PATH];
			FixGameVars(cmd.szEnsureFn, szFile, FALSE);
			if(GetFileAttributes(szFile) == 0xFFFFFFFF)
			{
				// not there!
				CString str;
				str.Format("The file '%s' was not built.\n"
					"Do you want to continue?", szFile);
				procWnd.SetForegroundWindow();
				if(AfxMessageBox(str, MB_YESNO) == IDNO)
					break;	// outta here
			}
		}
	}

	mychdir(szCurDir);

	s_bRunsCommands = false;

	return TRUE;
}