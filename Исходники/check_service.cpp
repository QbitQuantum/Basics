DWORD ServiceStatus(CONST printInfoStruct& printInfo) 
{
	SC_HANDLE hSCM;
	SC_HANDLE hService;
	DWORD cbBufSize;
	LPBYTE lpBuf = NULL;

	if (debug)
		std::wcout << L"Opening SC Manager" << '\n';

	hSCM = OpenSCManager(NULL, NULL, GENERIC_READ);
	if (hSCM == NULL)
		goto die;

	if (debug)
		std::wcout << L"Getting Service Information" << '\n';

	hService = OpenService(hSCM, printInfo.service.c_str(), SERVICE_QUERY_STATUS);
	if (hService == NULL)
		goto die;
	
	QueryServiceStatusEx(hService, SC_STATUS_PROCESS_INFO, NULL, 0, &cbBufSize);
	if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
		goto die;

	lpBuf = new BYTE[cbBufSize];
	if (QueryServiceStatusEx(hService, SC_STATUS_PROCESS_INFO, lpBuf, cbBufSize, &cbBufSize)) {
		LPSERVICE_STATUS_PROCESS pInfo = (LPSERVICE_STATUS_PROCESS)lpBuf;
		return pInfo->dwCurrentState;
	}


die:
	die();
	if (hSCM)
		CloseServiceHandle(hSCM);
	if (hService)
		CloseServiceHandle(hService);
	delete [] lpBuf;

	return -1;
}