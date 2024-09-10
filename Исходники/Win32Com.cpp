wchar_t *FolderDlgInnerW(HWND hWnd, wchar_t *title, wchar_t *default_dir)
{
	BROWSEINFOW info;
	wchar_t display_name[MAX_PATH];
	FOLDER_DLG_INNER_DATA data;
	LPMALLOC pMalloc;
	wchar_t *ret = NULL;
	if (UniIsEmptyStr(title))
	{
		title = NULL;
	}
	if (UniIsEmptyStr(default_dir))
	{
		default_dir = NULL;
	}

	Zero(&data, sizeof(data));
	data.default_dir = default_dir;

	Zero(display_name, sizeof(display_name));
	Zero(&info, sizeof(info));
	info.hwndOwner = hWnd;
	info.pidlRoot = NULL;
	info.pszDisplayName = display_name;
	info.lpszTitle = title;
	info.ulFlags = BIF_NEWDIALOGSTYLE | BIF_RETURNONLYFSDIRS | BIF_VALIDATE | BIF_SHAREABLE;
	info.lpfn = FolderDlgInnerCallbackW;
	info.lParam = (LPARAM)&data;

	if (SUCCEEDED(SHGetMalloc(&pMalloc)))
	{
		LPITEMIDLIST pidl;

		pidl = SHBrowseForFolderW(&info);

		if (pidl)
		{
			wchar_t tmp[MAX_PATH];

			if (SHGetPathFromIDListW(pidl, tmp))
			{
				ret = CopyUniStr(tmp);
			}

			pMalloc->Free(pidl);
		}

		pMalloc->Release();
	}

	return ret;
}