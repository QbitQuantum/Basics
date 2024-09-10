HRESULT CMainFrame::CheckForUpdates(bool Silent)
{
	// check if internet connection is active
	if(Silent)
	{
		DWORD nFlags = 0;
		if(!InternetGetConnectedState(&nFlags, 0) || (nFlags & INTERNET_CONNECTION_OFFLINE))
		{
			return S_OK;
		}
	}


	CWaitCursor wait;
	
	CString WMEVersion;
	HRESULT Ret = GetWMEVersionHttp(WMEVersion);
	if(FAILED(Ret)){
		if(!Silent) MessageBox(LOC("/str0145/Error querying latest available version."), NULL, MB_OK|MB_ICONERROR);
		return Ret;
	}
	else{
		DWORD VerMajor = atoi(Entry(1, WMEVersion, '.'));
		DWORD VerMinor = atoi(Entry(2, WMEVersion, '.'));
		DWORD VerBuild = atoi(Entry(3, WMEVersion, '.'));

		bool UpdateAvailable = false;
		
		if(VerMajor > DCGF_VER_MAJOR) UpdateAvailable = true;
		else if(VerMajor == DCGF_VER_MAJOR && VerMinor > DCGF_VER_MINOR) UpdateAvailable = true;
		else if(VerMajor == DCGF_VER_MAJOR && VerMinor == DCGF_VER_MINOR && VerBuild > DCGF_VER_BUILD) UpdateAvailable = true;
		
		if(!UpdateAvailable){
			if(!Silent) MessageBox(LOC("/str0146/Your WME version is up to date."), NULL, MB_OK|MB_ICONINFORMATION);
		}
		else{
			if(IDYES==MessageBox(LOC("/str0147/There is an updated version of WME available. Do you want to display the download page now?"), "", MB_OK|MB_ICONQUESTION|MB_YESNO)){
				ShellExecute(NULL, "open", LOC("/str1085/http://dead-code.org/redir.php?target=updates"), NULL, NULL, SW_SHOWMAXIMIZED);
			}
		}
	}


	return Ret;
}