BOOL CNetInstall::CheckFile(LPCWSTR lpszPath, tagFileInfo* pInfo)
{
	BOOL bRet = FALSE;
	if (StrCmpIW(PathFindExtensionW(lpszPath), L".cia"))
	{
		return FALSE;
	}
	HANDLE hFile = CreateFileW(lpszPath, FILE_READ_ATTRIBUTES, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		LARGE_INTEGER LargeInt;
		if (GetFileSizeEx(hFile, &LargeInt))
		{
			if (pInfo)
			{
				pInfo->uFileSize = LargeInt.QuadPart;
				pInfo->strPath = lpszPath;
				bRet = TRUE;
			}
		}
		CloseHandle(hFile);		
	}
	return bRet;
}