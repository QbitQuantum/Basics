bool system_alert_choose_scenario(char *chosen_dir)
{
#if defined(__WIN32__)
	BROWSEINFO bi = { 0 };
	TCHAR path[MAX_PATH];
	bi.lpszTitle = _T("Select a scenario to play:");
	bi.pszDisplayName = path;
	bi.lpfn = browse_callback_proc;
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE | 0x00000200; // no "New Folder" button
	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
	if (pidl)
	{
		SHGetPathFromIDList(pidl, path);
#ifdef UNICODE
		WideCharToMultiByte(CP_UTF8, 0, path, -1, chosen_dir, 256, NULL, NULL);
#else
		strncpy(chosen_dir, path, 255);
#endif
		LPMALLOC pMalloc = NULL;
		SHGetMalloc(&pMalloc);
		pMalloc->Free(pidl);
		pMalloc->Release();
		return true;
	}
#endif
	return false;
}