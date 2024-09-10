// do all the important initialization stuffz
bool InitializepreVentrilo()
{
	std::ifstream fin(strSettingsFile.c_str());
	std::string line;
	if(!std::getline(fin, line))
	{
		char *pProg;
		size_t len;
		errno_t err = _dupenv_s( &pProg, &len, "PROGRAMFILES" );
		if(!err)
		{
			settings.ventPath = pProg;
			settings.ventPath += "\\Ventrilo\\Ventrilo.exe";
			free( pProg );
		}
		else
			settings.ventPath = "";
	}
	else
		settings.ventPath = line;
	if(!(fin >> settings.pauseType))
		settings.pauseType = (PAUSE_TYPE_OTHERS | PAUSE_TYPE_SELF);
	if(!(fin >> settings.mediaPlayer))
		settings.mediaPlayer = MEDIA_PLAYER_WINAMP;
	if(!(fin >> settings.bAdjustVolume))
		settings.bAdjustVolume = true;
	if(!(fin >> settings.nAdjustedVolume))
		settings.nAdjustedVolume = 29;
	fin.close();
	SaveSettings();


	hinstDLL = LoadLibrary("prevent.dll");
	if(hinstDLL == NULL)
	{
		MessageBox(NULL, "Unable to load prevent.dll", NULL, NULL);
		return false;
	}


	pSetVentHook = (LPSetVentHook)GetProcAddress(hinstDLL, "SetVentHook");
	pKillVentHook = GetProcAddress(hinstDLL, "KillVentHook");
	pSetMediaPlayer = (LPdwhwnd)GetProcAddress(hinstDLL, "SetMediaPlayer");
	pSetMuteType = (LPSetMuteType)GetProcAddress(hinstDLL, "SetMuteType");
	if(pSetVentHook == NULL || pKillVentHook == NULL || pSetMediaPlayer == NULL || pSetMuteType == NULL)
	{
		MessageBox(NULL, "Unable to load DLL functions", NULL, NULL);
		return false;
	}


	hWndVent = FindWindow( NULL, "Ventrilo");
	if(hWndVent == NULL)
	{
		if((int)ShellExecute(NULL, "open", settings.ventPath.c_str(), "", NULL, SW_SHOWNORMAL) <= 32)
		{
			MessageBox(NULL, "Please select the Ventrilo executable.", NULL, NULL);

			OPENFILENAME ofn;
			char szFileName[MAX_PATH] = "";
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = NULL;
			ofn.lpstrFilter = "Ventrilo.exe\0Ventrilo.exe\0All Files (*.*)\0*.*\0";
			ofn.lpstrFile = szFileName;
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;
			ofn.lpstrDefExt = "exe";

			if(GetOpenFileName(&ofn))
			{
				settings.ventPath = szFileName;
				ShellExecute(NULL, "open", settings.ventPath.c_str(), "", NULL, SW_SHOWNORMAL);
			}
		}
	}

	hThreadVent = CreateThread(
				NULL,				// default security attributes
				0,					// use default stack size  
				ThreadVentProc,		// thread function 
				NULL,				// argument to thread function 
				0,					// use default creation flags 
				&dwThreadVentId);	// returns the thread identifier
	if(hThreadVent == NULL)
	{
		MessageBox(NULL, "Error.", NULL, NULL);
		return false;
	}

	OnMediaPlayer();

	return true;
}