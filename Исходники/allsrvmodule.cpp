void WINAPI CServiceModule::ServiceMain(
	DWORD dwArgc,
	LPSTR *lpszArgv)
{
	HRESULT hr;

	g.ssh = RegisterServiceCtrlHandlerA(c_szSvcName, ServiceControl);

	if (!g.ssh)
	{
		SetSvcStatus(SERVICE_STOPPED, GetLastError());
		return;
	}

	SetSvcStatus(SERVICE_START_PENDING, NO_ERROR);

	hr = FedSrv_Init();

	if (SUCCEEDED(hr))
		SetSvcStatus(SERVICE_RUNNING, NO_ERROR);
	else
		SetSvcStatus(SERVICE_STOPPED, GetLastError());

}