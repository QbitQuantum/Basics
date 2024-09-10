VOID UninstallService()
{
	LOG_TRACE();
	SC_HANDLE hSCMgr = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (NULL == hSCMgr)
	{
		std::cout << "Uninstall service failed. (OpenSCManager return null. GetLastError == " << GetLastError() << ")" << std::endl;
		LOG_RUN_ERROR("OpenSCManager failed. (%d)", GetLastError());
		return;
	}

	SC_HANDLE hSvc = OpenService(hSCMgr,MY_SERVICE_NAME, SERVICE_STOP | DELETE);
	if (NULL == hSvc)
	{
		std::cout << "Uninstall service failed. (OpenService return null. GetLastError == " << GetLastError() << ")" << std::endl;
		LOG_RUN_ERROR("CreateService failed. (%d)", GetLastError());
		CloseServiceHandle(hSCMgr);
		return;
	}

	//停止服务
	ControlService(hSvc, SERVICE_CONTROL_STOP, &g_svc_status);
	//删除服务
	if (DeleteService(hSvc))
	{
		LOG_RUN_DEBUG("Uninstall service success.");
		std::cout << "Uninstall service success." << std::endl;
	}
	else
	{
		LOG_RUN_DEBUG("DeleteService failed. (%d)", GetLastError());
		std::cout << "Uninstall service failed. (DeleteService return false. GetLastError == " << GetLastError() << ")" << std::endl;
	}

	CloseServiceHandle(hSvc);
	CloseServiceHandle(hSCMgr);
}