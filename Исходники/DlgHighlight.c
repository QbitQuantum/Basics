BOOL GetBookmarkFileName(HWND hwndHexView, LPCTSTR szFileName, TCHAR *szBookPath)
{
	TCHAR szBase[MAX_PATH] = {0};
	TCHAR szAppData[MAX_PATH];
	TCHAR *pszName;
	UINT64 bookid;
	
	if(szFileName == 0)
	{
		szFileName = szBase;

		if(!HexView_GetFileName(hwndHexView, szBase, MAX_PATH))
			return FALSE;
	}

	// has this file got a bookmark id already??
	if(LoadFileData(szFileName, TEXT("HexEdit.bookmark"), &bookid, sizeof(UINT64)) != sizeof(UINT64))
	{
		//BY_HANDLE_FILE_INFORMATION bhfi;
		//HANDLE hFile = CreateFile(szBase, 0, FILE_SHARE_READ|FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);

		//if(hFile == INVALID_HANDLE_VALUE)
		//	return FALSE;

		// generate one from the base NTFS fileid
		//GetFileInformationByHandle(hFile, &bhfi);
		//CloseHandle(hFile);

		bookid = GetTickCount();//(UINT64)bhfi.nFileIndexLow | ((UINT64)bhfi.nFileIndexHigh << 32);

		// only save if the file exists
		if(GetFileAttributes(szFileName) != INVALID_FILE_ATTRIBUTES)
		{
			SaveFileData(szFileName, TEXT("HexEdit.bookmark"), &bookid, sizeof(UINT64));
		}
	}

	if((pszName = _tcsrchr(szFileName, '\\')) == 0)
		return FALSE;

	// get location of application data

	//
	// get/create the following directory:
	//
	//	{ApplicationData}\Local\Catch22\Bookmarks 
	//
	GetProgramDataPath(szAppData, MAX_PATH);
	lstrcat(szAppData, TEXT("\\Bookmarks"));
	SHCreateDirectory(NULL, szAppData);

	//
	//	Formulate the bookmark filename
	//
	wsprintf(szBookPath, TEXT("%s\\%s-%08x-bookmark.xml"), szAppData, pszName+1, bookid);
	//lstrcat(szBookPath, pszName+1);
	//lstrcat(szBookPath, TEXT(".bookmark"));

	return TRUE;
}