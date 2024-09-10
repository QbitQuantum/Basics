char* FGDump::CreateSessionID()
{
	// Format for the session ID is: YYYY-MM-DD-HH-mm-SS
	// Will be dynamically allocated, caller should free the memory
	SYSTEMTIME st;
	char* szIDBuffer = NULL;

	GetSystemTime(&st);

	size_t nArgSize = _scprintf("%d-%02d-%02d-%02d-%02d-%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	szIDBuffer = (char*)malloc(nArgSize + 1);
	memset(szIDBuffer, 0, nArgSize + 1);
	_snprintf(szIDBuffer, nArgSize, "%d-%02d-%02d-%02d-%02d-%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

	return szIDBuffer;
}