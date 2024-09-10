BOOL CFileNavDlg::GetRecentDirectory(CString& strRecent)
{
	TCHAR lpszPath[MAX_PATH];
	LPITEMIDLIST pidl;
	SHGetSpecialFolderLocation(m_hWnd, CSIDL_RECENT, &pidl);
	SHGetPathFromIDList(pidl, lpszPath);
	strRecent = lpszPath;

	return TRUE;
}