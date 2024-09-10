BOOL CFUMApp::InitInstance()
{
	
	
	
	

#ifdef _AFXDLL
	Enable3dControls();			
#else
	Enable3dControlsStatic();	
#endif

	
	
	
	SetRegistryKey (_T("FreeDownloadManager.ORG"));

	CoInitialize (NULL);

	BOOL bNeedRegisterServer = FALSE;

	m_strAppPath = GetProfileString ("", "Path", "");

	if (m_strAppPath.IsEmpty () == FALSE)
	{
		if (m_strAppPath.Right (1) != "\\")
			m_strAppPath += "\\";
		if (GetFileAttributes (m_strAppPath + "fum.exe") == DWORD (-1))
		{
			bNeedRegisterServer = TRUE;
			m_strAppPath = "";
		}
	}

	if (m_strAppPath.IsEmpty ())
	{
		char sz [MAX_PATH];
		GetModuleFileName (NULL, sz, MAX_PATH);
		strrchr (sz, '\\') [1] = 0;
		WriteProfileString ("", "Path", sz);
		m_strAppPath = sz;
	}
	
	SetCurrentDirectory (m_strAppPath);

	if (strcmp (m_lpCmdLine, "-duis") == 0 && FALSE == IsRecentlyInstalledFumLaunched ())
		return FALSE;

	#ifndef _DEBUG
	if (MakeSureRecentlyInstalledFumLaunched () == FALSE)
		return FALSE;
	#endif

	InitLanguage ();

	if (strcmp (m_lpCmdLine, "-suis") == 0 ||
			strcmp (m_lpCmdLine, "-euis") == 0 ||
			strcmp (m_lpCmdLine, "-duis") == 0)
	{
		IntegrationSettings ();
		return FALSE;
	}

	if (lstrcmpi (m_lpCmdLine, "-shui") == 0)
	{
		HANDLE h = CreateEvent (NULL, TRUE, FALSE, "fum - oe - injapp");
		SetEvent (h);
		CloseHandle (h);
		return FALSE;
	}

	if (lstrcmpi (m_lpCmdLine, "-stui") == 0)
	{
		ShellExecute (0, "open", vmsGetAppFolder () + "fumoei.exe", 0, 0, SW_SHOW);
		return FALSE;
	}

	CString strUpdateFile = AfxGetApp ()->GetProfileString ("Update", "UpdateFile", "");
	if (strUpdateFile.IsEmpty () == FALSE)
	{
		AfxGetApp ()->WriteProfileString ("Update", "UpdateFile", "");
		m_hAppMutex = CreateMutex (NULL, TRUE, _pszAppMutex);
		if (FALSE == CDlgUpdate::StartUpdater (strUpdateFile))
		{
			DeleteFile (strUpdateFile);
			CloseHandle (m_hAppMutex);
		}
		else
		{
			return FALSE;
		}
	}

	
	char sz [MAX_PATH];
	fsGetSystemAppDataFolder (sz);
	CString str = sz; str += "Free Upload Manager\\uploads.sav";
	MoveFile (str, fsGetDataFilePath ("uploads.2.sav"));
	

	
	
	str = sz; str += "Free Upload Manager\\";
	if (str != fsGetAppDataFolder ())
	{
		CFileFind f; 
		BOOL b = f.FindFile (str + "uploads.?.sav");
		std::vector <CString> v;
		while (b)
		{
			b = f.FindNextFile ();
			v.push_back (f.GetFilePath ());
		}
		CString str2 = fsGetAppDataFolder ();
		for (size_t i = 0; i < v.size (); i++)
		{
			for (int j = 1, i = 0; j < 10 && i < (int)v.size (); j++)
			{
				CString str2; 
				str2.Format ("%suploads.%d.sav", fsGetAppDataFolder (), j);
				if (GetFileAttributes (str2) == DWORD (-1))
					MoveFile (v [i++], str2);
			}
		}
	}

	if (!InitATL())
		return FALSE;

	if (bNeedRegisterServer)
		RegisterServer ();

	AfxEnableControlContainer();

	

	
	

	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;

	

	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);

	_App.View_ReadWndPlacement (pFrame, "MainFrm");

	
	if (_tcscmp (m_lpCmdLine, _T ("-autorun")) == 0)
		pFrame->ShowWindow (SW_HIDE);	
	else if (_App.Prg_StartMinimized ())
	{
		if (IsWindowVisible (pFrame->m_hWnd))
			pFrame->ShowWindow (SW_MINIMIZE);
	}
	else
	{
		pFrame->UpdateWindow();
		if (pFrame->IsWindowVisible ())
			pFrame->SetForegroundWindow ();
	}

	return TRUE;
}