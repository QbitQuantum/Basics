void simVerifyTrust(const TCHAR *module, bool must_exist)
{
	TCHAR szModule[MAX_PATH];
	// For some reason VS2005 compiles this wrong, so you get a call to cvs::wide(NULL)
	// HMODULE hModule = GetModuleHandle(module?cvs::wide(module):NULL);
	HMODULE hModule;
	if(module)
		hModule = GetModuleHandle(module);
	else
		hModule = GetModuleHandle(NULL);

	if(!hModule && module)
	{
		if(!SearchPath(NULL,module,_T(".dll"),sizeof(szModule)/sizeof(szModule[0]),szModule,NULL))
		{
			if(must_exist)
			{
				printf("Unable to find %S  - aborting\n",module);
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
    WinTrustData.dwProvFlags = WTD_SAFER_FLAG | WTD_REVOCATION_CHECK_NONE | WTD_CACHE_ONLY_URL_RETRIEVAL;
    WinTrustData.pFile = &FileData;
	WinTrustData.fdwRevocationChecks = WTD_REVOKE_NONE;

    DWORD dwTrustErr = WinVerifyTrust(NULL, &WVTPolicyGUID, &WinTrustData);
	if(dwTrustErr)
	{
		if(dwTrustErr==TRUST_E_NOSIGNATURE)
		{
#ifdef COMMERCIAL_RELEASE
			printf("Trust verification failed for '%S' - image not signed\n",szModule);
#else
			printf("Trust verification failed for '%S' - community image file image not signed\n",szModule);
			return;
#endif
		}
		else if(dwTrustErr==TRUST_E_SUBJECT_NOT_TRUSTED)
			printf("Trust verification failed for '%S' - invalid signature\n",szModule);
		else
			printf("Trust verification failed for '%S' - error %08x\n",szModule,GetLastError());
		exit(-1);
		abort();
	}
}