void ServiceManager::UnInstall()
{
	SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
	if (schSCManager==0) 
	{
		long nError = GetLastError();
		TCHAR pTemp[121];
		_stprintf(pTemp, _T("OpenSCManager failed, error code = %d"), nError);
		LOG_WRITER_INSTANCE.WriteLog( pTemp);
	}
	else
	{
		SC_HANDLE schService = OpenService( schSCManager, SERVICE_PROPERTIES_INSTANCE.GetServiceName(), SERVICE_ALL_ACCESS);
		if (schService==0) 
		{
			long nError = GetLastError();
			TCHAR pTemp[121];
			_stprintf(pTemp, _T("OpenService failed, error code = %d"), nError);
			LOG_WRITER_INSTANCE.WriteLog( pTemp);
		}
		else
		{
			if(!DeleteService(schService)) 
			{
				TCHAR pTemp[121];
				_stprintf(pTemp, _T("Failed to delete service %s"), SERVICE_PROPERTIES_INSTANCE.GetServiceName());
				LOG_WRITER_INSTANCE.WriteLog( pTemp);
			}
			CloseServiceHandle(schService); 
		}
		CloseServiceHandle(schSCManager);	
	}

	CString logFileName=FolderHelper::GetModuleFileName().c_str();
	logFileName.Replace(_T(".exe"),_T(".log"));
	DeleteFile(logFileName);
}