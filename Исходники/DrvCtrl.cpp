BOOL DrvCtrl::LoadWdmInf(WCHAR *inf, WCHAR* szDrvSvcName)
{
	WCHAR exe[] = L"c:\\windows\\system32\\InfDefaultInstall.exe ";
	STARTUPINFOW si = { 0 };
	PROCESS_INFORMATION pi = { 0 };

	WCHAR *cmd = cs(exe, inf);
	if (!CreateProcessW(NULL, cmd, NULL, NULL, 0, 0, NULL, NULL, &si, &pi))
		return FALSE;
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	SC_HANDLE hSCM = OpenSCManagerW(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	SC_HANDLE hSvcHandle = OpenServiceW(hSCM, szDrvSvcName, SERVICE_ALL_ACCESS);
	if (hSvcHandle)
	{
		CloseServiceHandle(hSCM);
		CloseServiceHandle(hSvcHandle);
		return TRUE;
	}
	else
	{
		CloseServiceHandle(hSCM);
		return FALSE;
	}
}