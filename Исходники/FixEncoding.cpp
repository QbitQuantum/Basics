BOOL ConvertTextFileToUnicode(UINT CodePage)
{
	int const cbMax = 1024 * 1024;   // Unable to process files larger than 1MB
	HANDLE hFile = CreateFile(lpSource, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;
	LPSTR lpSourceText = (LPSTR)_malloca(cbMax);
	DWORD NumberOfBytesRead; 
	ReadFile(hFile, lpSourceText, cbMax, &NumberOfBytesRead, NULL);
	CloseHandle(hFile);

	// Convert the CodePage encoded text to unicode
	int cchWideChar = MultiByteToWideChar(CodePage, 0, lpSourceText, NumberOfBytesRead, NULL, 0);
	int cbUnicode = cchWideChar * sizeof(WCHAR);
	LPWSTR lpTarget = (LPWSTR)_malloca(cbUnicode);
	int nWideCharsWritten = MultiByteToWideChar(CodePage, 0, lpSourceText, NumberOfBytesRead, lpTarget, cchWideChar); 
	_freea(lpSourceText);

	// Backup the source file
	TCHAR szDefaultExt[5] = TEXT(".bak");
	//int nLength = _tcslen(lpSource) + _tcslen(szDefaultExt);
	//LPTSTR lpBakFileName = (LPTSTR)malloc(nLength * sizeof(TCHAR));
	//*lpBakFileName = NULL;
	TCHAR lpBakFileName[MAX_PATH] = TEXT("");
	_tcscat_s(lpBakFileName, MAX_PATH, lpSource);
	_tcscat_s(lpBakFileName, MAX_PATH, szDefaultExt);
	if (MoveFile(lpSource, lpBakFileName) == 0) return FALSE;

	// Write the unicode text
	HANDLE hNewFile = CreateFile(lpSource, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hNewFile == INVALID_HANDLE_VALUE) return FALSE;
	DWORD NumberOfBytesWritten;
	// Write the unicode signature
	const WORD bom = 0xfeff;
	WriteFile(hFile, &bom, sizeof(bom), &NumberOfBytesWritten, NULL);
	WriteFile(hNewFile, lpTarget, nWideCharsWritten * sizeof(WCHAR), &NumberOfBytesWritten, NULL); // Treat lpTarget as ansi type to get the length in byte
	_freea(lpTarget);
	CloseHandle(hNewFile);
	return TRUE;
}