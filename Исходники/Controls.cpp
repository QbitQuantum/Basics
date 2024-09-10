BOOL AddPathsToComboBoxEx(HWND hComboBoxEx, const TCHAR *Path)
{
	HIMAGELIST SmallIcons;
	BOOL bRet = Shell_GetImageLists(NULL, &SmallIcons);

	if(!bRet)
	{
		return FALSE;
	}

	SendMessage(hComboBoxEx, CBEM_SETIMAGELIST, 0, reinterpret_cast<LPARAM>(SmallIcons));

	/* Remove all items that are currently in the list. */
	SendMessage(hComboBoxEx, CB_RESETCONTENT, 0, 0);

	TCHAR FindPath[MAX_PATH];
	StringCchCopy(FindPath, SIZEOF_ARRAY(FindPath), Path);
	bRet = PathAppend(FindPath, _T("*"));

	if(!bRet)
	{
		return FALSE;
	}

	WIN32_FIND_DATA wfd;
	HANDLE hFirstFile = FindFirstFile(FindPath, &wfd);

	if(hFirstFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	BOOL success = TRUE;

	while(FindNextFile(hFirstFile, &wfd))
	{
		if((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY &&
			StrCmp(wfd.cFileName, _T("..")) != 0)
		{
			TCHAR FullFileName[MAX_PATH];
			LPTSTR szRet = PathCombine(FullFileName, Path, wfd.cFileName);

			if(szRet == NULL)
			{
				success = FALSE;
				break;
			}

			SHFILEINFO shfi;
			SHGetFileInfo(Path, NULL, &shfi, NULL, SHGFI_SYSICONINDEX);

			COMBOBOXEXITEM cbItem;
			cbItem.mask = CBEIF_TEXT | CBEIF_IMAGE | CBEIF_INDENT | CBEIF_SELECTEDIMAGE;
			cbItem.iItem = -1;
			cbItem.iImage = shfi.iIcon;
			cbItem.iSelectedImage = shfi.iIcon;
			cbItem.iIndent = 1;
			cbItem.iOverlay = 1;
			cbItem.pszText = wfd.cFileName;

			LRESULT lRet = SendMessage(hComboBoxEx, CBEM_INSERTITEM, 0, reinterpret_cast<LPARAM>(&cbItem));

			if(lRet == -1)
			{
				success = FALSE;
				break;
			}
		}
	}

	FindClose(hFirstFile);

	return success;
}