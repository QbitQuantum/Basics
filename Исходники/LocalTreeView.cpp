wxString CLocalTreeView::GetSpecialFolder(int folder, int &iconIndex, int &openIconIndex)
{
	LPITEMIDLIST list;
	if (SHGetSpecialFolderLocation((HWND)GetHandle(), folder, &list) != S_OK)
		return _T("");

	SHFILEINFO shFinfo;
	if (!SHGetFileInfo((LPCTSTR)list, 0, &shFinfo, sizeof(shFinfo), SHGFI_PIDL | SHGFI_ICON | SHGFI_SMALLICON))
		return _T("");

	DestroyIcon(shFinfo.hIcon);
	iconIndex = shFinfo.iIcon;

	if (!SHGetFileInfo((LPCTSTR)list, 0, &shFinfo, sizeof(shFinfo), SHGFI_PIDL | SHGFI_ICON | SHGFI_SMALLICON | SHGFI_OPENICON | SHGFI_DISPLAYNAME))
		return _T("");

	DestroyIcon(shFinfo.hIcon);
	openIconIndex = shFinfo.iIcon;

	wxString name = shFinfo.szDisplayName;

	LPMALLOC pMalloc;
    SHGetMalloc(&pMalloc);

	if (pMalloc)
	{
		pMalloc->Free(list);
		pMalloc->Release();
	}
	else
		wxLogLastError(wxT("SHGetMalloc"));

	return name;
}