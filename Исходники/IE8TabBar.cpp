LRESULT CIETabBar::OnIconChange(WPARAM wParam,LPARAM lParam)
{
	WCHAR *pszFilePath = (WCHAR *)lParam;
	PVOID PageID = (PVOID)wParam;

	UpdateTabItemIcon(
		PageID,
		(HICON)LoadImageW(AfxGetInstanceHandle(),pszFilePath,IMAGE_ICON,16,16,LR_LOADFROMFILE)
		);
	delete pszFilePath;

	return 0;
}