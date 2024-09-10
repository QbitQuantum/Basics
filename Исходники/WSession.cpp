DWORD apiGetConsoleSessionID()
{
	DWORD nSessionId = 0;
	DWORD (WINAPI* wtsGetActiveConsoleSessionId)(void) = NULL;
	MModule kernel32(L"kernel32.dll");
	if (kernel32.GetProcAddress("WTSGetActiveConsoleSessionId", wtsGetActiveConsoleSessionId))
	{
		nSessionId = wtsGetActiveConsoleSessionId();
	}
	return nSessionId;
}