/* Presumably Windows, pulled from MSDN sample code */
int
GetFileNameFromHandle(HANDLE hFile, char filepath[])
{
    int bSuccess = 0;
    TCHAR pszFilename[MAXPATHLEN+1];
    char filename[MAXPATHLEN+1];
    HANDLE hFileMap;

    /* Get the file size. */
    DWORD dwFileSizeHi = 0;
    DWORD dwFileSizeLo = GetFileSize(hFile, &dwFileSizeHi);

    if (dwFileSizeLo == 0 && dwFileSizeHi == 0) {
	_tprintf(TEXT("Cannot map a file with a length of zero.\n"));
	return FALSE;
    }

    /* Create a file mapping object. */
    hFileMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 1, NULL);

    if (hFileMap) {
	/* Create a file mapping to get the file name. */
	void* pMem = MapViewOfFile(hFileMap, FILE_MAP_READ, 0, 0, 1);

	if (pMem) {
	    if (GetMappedFileName (GetCurrentProcess(), pMem, pszFilename, MAXPATHLEN)) {

		/* Translate path with device name to drive letters. */
		TCHAR szTemp[MAXPATHLEN+1];
		szTemp[0] = '\0';

		if (GetLogicalDriveStrings(MAXPATHLEN, szTemp)) {
		    TCHAR szName[MAXPATHLEN];
		    TCHAR szDrive[3] = TEXT(" :");
		    int bFound = 0;
		    TCHAR* p = szTemp;

		    do {
			/* Copy the drive letter to the template string */
			*szDrive = *p;

			/* Look up each device name */
			if (QueryDosDevice(szDrive, szName, MAXPATHLEN)) {
			    size_t uNameLen = _tcslen(szName);

			    if (uNameLen < MAXPATHLEN) {
				bFound = _tcsnicmp(pszFilename, szName, uNameLen) == 0;

				if (bFound && *(pszFilename + uNameLen) == _T('\\')) {
				    /* Reconstruct pszFilename using szTempFile */
				    /* Replace device path with DOS path */
				    TCHAR szTempFile[MAXPATHLEN];
				    StringCchPrintf(szTempFile, MAXPATHLEN, TEXT("%s%s"), szDrive, pszFilename+uNameLen);
				    StringCchCopyN(pszFilename, MAXPATHLEN+1, szTempFile, _tcslen(szTempFile));
				}
			    }
			}

			/* Go to the next NULL character. */
			while (*p++);
		    } while (!bFound && *p)
			; /* end of string */
		}
	    }
	    bSuccess = TRUE;
	    UnmapViewOfFile(pMem);
	}

	CloseHandle(hFileMap);
    }
    if (sizeof(TCHAR) == sizeof(wchar_t)) {
	wcstombs(filename, (const wchar_t *)pszFilename, MAXPATHLEN);
	bu_strlcpy(filepath, filename, MAXPATHLEN);
    } else {
	bu_strlcpy(filepath, pszFilename, MAXPATHLEN);
    }
    return (bSuccess);
}