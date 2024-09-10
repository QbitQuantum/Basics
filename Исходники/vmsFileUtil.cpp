void vmsFileUtil::GetAppDataPath(LPCSTR pszAppName, LPSTR szPath)
{
	LPITEMIDLIST pidl = NULL;
	SHGetSpecialFolderLocation (NULL, CSIDL_APPDATA, &pidl);
	SHGetPathFromIDList (pidl, szPath);
	
	vmsFileUtil::MakePathOK (szPath);
	lstrcat (szPath, pszAppName);
	lstrcat (szPath, "\\");
}