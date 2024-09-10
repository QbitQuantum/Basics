void CLibraryAccess::VerifyTrust(const char *module, bool must_exist)
{
	TCHAR szModule[MAX_PATH];
	// For some reason VS2005 compiles this wrong, so you get a call to cvs::wide(NULL)
	// HMODULE hModule = GetModuleHandle(module?cvs::wide(module):NULL);
	HMODULE hModule;
	if(module)
		hModule = GetModuleHandle(cvs::wide(module));
	else
		hModule = GetModuleHandle(NULL);

	if(!hModule && module)
	{
		if(!SearchPath(NULL,cvs::wide(module),_T(".dll"),sizeof(szModule)/sizeof(szModule[0]),szModule,NULL))
		{
			if(must_exist)
			{
				CServerIo::error("Unable to find %s - aborting",module);
				exit(-1);
				abort();
			}
			return;
		}
	}
	else
		GetModuleFileName(hModule,szModule,sizeof(szModule));

	WINTRUST_FILE_INFO FileData = {sizeof(WINTRUST_FILE_INFO)};
	WINTRUST_DATA WinTrustData = {sizeof(WINTRUST_DATA)};
    FileData.pcwszFilePath = szModule;

    GUID WVTPolicyGUID = WINTRUST_ACTION_GENERIC_VERIFY_V2;

    WinTrustData.dwUIChoice = WTD_UI_NONE;
    WinTrustData.dwUnionChoice = WTD_CHOICE_FILE;
    WinTrustData.dwProvFlags = WTD_SAFER_FLAG;
    WinTrustData.pFile = &FileData;

    DWORD dwTrustErr = WinVerifyTrust(NULL, &WVTPolicyGUID, &WinTrustData);
	if(dwTrustErr)
	{
		if(dwTrustErr==TRUST_E_NOSIGNATURE)
		{
#ifdef COMMERCIAL_RELEASE
			CServerIo::error("Executable file '%s' trust verification failed - executable image not signed\n",(const char *)cvs::narrow(szModule));
#else
			CServerIo::trace(1,"Executable file '%s' trust verification failed - executable image not signed\n",(const char *)cvs::narrow(szModule));
			return;
#endif
		}
		else if(dwTrustErr==TRUST_E_SUBJECT_NOT_TRUSTED)
			CServerIo::error("Executable file '%s' trust verification failed - invalid signature\n",(const char *)cvs::narrow(szModule));
		else
			CServerIo::error("Executable file '%s' trust verification failed - error %08x\n",(const char *)cvs::narrow(szModule),GetLastError());
		exit(-1);
		abort();
	}
}