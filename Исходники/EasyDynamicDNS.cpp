BOOL Uninstall()
{
	EventLog log;

	// open SCManager
	SC_HANDLE scMgr = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (scMgr == NULL) {
		log.LogLastError("Unable to open service control manager");
		_tprintf(_T("Unable to open service manager!\n"));
		return FALSE;
	}

	// open service and delete
	SC_HANDLE svc = OpenService(scMgr, _T("EasyDynamicDNS"), DELETE);
	if (svc == NULL) {
		log.LogLastError("Unable to open service");
		_tprintf(_T("Unable to open service!\n"));
		CloseServiceHandle(scMgr);
		return FALSE;
	}
	if (DeleteService(svc) != TRUE) {
		log.LogLastError("Unable to delete service");
		_tprintf(_T("Unable to delete service!\n"));
		CloseServiceHandle(svc);
		CloseServiceHandle(scMgr);
		return FALSE;
	}
	CloseServiceHandle(svc);

	// close SCManager
	CloseServiceHandle(scMgr);

	log.LogEvent(EVENTLOG_INFORMATION_TYPE, "EasyDynamicDNS uninstalled.");
	EventLog::UnregisterEventSource();
	return TRUE;
}