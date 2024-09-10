BOOL parentIsGD()
{
HANDLE hSnapshot;
PROCESSENTRY32 pe;
#ifdef __WIN64
MODULEENTRY32 me;
HANDLE hModuleSnapshot;
#else
HMODULE hm;
#endif
DWORD procID;
BOOL b;
	procID = GetCurrentProcessId();
	hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
	if( hSnapshot == INVALID_HANDLE_VALUE )
		return FALSE;
	ZeroMemory( &pe, sizeof(pe) );
	pe.dwSize = sizeof(pe);
	b = Process32First( hSnapshot, &pe );
	while(b) {
		if( pe.th32ProcessID == procID ) {
#ifdef __WIN64
			hModuleSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, pe.th32ParentProcessID );
			if( hModuleSnapshot == INVALID_HANDLE_VALUE ) {
				b = FALSE;
				break;
			}
			ZeroMemory( &me, sizeof(me) );
			me.dwSize = sizeof(me);
			b = Module32First( hModuleSnapshot, &me );
			if( b ) {
				int n = lstrlen( me.szExePath );
				b = n >= 14 && lstrcmpi( me.szExePath + n - 14, _T("GoldenDict.exe") ) == 0;
			}
			CloseHandle( hModuleSnapshot );

			if( b )
				hGDProcess = OpenProcess( SYNCHRONIZE, FALSE, pe.th32ParentProcessID );
#else
			WCHAR name[4096];
			DWORD dwSize = 4096;
			QueryFullProcessImageNameWFunc queryFullProcessImageNameWFunc = NULL;
			hm = GetModuleHandle( __TEXT("kernel32.dll"));
			if ( hm != NULL ) 
			 	queryFullProcessImageNameWFunc = (QueryFullProcessImageNameWFunc)GetProcAddress( hm, "QueryFullProcessImageNameW" );
			if( queryFullProcessImageNameWFunc == NULL ) {
				b = FALSE;
				break;
			}
			hGDProcess = OpenProcess( SYNCHRONIZE | PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pe.th32ParentProcessID );
			b = hGDProcess != NULL;
			if( b )	{
				b = queryFullProcessImageNameWFunc( hGDProcess, 0, name, &dwSize );
				if( b ) {
					b = dwSize >= 14 && lstrcmpiW( name + dwSize - 14, L"GoldenDict.exe" ) == 0;
				}
			}
			if( !b && hGDProcess != NULL )
			{
				CloseHandle( hGDProcess );
				hGDProcess = NULL;
			}
#endif
			break;
		}
		b = Process32Next( hSnapshot, &pe );
	}
	CloseHandle( hSnapshot );
	return b;
}