/* Get the full path of the process running in iProcessID. On error, false is
 * returned and an error message is placed in sName. */
bool GetProcessFileName( uint32_t iProcessID, std::string &sName )
{
	/* This method works in everything except for NT4, and only uses
	 * kernel32.lib functions. */
	do {
		HANDLE hSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, iProcessID );
		if( hSnap == nullptr )
		{
			sName = werr_format( GetLastError(), "CreateToolhelp32Snapshot" );
			break;
		}

		MODULEENTRY32 me;
		ZERO( me );
		me.dwSize = sizeof(MODULEENTRY32);
		bool bRet = !!Module32First( hSnap, &me );
		CloseHandle( hSnap );

		if( bRet )
		{
			sName = me.szExePath;
			return true;
		}

		sName = werr_format( GetLastError(), "Module32First" );
	} while(0);

	// This method only works in NT/2K/XP.
	do {
		static HINSTANCE hPSApi = nullptr;
		typedef DWORD (WINAPI* pfnGetProcessImageFileNameA)(HANDLE hProcess, LPSTR lpImageFileName, DWORD nSize);
		static pfnGetProcessImageFileNameA pGetProcessImageFileName = nullptr;
		static bool bTried = false;

		if( !bTried )
		{
			bTried = true;

			hPSApi = LoadLibrary("psapi.dll");
			if( hPSApi == nullptr )
			{
				sName = werr_format( GetLastError(), "LoadLibrary" );
				break;
			}
			else
			{
				pGetProcessImageFileName = (pfnGetProcessImageFileNameA) GetProcAddress( hPSApi, "GetProcessImageFileNameA" );
				if( pGetProcessImageFileName == nullptr )
				{
					sName = werr_format( GetLastError(), "GetProcAddress" );
					break;
				}
			}
		}

		if( pGetProcessImageFileName != nullptr )
		{
			HANDLE hProc = OpenProcess( PROCESS_VM_READ|PROCESS_QUERY_INFORMATION, NULL, iProcessID );
			if( hProc == nullptr )
			{
				sName = werr_format( GetLastError(), "OpenProcess" );
				break;
			}

			char buf[1024];
			int iRet = pGetProcessImageFileName( hProc, buf, sizeof(buf) );
			CloseHandle( hProc );

			if( iRet )
			{
				if( iRet == sizeof(buf) )
					buf[iRet-1] = 0;
				sName = buf;
				return true;
			}

			sName = werr_format( GetLastError(), "GetProcessImageFileName" );
		}
	} while(0);

	return false;
}