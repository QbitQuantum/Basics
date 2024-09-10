	/**
	 * Stops and removes the service
	 *
	 * @param name The name of the service to uninstall 
	 *
	 * @author mickem
	 *
	 * @date 03-13-2004
	 *
	 */
	void Uninstall(std::wstring name) {
		SC_HANDLE   schService;
		SC_HANDLE   schSCManager;
		Stop(name);

		schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
		if (!schSCManager)
			throw SCException("OpenSCManager failed: " + error::lookup::last_error());
		schService = OpenService(schSCManager, name.c_str(), SERVICE_ALL_ACCESS);
		if (schService) {
			if(!DeleteService(schService)) {
				std::string err = "DeleteService failed: " + error::lookup::last_error();
				CloseServiceHandle(schService);
				CloseServiceHandle(schSCManager);
				throw SCException(err);
			}
			CloseServiceHandle(schService);
		} else {
			std::string err = "OpenService failed: " + error::lookup::last_error();
			CloseServiceHandle(schSCManager);
			throw SCException(err);
		}
		CloseServiceHandle(schSCManager);
	}