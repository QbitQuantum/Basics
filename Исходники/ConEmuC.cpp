void _wprintf(LPCWSTR asBuffer)
{
	if (!asBuffer) return;

	int nAllLen = lstrlenW(asBuffer);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwWritten = 0;

	if (!IsOutputRedirected())
	{
		WriteConsoleW(hOut, asBuffer, nAllLen, &dwWritten, 0);
	}
	else
	{
		UINT  cp = GetConsoleOutputCP();
		int cchMax = WideCharToMultiByte(cp, 0, asBuffer, -1, NULL, 0, NULL, NULL) + 1;
		char* pszOem = (cchMax > 1) ? (char*)malloc(cchMax) : NULL;
		if (pszOem)
		{
			int nWrite = WideCharToMultiByte(cp, 0, asBuffer, -1, pszOem, cchMax, NULL, NULL);
			if (nWrite > 1)
			{
				// Don't write terminating '\0' to redirected output
				WriteFile(hOut, pszOem, nWrite-1, &dwWritten, 0);
			}
			free(pszOem);
		}
	}
}