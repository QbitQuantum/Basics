/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer
//
/////////////////////////////////////////////////////////////////////////////
STDAPI DllRegisterServer(void)
{
	HRESULT hr = E_FAIL;

	HKEY hLTMKey = NULL;
	HKEY hLTMModuleKey = NULL;
	
	HKEY hRootKey = NULL;
	HKEY hModuleKey = NULL;
	HKEY hInprocServerKey = NULL;
	HKEY hProgIDKey = NULL;
	
	WCHAR* pwszCLSID = NULL;
	GlobalModuleData* pModuleData = &g_pThisTestModule->m_gmd;
	CHAR szModuleFileName[MAX_NAME_LEN];
	CHAR szProgID[MAX_NAME_LEN];
	CHAR szModuleName[MAX_NAME_LEN];
	CHAR szGuid[MAX_NAME_LEN];

	//Unregister First
	DllUnregisterServer();
	
	//{...Guid...}
	StringFromCLSID(*pModuleData->m_pguidModuleCLSID, &pwszCLSID);
	WideCharToMultiByte(CP_ACP, 0, pwszCLSID, -1, szGuid, MAX_NAME_LEN, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, pModuleData->m_wszModuleName, -1, szModuleName, MAX_NAME_LEN, NULL, NULL);

	strcpy(szProgID, "LTMTest.");
	strcat(szProgID, szModuleName);

	// Step 1: Register our CLSID as an OLE Server
	//HKEY_CLASSES_ROOT\CLSID
	if(ERROR_SUCCESS == RegCreateKeyA(HKEY_CLASSES_ROOT, "CLSID", &hRootKey))
	{
		//HKEY_CLASSES_ROOT\CLSID\{..Guid..}
		if(ERROR_SUCCESS == RegCreateKeyA(hRootKey, szGuid, &hModuleKey))
		{
			//{Guid}\Value=ModuleName
			RegSetValueEx(hModuleKey, NULL, 0, REG_SZ, (BYTE*)szModuleName, ((DWORD)strlen(szModuleName)) * sizeof(CHAR));

			//HKEY_CLASSES_ROOT\CLSID\{..Guid..}\InprocServer32
			if(ERROR_SUCCESS == RegCreateKeyA(hModuleKey, "InprocServer32", &hInprocServerKey))
			{
				//InprocServer32\<>\FileName.dll
				GetModuleFileNameA(g_hInstance, szModuleFileName, MAX_NAME_LEN);
				RegSetValueExA(hInprocServerKey, NULL, 0, REG_SZ, (BYTE*)szModuleFileName, ((DWORD)strlen(szModuleFileName)) * sizeof(CHAR));
				
				//InprocServer32\ThreadingModel\Both
				RegSetValueExA(hInprocServerKey, "ThreadingModel", 0, REG_SZ, (BYTE*)"Both", ((DWORD)strlen("Both")) * sizeof(CHAR));
				RegCloseKey(hInprocServerKey);
				hr = S_OK;
			}

			//HKEY_CLASSES_ROOT\CLSID\{..Guid..}\ProgID
			if(ERROR_SUCCESS == RegCreateKeyA(hModuleKey, "ProgID", &hProgIDKey))
			{
				RegSetValueExA(hProgIDKey, NULL, 0, REG_SZ, (BYTE*)szProgID, ((DWORD)strlen(szProgID)) * sizeof(CHAR));
				RegCloseKey(hProgIDKey);
			}
			RegCloseKey(hModuleKey);
		}
		RegCloseKey(hRootKey);
	}


	//HKEY_CLASSES_ROOT\ProgID
	if(ERROR_SUCCESS == RegCreateKeyA(HKEY_CLASSES_ROOT, szProgID, &hRootKey))
	{
		//HKEY_CLASSES_ROOT\ProgID\CLSID
		if(ERROR_SUCCESS == RegCreateKeyA(hRootKey, "CLSID", &hModuleKey))
		{
			//ProgID\CLSID\{Guid}
			RegSetValueExA(hModuleKey, NULL, 0, REG_SZ, (BYTE*)szGuid, ((DWORD)strlen(szGuid)) * sizeof(CHAR));
			RegCloseKey(hModuleKey);
			hr = S_OK;
		}
		RegCloseKey(hRootKey);
	}
	

	//Step 2: Register our test in the LTM Test Location
	//So LTM is aware of a new test module is available for running...
	
	//Obtain the Key for HKEY_LOCAL_MACHINE\"SOFTWARE\Microsoft\LTM\Test Modules"
	if(ERROR_SUCCESS == RegCreateKeyA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\LTM\\Test Modules", &hLTMKey))
	{

		//Obtain the Key for "...\{Guid}
		if(ERROR_SUCCESS == RegCreateKeyA(hLTMKey, szGuid, &hLTMModuleKey))
		{
			//ModuleName
			RegSetValueExA(hLTMModuleKey, NULL, 0, REG_SZ, (BYTE*)szModuleName, ((DWORD)strlen(szModuleName)) * sizeof(CHAR));
		}
	}

	RegCloseKey(hLTMKey);
	RegCloseKey(hLTMModuleKey);
	CoTaskMemFree(pwszCLSID);
	return hr;
}