int _cdecl uninstall_minifilter (void) {

	SC_HANDLE  hService = NULL;
	SC_HANDLE  hSCManager = NULL;
	int ret = 0;

	hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);

	PrintResult(L"OpenSCManager", L"Opening Service Control Manager Succeded");

	if(hSCManager) {
		if(!hService) {
			SERVICE_STATUS    ss;

			hService = OpenServiceW(hSCManager, L"protegeDados", SERVICE_START | DELETE | SERVICE_STOP);

			ControlService(hService, SERVICE_CONTROL_STOP, &ss);
			DeleteService(hService);
			ret = 1;
		}
		CloseServiceHandle(hSCManager);
	}
	return ret;
}