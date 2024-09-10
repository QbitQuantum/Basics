void
ArchDaemonWindows::uninstallDaemon(const char* name)
{
	// remove parameters for this service.  ignore failures.
	HKEY key = openNTServicesKey();
	key      = ArchMiscWindows::openKey(key, name);
	if (key != NULL) {
		ArchMiscWindows::deleteKey(key, _T("Parameters"));
		ArchMiscWindows::closeKey(key);
	}

	// open service manager
	SC_HANDLE mgr = OpenSCManager(NULL, NULL, GENERIC_WRITE);
	if (mgr == NULL) {
		// can't open service manager
		throw XArchDaemonUninstallFailed(new XArchEvalWindows);
	}

	// open the service.  oddly, you must open a service to delete it.
	SC_HANDLE service = OpenService(mgr, name, DELETE | SERVICE_STOP);
	if (service == NULL) {
		DWORD err = GetLastError();
		CloseServiceHandle(mgr);
		if (err != ERROR_SERVICE_DOES_NOT_EXIST) {
			throw XArchDaemonUninstallFailed(new XArchEvalWindows(err));
		}
		throw XArchDaemonUninstallNotInstalled(new XArchEvalWindows(err));
	}

	// stop the service.  we don't care if we fail.
	SERVICE_STATUS status;
	ControlService(service, SERVICE_CONTROL_STOP, &status);

	// delete the service
	const bool okay = (DeleteService(service) == 0);
	const DWORD err = GetLastError();

	// clean up
	CloseServiceHandle(service);
	CloseServiceHandle(mgr);

	// give windows a chance to remove the service before
	// we check if it still exists.
	ARCH->sleep(1);

	// handle failure.  ignore error if service isn't installed anymore.
	if (!okay && isDaemonInstalled(name)) {
		if (err == ERROR_SUCCESS) {
			// this seems to occur even though the uninstall was successful.
			// it could be a timing issue, i.e., isDaemonInstalled is
			// called too soon. i've added a sleep to try and stop this.
			return;
		}
		if (err == ERROR_IO_PENDING) {
			// this seems to be a spurious error
			return;
		}
		if (err != ERROR_SERVICE_MARKED_FOR_DELETE) {
			throw XArchDaemonUninstallFailed(new XArchEvalWindows(err));
		}
		throw XArchDaemonUninstallNotInstalled(new XArchEvalWindows(err));
	}
}