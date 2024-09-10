/************************* Workers ************************************/
static BOOL IsShutdownTypeEnabled(BYTE shutdownType)
{
	BOOL bReturn = FALSE;
	switch (shutdownType) {
	case SDSDT_HIBERNATE:
	case SDSDT_STANDBY:
		bReturn = shutdownType == SDSDT_HIBERNATE ? IsPwrHibernateAllowed() : IsPwrSuspendAllowed() != 0;
		/* test privilege */
		if (bReturn) {
			bReturn = WinNT_SetPrivilege(SE_SHUTDOWN_NAME, TRUE);
			if (bReturn) WinNT_SetPrivilege(SE_SHUTDOWN_NAME, FALSE);
		}
		break;
	case SDSDT_LOGOFF:
		{
			HKEY hKey;
			DWORD dwSetting, dwSize;
			/* NoLogOff is BINARY on Win9x/ME and DWORD on Win2000+ */
			bReturn = TRUE;
			if (RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer"), 0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS) {
				dwSize = sizeof(dwSetting);
				if (RegQueryValueEx(hKey, _T("NoLogOff"), 0, NULL, (LPBYTE)&dwSetting, &dwSize) == ERROR_SUCCESS)
					if (dwSetting) bReturn = FALSE;
				RegCloseKey(hKey);
			}
		}
		break;
	case SDSDT_LOCKWORKSTATION:
		{
			HKEY hKey;
			DWORD dwSize, dwSetting;
			/* DisableLockWorkstation is DWORD on Win2000+ */
			bReturn = TRUE;
			if (RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System"), 0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS) {
				dwSize = sizeof(dwSetting);
				if (!RegQueryValueEx(hKey, _T("DisableLockWorkstation"), 0, NULL, (LPBYTE)&dwSetting, &dwSize))
					if (dwSetting)
						bReturn = FALSE;
				RegCloseKey(hKey);
			}
		}
		break;
	case SDSDT_CLOSERASCONNECTIONS:
		/* check if RAS installed/available */
		bReturn = TRUE;
		break;
	case SDSDT_SETMIRANDAOFFLINE:
	case SDSDT_CLOSEMIRANDA:
		bReturn = TRUE; /* always possible */
		break;
	case SDSDT_REBOOT:
	case SDSDT_SHUTDOWN:
		/* test privileges */
		bReturn = WinNT_SetPrivilege(SE_SHUTDOWN_NAME, TRUE);
		if (bReturn)
			WinNT_SetPrivilege(SE_SHUTDOWN_NAME, FALSE);
		break;
	}
	return bReturn;
}