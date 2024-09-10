int dha_uninstall(void)
{
	SC_HANDLE hSCManager = NULL;
	SC_HANDLE hService = NULL;
	char szPath[MAX_PATH];
	int result = 0;

	hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	hService = OpenService(hSCManager, DRV_NAME, SERVICE_ALL_ACCESS);

	dha_stop();

	result = DeleteService(hService);
	if(!result) print_last_error("Error while deleting service");

	CloseServiceHandle(hService);
	CloseServiceHandle(hSCManager);

	GetWindowsDirectory(szPath, MAX_PATH);
	strcpy(szPath + strlen(szPath), "\\system32\\drivers\\" DRV_FILENAME);
	DeleteFile(szPath);

	return 0;
}