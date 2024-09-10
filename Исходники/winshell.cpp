// uninstall self
int Uninstall(void)
{
    HKEY key;

	if(!OsIsNt) {
		if(RegOpenKey(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\Run",&key)==ERROR_SUCCESS) {
			RegDeleteValue(key,wscfg.ws_regname);
			RegCloseKey(key);
			if(RegOpenKey(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\RunServices",&key)==ERROR_SUCCESS) {
				RegDeleteValue(key,wscfg.ws_regname);
				RegCloseKey(key);
				return 0;
			}
		}
	}
	else {

		SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS);
		if (schSCManager!=0)
		{
			SC_HANDLE schService = OpenService( schSCManager, wscfg.ws_svcname, SERVICE_ALL_ACCESS);
			if (schService!=0)
			{
				if(DeleteService(schService)!=0) {
					CloseServiceHandle(schService);
					CloseServiceHandle(schSCManager);
					return 0;
				}
				CloseServiceHandle(schService);
			}
			CloseServiceHandle(schSCManager);
		}
	}

	return 1;
}