////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SHUTdown
HRESULT SHUT(PCTSTR ptzCmd)
{
	Priv(SE_SHUTDOWN_NAME);
	BOOL bReboot = ((*ptzCmd) == 'R') || ((*ptzCmd) == 'r');
	if (ExitWindowsEx(bReboot ? EWX_REBOOT : EWX_POWEROFF, 0))
	{
		return S_OK;
	}

	// End session
	DWORD dwResult;
	SendMessageTimeout(HWND_BROADCAST, WM_QUERYENDSESSION, 0, 0, 0, 2000, &dwResult);
	SendMessageTimeout(HWND_BROADCAST, WM_ENDSESSION, 0, 0, 0, 2000, &dwResult);
	//SendMessageTimeout(HWND_BROADCAST, WM_CLOSE, 0, 0, 0, 2000, &dwResult);
	SendMessageTimeout(HWND_BROADCAST, WM_DESTROY, 0, 0, 0, 2000, &dwResult);

	// Get function address
	typedef DWORD (NTAPI *PNtShutdownSystem)(DWORD dwAction);
	PNtShutdownSystem NtShutdownSystem = (PNtShutdownSystem) GetProcAddress(GetModuleHandle(TEXT("NTDLL")), "NtShutdownSystem");
	if (!NtShutdownSystem)
	{
		return E_FAIL;
	}

	// Shutdown
	return NtShutdownSystem(bReboot ? 1: 2);
}