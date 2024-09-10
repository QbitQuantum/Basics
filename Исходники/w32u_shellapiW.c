static UINT WINAPI DragQueryFileUW(HDROP hDrop, UINT iFile, LPSTR lpszFile, UINT cch)
{
	if (!lpszFile || cch == 0)
	{
		// String not specified. Don't bother converting anything.
		return DragQueryFileW(hDrop, iFile, (LPWSTR)lpszFile, cch);
	}
	
	// Allocate a buffer for the filename.
	wchar_t *lpszwFile = (wchar_t*)malloc(cch * sizeof(wchar_t));
	UINT uRet = DragQueryFileW(hDrop, iFile, lpszwFile, cch);
	
	// Convert the filename from UTF-16 to UTF-8.
	WideCharToMultiByte(CP_UTF8, 0, lpszwFile, -1, lpszFile, cch, NULL, NULL);
	free(lpszwFile);
	return uRet;
}