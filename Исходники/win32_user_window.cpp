KListRef Win32UserWindow::SelectDirectory(
	bool multiple,
	std::string& title,
	std::string& path,
	std::string& defaultName)
{
	KListRef results = new StaticBoundList();

	BROWSEINFO bi = { 0 };
	std::wstring titleW = UTF8ToWide(title);
	bi.lpszTitle = titleW.c_str();
	bi.hwndOwner = this->windowHandle;
	bi.ulFlags = BIF_RETURNONLYFSDIRS;
	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

	if (pidl != 0)
	{
		wchar_t in_path[MAX_PATH];
		if (SHGetPathFromIDList(pidl, in_path))
		{
			std::wstring inPathW = in_path;
			std::string inPath = WideToUTF8(inPathW);
			results->Append(Value::NewString(inPath));
		}

		IMalloc * imalloc = 0;
		if (SUCCEEDED(SHGetMalloc(&imalloc)))
		{
			imalloc->Free(pidl);
			imalloc->Release();
		}
	}
	return results;
}