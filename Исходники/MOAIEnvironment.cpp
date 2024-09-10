//----------------------------------------------------------------//
void MOAIEnvironment::DetectEnvironment () {

	RTTI_SINGLE ( MOAIGlobalEventSource )
	
	#if defined( MOAI_OS_WINDOWS )
	
		//printf ( "Env Windows\n" );
		this->SetValue ( MOAI_ENV_osBrand, "Windows" );
		
		UUID uuid;
		UuidCreateSequential ( &uuid );
		
		// For now, we'll just use the MAC address which is the last 6 bytes of the uuid.
		char buf[13];
		sprintf ( buf, "%02X%02X%02X%02X%02X%02X", uuid.Data4[2], uuid.Data4[3], uuid.Data4[4], uuid.Data4[5], uuid.Data4[6], uuid.Data4[7]);
		this->SetValue ( MOAI_ENV_udid, buf );
		
		char path[MAX_PATH];
		//HRESULT hr = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, path);
		SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, path);
		this->SetValue ( MOAI_ENV_documentDirectory, path );
		
		const int BUFSIZE = 256;
		TCHAR pszOS[BUFSIZE];

		OSVERSIONINFOEX osvi;
		SYSTEM_INFO si;
		PGNSI pGNSI;				

		ZeroMemory(&si, sizeof(SYSTEM_INFO));
		ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));

		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
		GetVersionEx((OSVERSIONINFO*) &osvi);
		
		pGNSI = (PGNSI) GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "GetNativeSystemInfo");
		if(NULL != pGNSI) {
			pGNSI(&si);
		}
		else {
			GetSystemInfo(&si);
		}

		if ( VER_PLATFORM_WIN32_NT==osvi.dwPlatformId && osvi.dwMajorVersion > 4 ) {
		
			strcpy ( pszOS, TEXT ( "Win" ));			
			if ( osvi.dwMajorVersion == 6 ) {
				if ( osvi.dwMinorVersion == 1 ) {
					if( osvi.wProductType == VER_NT_WORKSTATION )
						strcat(pszOS, TEXT("7"));
					else strcat(pszOS, TEXT("2008R2" ));
				}
				else if( osvi.dwMinorVersion == 0 ) {
					if( osvi.wProductType == VER_NT_WORKSTATION )
						strcat(pszOS, TEXT("Vista"));
					else strcat(pszOS, TEXT("Server2008" ));
				}
			}
			else if ( osvi.dwMajorVersion == 5 ) {
				if (osvi.dwMinorVersion == 2) {				
					if( osvi.wProductType == VER_NT_WORKSTATION && si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64) {
						strcat(pszOS, TEXT( "XPx64"));
					}
					else {
						strcat(pszOS, TEXT("Server2003"));
					}
				}
				else if ( osvi.dwMinorVersion == 1 ) {
					strcat(pszOS, TEXT("XP"));					
				}
				else if ( osvi.dwMinorVersion == 0 ) {
					strcat(pszOS, TEXT("2000"));
				}
			}
			
			this->SetValue ( MOAI_ENV_osVersion, pszOS );
		}
		else {
			this->SetValue ( MOAI_ENV_osVersion, "WinUnknown" );
		}
		
	#elif defined( MOAI_OS_LINUX )
	
		//printf ( "Env Linux\n" );
		this->SetValue ( MOAI_ENV_osBrand, "Linux" );

	#elif defined ( MOAI_OS_OSX )
	
		//printf ( "Env OSX\n" );
		this->SetValue ( MOAI_ENV_osBrand, "OSX" );
	  #if 0 /* doesn't compile yet */
		// OS Version
		SInt32 majorVersion,minorVersion,bugFixVersion;

		Gestalt(gestaltSystemVersionMajor, &majorVersion);
		Gestalt(gestaltSystemVersionMinor, &minorVersion);
		Gestalt(gestaltSystemVersionBugFix, &bugFixVersion);

		char buffer[256];
		sprintf(buffer, "%d.%d.%d",majorVersion,minorVersion,bugFixVersion);
		this->SetValue ( MOAI_ENV_osVersion, buffer );
	  #endif
	#else
		//printf ( "No environment detected\n" );
	#endif
}