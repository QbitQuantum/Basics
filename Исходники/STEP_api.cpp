PSTEPlugin STEPluginLoadFile(LPCWSTR strPluginFile) {
	HINSTANCE hLib;
	CString strPluginFolder;
	{
		wchar_t   drive[_MAX_DRIVE];
		wchar_t   dir[_MAX_DIR];
		wchar_t   buff[_MAX_PATH] = {'\0'};
		wchar_t   full[_MAX_PATH] = {'\0'};

		_tsplitpath(strPluginFile, drive, dir, NULL, NULL);
		_tmakepath_s(buff,_MAX_PATH, drive, dir, NULL, NULL);
		if (drive[0] == '\0') {
			CSuperTagEditorApp	*pApp = (CSuperTagEditorApp *)AfxGetApp();
			CString strEXE;
			{
				wchar_t*	szName = pApp->MakeFileName(L"");
				wchar_t   drive[_MAX_DRIVE];
				wchar_t   dir[_MAX_DIR];
				wchar_t   buff[_MAX_PATH] = {'\0'};
				_tsplitpath(szName, drive, dir, NULL, NULL);
				_tmakepath_s(buff,_MAX_PATH, drive, dir, L"", L"");
				strEXE = buff;
				delete szName;
			}

			wcscpy_s(full,_MAX_PATH, strEXE);
			wcscat_s(full,_MAX_PATH, dir);
			_wfullpath(buff, full, _MAX_PATH);
		}
		strPluginFolder = buff;
		wchar_t* pathvar = _wgetenv(L"PATH");
		CString strPath = L"PATH=";
		strPath = strPath + strPluginFolder + ";" + pathvar;
		_wputenv(strPath);
		hLib = LoadLibrary(strPluginFile);
		strPath = L"PATH=";
		strPath = strPath + pathvar;
		_wputenv(strPath);
		if (hLib == NULL) return NULL;
	}

	UINT (WINAPI *STEPGetAPIVersion)(void);
	bool (WINAPI *STEPInit)(UINT, LPCWSTR);
	LPCWSTR (WINAPI *STEPGetPluginName)(void);

	(FARPROC&)STEPInit = GetProcAddress(hLib, "_STEPInit@8");
	(FARPROC&)STEPGetAPIVersion = GetProcAddress(hLib, "_STEPGetAPIVersion@0");
	(FARPROC&)STEPGetPluginName = GetProcAddress(hLib, "_STEPGetPluginName@0");
	if (STEPInit == NULL || STEPGetAPIVersion == NULL || STEPGetPluginName == NULL)	return  NULL;
	if ((STEPGetAPIVersion() & 0xFFFF00) > (STEP_API_VERSION & 0xFFFF00))	return NULL; /* STEP 029 */
	PSTEPlugin pPlugin = new STEPlugin;
	pPlugin->hLib = hLib;
	pPlugin->sFileName = strPluginFile;
	pPlugin->sPluginName = STEPGetPluginName();
	(FARPROC&)pPlugin->STEPGetToolTipText = GetProcAddress(hLib, "_STEPGetToolTipText@4");
	(FARPROC&)pPlugin->STEPGetStatusMessage = GetProcAddress(hLib, "_STEPGetStatusMessage@4");
	(FARPROC&)pPlugin->STEPOnUpdateCommand = GetProcAddress(hLib, "_STEPOnUpdateCommand@4");
	(FARPROC&)pPlugin->STEPOnCommand = GetProcAddress(hLib, "_STEPOnCommand@8");
	(FARPROC&)pPlugin->STEPSupportSIF = GetProcAddress(hLib, "_STEPSupportSIF@4");
	(FARPROC&)pPlugin->STEPSupportTrackNumberSIF = GetProcAddress(hLib, "_STEPSupportTrackNumberSIF@4");
	(FARPROC&)pPlugin->STEPSupportGenreSIF = GetProcAddress(hLib, "_STEPSupportGenreSIF@4");
	(FARPROC&)pPlugin->STEPGetControlType = GetProcAddress(hLib, "_STEPGetControlType@12");
	(FARPROC&)pPlugin->STEPGetColumnMax = GetProcAddress(hLib, "_STEPGetColumnMax@12");
	(FARPROC&)pPlugin->STEPGetColumnName = GetProcAddress(hLib, "_STEPGetColumnName@8");
	(FARPROC&)pPlugin->STEPHasSpecificColumnName = GetProcAddress(hLib, "_STEPHasSpecificColumnName@4");
	(FARPROC&)pPlugin->STEPLoad = GetProcAddress(hLib, "_STEPLoad@8");
	(FARPROC&)pPlugin->STEPSave = GetProcAddress(hLib, "_STEPSave@4");
	(FARPROC&)pPlugin->STEPShowOptionDialog = GetProcAddress(hLib, "_STEPShowOptionDialog@4");
	(FARPROC&)pPlugin->STEPOnLoadMenu = GetProcAddress(hLib, "_STEPOnLoadMenu@8");
	(FARPROC&)pPlugin->STEPOnLoadMainMenu = GetProcAddress(hLib, "_STEPOnLoadMainMenu@0");
	(FARPROC&)pPlugin->STEPGetPluginInfo = GetProcAddress(hLib, "_STEPGetPluginInfo@0");
	(FARPROC&)pPlugin->STEPInitFileSpecificInfo = GetProcAddress(hLib, "_STEPInitFileSpecificInfo@4");
	(FARPROC&)pPlugin->STEPOnConvSiFieldToId3tag = GetProcAddress(hLib, "_STEPOnConvSiFieldToId3tag@4");

	plugins.arPlugins.Add(pPlugin);

	if ((*STEPInit)(plugins.arPlugins.GetSize(), strPluginFolder) == false) {
		return NULL;
	}

	return pPlugin;
}