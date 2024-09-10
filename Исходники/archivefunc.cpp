//##################################################################
// See DeleteDirectoryA
//##################################################################
BOOL DeleteDirectoryW(LPCWSTR lpszDir)
{
	size_t len      = lstrlenW(lpszDir);
	WCHAR *pszFrom  = new WCHAR[len+2];

	lstrcpyW(pszFrom, lpszDir);
	pszFrom[len] = 0;
	pszFrom[len+1] = 0;  // Append extra NUL

	SHFILEOPSTRUCTW fileop;
	fileop.hwnd   = NULL;
	fileop.wFunc  = FO_DELETE;
	fileop.pFrom  = pszFrom;
	fileop.pTo    = NULL;
	fileop.fFlags = FOF_NOCONFIRMATION|FOF_SILENT;

	fileop.fAnyOperationsAborted = FALSE;
	fileop.lpszProgressTitle     = NULL;
	fileop.hNameMappings         = NULL;

	int ret = SHFileOperationW(&fileop);
	delete [] pszFrom;
	return (ret == 0);
}