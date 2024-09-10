void CSettingsDictPage::OnBrowseLocation()
{
	TCHAR szPath[_MAX_PATH];
	CString strTitle = LoadString(IDS_DICT_LOCATION_PROMPT);

	BROWSEINFO info;
	ZeroMemory(&info, sizeof(info));
	info.hwndOwner = m_hWnd;
	info.pszDisplayName = szPath;
	info.lpszTitle = strTitle;
	info.ulFlags = BIF_RETURNONLYFSDIRS | BIF_VALIDATE | BIF_USENEWUI;
	info.lpfn = BrowseCallbackProc;
	info.lParam = (LPARAM) this;

	LPITEMIDLIST pItem = SHBrowseForFolder(&info);
	if (pItem == NULL)
		return;

	if (SHGetPathFromIDList(pItem, szPath))
	{
		PathRemoveBackslash(szPath);
		m_strDictLocation = szPath;
		UpdateData(false);
	}

	LPMALLOC pMalloc;
	if (SUCCEEDED(SHGetMalloc(&pMalloc)))
		pMalloc->Free(pItem);
}