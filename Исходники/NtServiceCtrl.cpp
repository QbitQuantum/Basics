DWORD InstallService(
	__in        LPCWSTR     lpServiceName,
	__in_opt    LPCWSTR     lpDisplayName,
	__in        DWORD       dwDesiredAccess,
	__in        DWORD       dwServiceType,
	__in        DWORD       dwStartType,
	__in        DWORD       dwErrorControl,
	__in_opt    LPCWSTR     lpBinaryPathName,
	__in_opt    LPCWSTR     lpLoadOrderGroup,
	__out_opt   LPDWORD     lpdwTagId,
	__in_opt    LPCWSTR     lpDependencies,
	__in_opt    LPCWSTR     lpServiceStartName,
	__in_opt    LPCWSTR     lpPassword
	)
{
	SC_HANDLE sch;
	SC_HANDLE service;
	DWORD dwError = ERROR_SUCCESS;

	sch = OpenSCManager(NULL, NULL, GENERIC_WRITE);
	if(sch)
	{
		service = CreateServiceW(
			sch,
			lpServiceName,
			lpDisplayName,
			dwDesiredAccess,
			dwServiceType,
			dwStartType,
			dwErrorControl,
			lpBinaryPathName,
			lpLoadOrderGroup,
			lpdwTagId,
			lpDependencies,
			lpServiceStartName,
			lpPassword);

		if(service)
		{
			CloseServiceHandle(service);
		}
		else
		{
			dwError = GetLastError();
		}
		
		CloseServiceHandle(sch);
	}
	else
	{
		dwError = GetLastError();
	}

	return dwError;
}