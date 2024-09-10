VOID setFileIcon (HWND hDlg, TCHAR* fileDir, WIN32_FIND_DATA* findData, LVITEM* lvI, HIMAGELIST hIL)
{
	SHFILEINFO shfi;
	if (lstrcmp (findData->cFileName, L"..") == 0)
	{
		HINSTANCE hInst = (HINSTANCE) GetWindowLong (hDlg, GWL_HINSTANCE);
		shfi.hIcon = LoadIcon (hInst, MAKEINTRESOURCE (IDI_ICON1));
		lvI->iImage = ImageList_AddIcon (hIL, shfi.hIcon);
	}
	else
	{
		TCHAR fullPath [FM_MAX_PATH];
		lstrcpy (fullPath, fileDir);
		lstrcat (fullPath, findData->cFileName);
		SHGetFileInfo (fullPath, findData->dwFileAttributes, &shfi, sizeof(SHFILEINFO),
			SHGFI_ICON | SHGFI_SMALLICON | SHGFI_USEFILEATTRIBUTES | SHGFI_ADDOVERLAYS);
		if (shfi.hIcon == NULL)
		{
			wprintfd (L"Не найдена иконка для файла %s", fullPath);
			return;
		}
		lvI->iImage = ImageList_ReplaceIcon (hIL, -1, shfi.hIcon);
		if (lvI->iImage == -1)
		{
			lvI->iImage = 0;
		}
	}
	DestroyIcon (shfi.hIcon);
	return;
}