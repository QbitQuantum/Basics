 std::string BrowseFolder()
{
	TCHAR path[MAX_PATH];

	BROWSEINFO bi = { 0 };
	bi.lpszTitle = ("Please select the folder path...");

	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

	if (pidl != 0)
	{
		//get the name of the folder and put it in path
		SHGetPathFromIDList(pidl, path);

		//free memory used
		IMalloc * imalloc = 0;
		if (SUCCEEDED(SHGetMalloc(&imalloc)))
		{
			imalloc->Free(pidl);
			imalloc->Release();
		}
		//std::wstring arr_w(path);
		//std::string paths(arr_w.begin(), arr_w.end());
		return path;
	}

	return "";
}