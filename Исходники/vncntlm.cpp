int CheckUserGroupPasswordUni2(char * userin,char *password,const char *machine)
{
	int result=0;
	BOOL NT4OS=false;
	BOOL W2KOS=false;
	char clientname[256];
	strcpy_s(clientname,256,machine);
	if (!CheckNetapi95() && !CheckNetApiNT())
	{
		return false;
	}
	OSVERSIONINFO VerInfo;
	VerInfo.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
	if (!GetVersionEx (&VerInfo))   // If this fails, something has gone wrong
		{
		  return FALSE;
		}
	if (VerInfo.dwPlatformId == VER_PLATFORM_WIN32_NT && VerInfo.dwMajorVersion == 4)
		{
			NT4OS=true;
		}
	if (VerInfo.dwPlatformId == VER_PLATFORM_WIN32_NT && VerInfo.dwMajorVersion >= 5)
		{
			W2KOS=true;
		}
	//////////////////////////////////////////////////
	// Load reg settings
	//////////////////////////////////////////////////
	char pszgroup1[256];
	char pszgroup2[256];
	char pszgroup3[256];
	char *group1=NULL;
	char *group2=NULL;
	char *group3=NULL;
	long locdom1=1;
	long locdom2=0;
	long locdom3=0;
	group1=Readgroup1();
	group2=Readgroup2();
	group3=Readgroup3();
	locdom1=Readlocdom1(locdom1);
	locdom2=Readlocdom2(locdom2);
	locdom3=Readlocdom3(locdom3);
	strcpy(pszgroup1,"VNCACCESS");
	strcpy(pszgroup2,"Administrators");
	strcpy(pszgroup3,"VNCVIEWONLY");
	if (group1){strcpy(pszgroup1,group1);}
	if (group2){strcpy(pszgroup2,group2);}
	if (group3){strcpy(pszgroup3,group3);}

	savegroup1(pszgroup1);
	savegroup2(pszgroup2);
	savegroup3(pszgroup3);
	savelocdom1(locdom1);
	savelocdom2(locdom2);
	savelocdom3(locdom3);

	if (group1){strcpy(pszgroup1,group1);delete group1;}
	if (group2){strcpy(pszgroup2,group2);delete group2;}
	if (group3){strcpy(pszgroup3,group3);delete group3;}

	//////////////////////////////////////////////////
	// logon user only works on NT>
	// NT4/w2k only as service (system account)
	// XP> works also as application
	// Group is not used...admin access rights is needed
	// MS keep changes there security model for each version....
	//////////////////////////////////////////////////
////////////////////////////////////////////////////
if (strcmp(pszgroup1,"")==0 && strcmp(pszgroup2,"")==0 && strcmp(pszgroup3,"")==0)
	if ( NT4OS || W2KOS){
		char szCurrentDir[MAX_PATH];
		if (GetModuleFileName(NULL, szCurrentDir, MAX_PATH))
		{
			char* p = strrchr(szCurrentDir, '\\');
			if (p == NULL) return false;
			*p = '\0';
			strcat (szCurrentDir,"\\authadmin.dll");
		}
		HMODULE hModule = LoadLibrary(szCurrentDir);
		if (hModule)
			{
				CheckUserGroupPassword = (CheckUserGroupPasswordFn) GetProcAddress( hModule, "CUGP" );
				HRESULT hr = CoInitialize(NULL);
				result=CheckUserGroupPassword(userin,password,clientname,pszgroup1,locdom1);
				CoUninitialize();
				FreeLibrary(hModule);
			}
		else 
			{
				MessageBoxSecure(NULL, "authadmin.dll not found", sz_ID_WARNING, MB_OK);
				result=0;
			}

	}
	if (result==1) goto accessOK;

if (strcmp(pszgroup1,"")!=0)
{
	
	///////////////////////////////////////////////////
	// NT4 domain and workgroups
	//
	///////////////////////////////////////////////////
	{
		char szCurrentDir[MAX_PATH];
		if (GetModuleFileName(NULL, szCurrentDir, MAX_PATH))
		{
			char* p = strrchr(szCurrentDir, '\\');
			if (p == NULL) return false;
			*p = '\0';
			strcat (szCurrentDir,"\\workgrpdomnt4.dll");
		}
		HMODULE hModule = LoadLibrary(szCurrentDir);
		if (hModule)
			{
				CheckUserGroupPassword = (CheckUserGroupPasswordFn) GetProcAddress( hModule, "CUGP" );
				HRESULT hr = CoInitialize(NULL);
				result=CheckUserGroupPassword(userin,password,clientname,pszgroup1,locdom1);
				CoUninitialize();
				FreeLibrary(hModule);
			}
		else
			{
				MessageBoxSecure(NULL, "workgrpdomnt4.dll not found", sz_ID_WARNING, MB_OK);
				result=0;
			}

	}
	if (result==1) goto accessOK;
	/////////////////////////////////////////////////////////////////
	if (CheckAD() && W2KOS && (locdom1==2||locdom1==3))
	{
		char szCurrentDir[MAX_PATH];
		if (GetModuleFileName(NULL, szCurrentDir, MAX_PATH))
		{
			char* p = strrchr(szCurrentDir, '\\');
			if (p == NULL) return false;
			*p = '\0';
			strcat (szCurrentDir,"\\ldapauth.dll");
		}
		HMODULE hModule = LoadLibrary(szCurrentDir);
		if (hModule)
			{
				CheckUserGroupPassword = (CheckUserGroupPasswordFn) GetProcAddress( hModule, "CUGP" );
				HRESULT hr = CoInitialize(NULL);
				result=CheckUserGroupPassword(userin,password,clientname,pszgroup1,locdom1);
				CoUninitialize();
				FreeLibrary(hModule);
			}
		else 
			{
				MessageBoxSecure(NULL, "ldapauth.dll not found", sz_ID_WARNING, MB_OK);
				result=0;
			}
	}
	if (result==1) goto accessOK;
	//////////////////////////////////////////////////////////////////////
	if (CheckAD() && NT4OS && CheckDsGetDcNameW() && (locdom1==2||locdom1==3))
	{
		char szCurrentDir[MAX_PATH];
		if (GetModuleFileName(NULL, szCurrentDir, MAX_PATH))
		{
			char* p = strrchr(szCurrentDir, '\\');
			if (p == NULL) return false;
			*p = '\0';
			strcat (szCurrentDir,"\\ldapauthnt4.dll");
		}
		HMODULE hModule = LoadLibrary(szCurrentDir);
		if (hModule)
			{
				CheckUserGroupPassword = (CheckUserGroupPasswordFn) GetProcAddress( hModule, "CUGP" );
				HRESULT hr = CoInitialize(NULL);
				result=CheckUserGroupPassword(userin,password,clientname,pszgroup1,locdom1);
				CoUninitialize();
				FreeLibrary(hModule);
			}
		else 
			{
				MessageBoxSecure(NULL, "ldapauthnt4.dll not found", sz_ID_WARNING, MB_OK);
				result=0;
			}
	}
	if (result==1) goto accessOK;
	//////////////////////////////////////////////////////////////////////
	if (CheckAD() && !NT4OS && !W2KOS && (locdom1==2||locdom1==3))
	{
		char szCurrentDir[MAX_PATH];
		if (GetModuleFileName(NULL, szCurrentDir, MAX_PATH))
		{
			char* p = strrchr(szCurrentDir, '\\');
			if (p == NULL) return false;
			*p = '\0';
			strcat (szCurrentDir,"\\ldapauth9x.dll");
		}
		HMODULE hModule = LoadLibrary(szCurrentDir);
		if (hModule)
			{
				CheckUserGroupPassword = (CheckUserGroupPasswordFn) GetProcAddress( hModule, "CUGP" );
				HRESULT hr = CoInitialize(NULL);
				result=CheckUserGroupPassword(userin,password,clientname,pszgroup1,locdom1);
				CoUninitialize();
				FreeLibrary(hModule);
			}
		else 
			{
				MessageBoxSecure(NULL, "ldapauth9x.dll not found", sz_ID_WARNING, MB_OK);
				result=0;
			}
	}
	if (result==1) goto accessOK;
}
/////////////////////////////////////////////////
if (strcmp(pszgroup2,"")!=0)
{
	///////////////////////////////////////////////////
	// NT4 domain and workgroups
	//
	///////////////////////////////////////////////////
	{
		char szCurrentDir[MAX_PATH];
		if (GetModuleFileName(NULL, szCurrentDir, MAX_PATH))
		{
			char* p = strrchr(szCurrentDir, '\\');
			if (p == NULL) return false;
			*p = '\0';
			strcat (szCurrentDir,"\\workgrpdomnt4.dll");
		}
		HMODULE hModule = LoadLibrary(szCurrentDir);
		if (hModule)
			{
				CheckUserGroupPassword = (CheckUserGroupPasswordFn) GetProcAddress( hModule, "CUGP" );
				HRESULT hr = CoInitialize(NULL);
				result=CheckUserGroupPassword(userin,password,clientname,pszgroup2,locdom2);
				CoUninitialize();
				FreeLibrary(hModule);
			}
		else 
			{
				MessageBoxSecure(NULL, "workgrpdomnt4.dll not found", sz_ID_WARNING, MB_OK);
				result=0;
			}

	}
	if (result==1) goto accessOK;
	//////////////////////////////////////////////////////
	if ( NT4OS || W2KOS){
		char szCurrentDir[MAX_PATH];
		if (GetModuleFileName(NULL, szCurrentDir, MAX_PATH))
		{
			char* p = strrchr(szCurrentDir, '\\');
			if (p == NULL) return false;
			*p = '\0';
			strcat (szCurrentDir,"\\authadmin.dll");
		}
		HMODULE hModule = LoadLibrary(szCurrentDir);
		if (hModule)
			{
				CheckUserGroupPassword = (CheckUserGroupPasswordFn) GetProcAddress( hModule, "CUGP" );
				HRESULT hr = CoInitialize(NULL);
				result=CheckUserGroupPassword(userin,password,clientname,pszgroup2,locdom2);
				CoUninitialize();
				FreeLibrary(hModule);
			}
		else 
			{
				MessageBoxSecure(NULL, "authadmin.dll not found", sz_ID_WARNING, MB_OK);
				result=0;
			}

	}
	if (result==1) goto accessOK;
	//////////////////////////////////////////////////////////////////
	if (CheckAD() && W2KOS && (locdom2==2||locdom2==3))
	{
		char szCurrentDir[MAX_PATH];
		if (GetModuleFileName(NULL, szCurrentDir, MAX_PATH))
		{
			char* p = strrchr(szCurrentDir, '\\');
			if (p == NULL) return false;
			*p = '\0';
			strcat (szCurrentDir,"\\ldapauth.dll");
		}
		HMODULE hModule = LoadLibrary(szCurrentDir);
		if (hModule)
			{
				CheckUserGroupPassword = (CheckUserGroupPasswordFn) GetProcAddress( hModule, "CUGP" );
				HRESULT hr = CoInitialize(NULL);
				result=CheckUserGroupPassword(userin,password,clientname,pszgroup2,locdom2);
				CoUninitialize();
				FreeLibrary(hModule);
			}
		else 
			{
				MessageBoxSecure(NULL, "ldapauth.dll not found", sz_ID_WARNING, MB_OK);
				result=0;
			}
	}
	if (result==1) goto accessOK;
	///////////////////////////////////////////////////////////////////////
	if (CheckAD() && NT4OS && CheckDsGetDcNameW() && (locdom2==2||locdom2==3))
	{
		char szCurrentDir[MAX_PATH];
		if (GetModuleFileName(NULL, szCurrentDir, MAX_PATH))
		{
			char* p = strrchr(szCurrentDir, '\\');
			if (p == NULL) return false;
			*p = '\0';
			strcat (szCurrentDir,"\\ldapauthnt4.dll");
		}
		HMODULE hModule = LoadLibrary(szCurrentDir);
		if (hModule)
			{
				CheckUserGroupPassword = (CheckUserGroupPasswordFn) GetProcAddress( hModule, "CUGP" );
				HRESULT hr = CoInitialize(NULL);
				result=CheckUserGroupPassword(userin,password,clientname,pszgroup2,locdom2);
				CoUninitialize();
				FreeLibrary(hModule);
			}
		else 
			{
				MessageBoxSecure(NULL, "ldapauthnt4.dll not found", sz_ID_WARNING, MB_OK);
				result=0;
			}
	}
	if (result==1) goto accessOK;
	///////////////////////////////////////////////////////////////////////
	if (CheckAD() && !NT4OS && !W2KOS && (locdom2==2||locdom2==3))
	{
		char szCurrentDir[MAX_PATH];
		if (GetModuleFileName(NULL, szCurrentDir, MAX_PATH))
		{
			char* p = strrchr(szCurrentDir, '\\');
			if (p == NULL) return false;
			*p = '\0';
			strcat (szCurrentDir,"\\ldapauth9x.dll");
		}
		HMODULE hModule = LoadLibrary(szCurrentDir);
		if (hModule)
			{
				CheckUserGroupPassword = (CheckUserGroupPasswordFn) GetProcAddress( hModule, "CUGP" );
				HRESULT hr = CoInitialize(NULL);
				result=CheckUserGroupPassword(userin,password,clientname,pszgroup2,locdom2);
				CoUninitialize();
				FreeLibrary(hModule);
			}
		else 
			{
				MessageBoxSecure(NULL, "ldapauth9x.dll not found", sz_ID_WARNING, MB_OK);
				result=0;
			}
	}
	if (result==1) goto accessOK;
}
////////////////////////////
if (strcmp(pszgroup3,"")!=0)
{
	///////////////////////////////////////////////////
	// NT4 domain and workgroups
	//
	///////////////////////////////////////////////////
	{
		char szCurrentDir[MAX_PATH];
		if (GetModuleFileName(NULL, szCurrentDir, MAX_PATH))
		{
			char* p = strrchr(szCurrentDir, '\\');
			if (p == NULL) return false;
			*p = '\0';
			strcat (szCurrentDir,"\\workgrpdomnt4.dll");
		}
		HMODULE hModule = LoadLibrary(szCurrentDir);
		if (hModule)
			{
				CheckUserGroupPassword = (CheckUserGroupPasswordFn) GetProcAddress( hModule, "CUGP" );
				HRESULT hr = CoInitialize(NULL);
				result=CheckUserGroupPassword(userin,password,clientname,pszgroup3,locdom3);
				CoUninitialize();
				FreeLibrary(hModule);
			}
		else 
			{
				MessageBoxSecure(NULL, "workgrpdomnt4.dll not found", sz_ID_WARNING, MB_OK);
				result=0;
			}

	}
	if (result==1) goto accessOK2;
	////////////////////////////////////////////////////////
	if ( NT4OS || W2KOS){
		char szCurrentDir[MAX_PATH];
		if (GetModuleFileName(NULL, szCurrentDir, MAX_PATH))
		{
			char* p = strrchr(szCurrentDir, '\\');
			if (p == NULL) return false;
			*p = '\0';
			strcat (szCurrentDir,"\\authadmin.dll");
		}
		HMODULE hModule = LoadLibrary(szCurrentDir);
		if (hModule)
			{
				CheckUserGroupPassword = (CheckUserGroupPasswordFn) GetProcAddress( hModule, "CUGP" );
				HRESULT hr = CoInitialize(NULL);
				result=CheckUserGroupPassword(userin,password,clientname,pszgroup3,locdom3);
				CoUninitialize();
				FreeLibrary(hModule);
			}
		else 
			{
				MessageBoxSecure(NULL, "authadmin.dll not found", sz_ID_WARNING, MB_OK);
				result=0;
			}

	}
	if (result==1) goto accessOK2;
	////////////////////////////////////////////////////////////////
	if (CheckAD() && W2KOS && (locdom3==2||locdom3==3))
	{
		char szCurrentDir[MAX_PATH];
		if (GetModuleFileName(NULL, szCurrentDir, MAX_PATH))
		{
			char* p = strrchr(szCurrentDir, '\\');
			if (p == NULL) return false;
			*p = '\0';
			strcat (szCurrentDir,"\\ldapauth.dll");
		}
		HMODULE hModule = LoadLibrary(szCurrentDir);
		if (hModule)
			{
				CheckUserGroupPassword = (CheckUserGroupPasswordFn) GetProcAddress( hModule, "CUGP" );
				HRESULT hr = CoInitialize(NULL);
				result=CheckUserGroupPassword(userin,password,clientname,pszgroup3,locdom3);
				CoUninitialize();
				FreeLibrary(hModule);
			}
		else 
			{
				MessageBoxSecure(NULL, "ldapauth.dll not found", sz_ID_WARNING, MB_OK);
				result=0;
			}
	}
	if (result==1) goto accessOK2;
	///////////////////////////////////////////////////////////////////
	if (CheckAD() && NT4OS && CheckDsGetDcNameW() && (locdom3==2||locdom3==3))
	{
		char szCurrentDir[MAX_PATH];
		if (GetModuleFileName(NULL, szCurrentDir, MAX_PATH))
		{
			char* p = strrchr(szCurrentDir, '\\');
			if (p == NULL) return false;
			*p = '\0';
			strcat (szCurrentDir,"\\ldapauthnt4.dll");
		}
		HMODULE hModule = LoadLibrary(szCurrentDir);
		if (hModule)
			{
				CheckUserGroupPassword = (CheckUserGroupPasswordFn) GetProcAddress( hModule, "CUGP" );
				HRESULT hr = CoInitialize(NULL);
				result=CheckUserGroupPassword(userin,password,clientname,pszgroup3,locdom3);
				CoUninitialize();
				FreeLibrary(hModule);
			}
		else 
			{
				MessageBoxSecure(NULL, "ldapauthnt4.dll not found", sz_ID_WARNING, MB_OK);
				result=0;
			}
		}
		if (result==1) goto accessOK2;
		///////////////////////////////////////////////////////////////////
	if (CheckAD() && !NT4OS && !W2KOS && (locdom3==2||locdom3==3))
	{
		char szCurrentDir[MAX_PATH];
		if (GetModuleFileName(NULL, szCurrentDir, MAX_PATH))
		{
			char* p = strrchr(szCurrentDir, '\\');
			if (p == NULL) return false;
			*p = '\0';
			strcat (szCurrentDir,"\\ldapauth9x.dll");
		}
		HMODULE hModule = LoadLibrary(szCurrentDir);
		if (hModule)
			{
				CheckUserGroupPassword = (CheckUserGroupPasswordFn) GetProcAddress( hModule, "CUGP" );
				HRESULT hr = CoInitialize(NULL);
				result=CheckUserGroupPassword(userin,password,clientname,pszgroup3,locdom3);
				CoUninitialize();
				FreeLibrary(hModule);
			}
		else 
			{
				MessageBoxSecure(NULL, "ldapauth9x.dll not found", sz_ID_WARNING, MB_OK);
				result=0;
			}
		}
		if (result==1) goto accessOK2;
	}

	/////////////////////////////////////////////////
	// If we reach this place auth failed
	/////////////////////////////////////////////////
	{
				typedef BOOL (*LogeventFn)(char *machine,char *user);
				LogeventFn Logevent = 0;
				char szCurrentDir[MAX_PATH];
				if (GetModuleFileName(NULL, szCurrentDir, MAX_PATH))
					{
						char* p = strrchr(szCurrentDir, '\\');
						*p = '\0';
						strcat (szCurrentDir,"\\logging.dll");
					}
				HMODULE hModule = LoadLibrary(szCurrentDir);
				if (hModule)
					{
						Logevent = (LogeventFn) GetProcAddress( hModule, "LOGFAILEDUSER" );
						Logevent((char *)clientname,userin);
						FreeLibrary(hModule);
					}
				return result;
	}

	accessOK://full access
	{
				typedef BOOL (*LogeventFn)(char *machine,char *user);
				LogeventFn Logevent = 0;
				char szCurrentDir[MAX_PATH];
				if (GetModuleFileName(NULL, szCurrentDir, MAX_PATH))
					{
						char* p = strrchr(szCurrentDir, '\\');
						*p = '\0';
						strcat (szCurrentDir,"\\logging.dll");
					}
				HMODULE hModule = LoadLibrary(szCurrentDir);
				if (hModule)
					{
						Logevent = (LogeventFn) GetProcAddress( hModule, "LOGLOGONUSER" );
						Logevent((char *)clientname,userin);
						FreeLibrary(hModule);
					}
				return result;
	}

	accessOK2://readonly
	{
				typedef BOOL (*LogeventFn)(char *machine,char *user);
				LogeventFn Logevent = 0;
				char szCurrentDir[MAX_PATH];
				if (GetModuleFileName(NULL, szCurrentDir, MAX_PATH))
					{
						char* p = strrchr(szCurrentDir, '\\');
						*p = '\0';
						strcat (szCurrentDir,"\\logging.dll");
					}
				HMODULE hModule = LoadLibrary(szCurrentDir);
				if (hModule)
					{
						Logevent = (LogeventFn) GetProcAddress( hModule, "LOGLOGONUSER" );
						Logevent((char *)clientname,userin);
						FreeLibrary(hModule);
					}
				result=2;
	}

	return result;
}