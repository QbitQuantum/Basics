WCHAR* GetWndFileName(HWND hWnd)
{
	WCHAR* szName=(WCHAR*)malloc(MAX_PATH*2+1);
	DWORD dwPID = 0;

	GetWindowThreadProcessId( hWnd, &dwPID);

	HANDLE hTH = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, dwPID);

	if ( hTH != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32W me = { sizeof( MODULEENTRY32W) };
		if ( Module32FirstW( hTH, &me))
		{
			lstrcpyW(szName,me.szModule);
			//sprintf(szName,"[%s]\n",me.szExePath);
		}
		CloseHandle( hTH);
	}
	return szName;
}