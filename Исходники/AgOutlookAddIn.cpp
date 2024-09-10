UINT WINAPI PreventUninstall(MSIHANDLE hInstall)
{
#ifdef NOTUSED
	CString strMsg;
	strMsg.Format("Are you really, really sure you want to uninstall %s?", g_szAppName);
	if (MessageBox(hWndSetup, strMsg, g_szAppName, MB_YESNO) != IDYES)
		return false; // Do not continue uninstalling
#endif NOTUSED

	// DllUnregisterServer is called to ensure that all vestige of Creata Mail COM
	// objects' registration is removed upon uinstall. This fixes the problem where
	// CreataMail would still appear in Explorer Bar menu after uinstall.  
	DllUnregisterServer();

	/*BOOL bMaintMode = MsiGetMode(hInstall, MSIRUNMODE_MAINTENANCE); 
	::MessageBox(NULL, String("TEST bMaintMode = %X", bMaintMode), "Install Test", MB_OK);*/
	
	// If AutoUpdate is not in progress and Uninstall is not in Maintenance mode then
	// the survey page is displayed. Otherwise, if Autoupdate is in progress the status 
	// is now cleared. If Uninstall is in Maintenance mode then Maintenance mode status 
	// is now cleared.
	DWORD dwUpdateStatus = 0;
	DWORD dwInstallStatus = 0;
	bool bInstallStatKeyFound = GetInstallStatus(dwInstallStatus);
	CAutoUpdate::GetAutoUpdateStatus(dwUpdateStatus);

	if (dwUpdateStatus == AUTOUPDATE_STATUS_DONE)
	{
#ifdef NOTUSED
		if (!bInstallStatKeyFound || dwInstallStatus != UNINSTALL_STATUS_MAINTENANCE)
		{
			CString szURL;
			CAuthenticate Auth;
			if (Auth.ReadHost(szURL))
			{
				szURL += DEFAULT_UNINSTALL;
				DWORD dwResult = (DWORD)::ShellExecute(NULL, "open", szURL, NULL, NULL, SW_SHOWNORMAL);	
			}
		}
#endif NOTUSED
	}
	else
		CAutoUpdate::SetAutoUpdateStatus(AUTOUPDATE_STATUS_DONE);

	if (dwInstallStatus == UNINSTALL_STATUS_MAINTENANCE)
		SetInstallStatus(UNINSTALL_STATUS_DONE);

	return 1; // Continue with the uninstall
}