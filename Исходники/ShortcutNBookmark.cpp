CString CShortcutNBookmark::GetSpecialFolderLocation(int nFolder)
{
	CString Result;
	
	LPITEMIDLIST pidl;
	HRESULT hr = SHGetSpecialFolderLocation(NULL, nFolder, &pidl);
	
	if (SUCCEEDED(hr))
	{
		// Convert the item ID list's binary
		// representation into a file system path
		char szPath[_MAX_PATH];
		
		if (SHGetPathFromIDList(pidl, szPath))
		{
			Result = szPath;
		}
		else
		{
			ATLASSERT(FALSE);
		}
	}
	else
	{
		ATLASSERT(FALSE);
	}
	
	return Result;
}