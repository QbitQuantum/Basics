codeUNINSTALL_INIT Uninstall_Init(
    HWND        hwndParent,
    LPCTSTR     pszInstallDir
    )
{
	// Disable Today Plugin
	HKEY key;
	DWORD dwEnabled, dwRet;
	DWORD lpcbData = sizeof(dwEnabled);
	
	dwRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE,_T("\\Software\\Microsoft\\Today\\Items\\PockeTwit"),0,0,&key);
	
	dwEnabled = 0;
	
	dwRet = RegSetValueEx(key,_T("Enabled"),0,REG_DWORD,(LPBYTE)&dwEnabled,sizeof(DWORD));
	
	RegFlushKey(key);

	RegCloseKey(key);

	PostMessage(HWND_BROADCAST, WM_WININICHANGE, 0xF2, 0);

	Sleep(1000);

    return codeUNINSTALL_INIT_CONTINUE;
}