int TestPathIsUNCEx(int argc, char* argv[])
{
	BOOL status;
	LPTSTR Server;
	TCHAR Path[PATHCCH_MAX_CCH];

	/* Path is UNC */

	_tcscpy(Path, testPathUNC);

	status = PathIsUNCEx(Path, (LPCTSTR*) &Server);

	if (!status)
	{
		_tprintf(_T("PathIsUNCEx status: 0x%08")_T(PRIX32)_T("\n"), status);
		return -1;
	}

	if (_tcscmp(Server, testServer) != 0)
	{
		_tprintf(_T("Server Name Mismatch: Actual: %s, Expected: %s\n"), Server, testServer);
		return -1;
	}

	/* Path is not UNC */

	_tcscpy(Path, testPathNotUNC);

	status = PathIsUNCEx(Path, (LPCTSTR*) &Server);

	if (status)
	{
		_tprintf(_T("PathIsUNCEx status: 0x%08")_T(PRIX32)_T("\n"), status);
		return -1;
	}

	return 0;
}