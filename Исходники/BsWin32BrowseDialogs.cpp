	void setDefaultPath(IFileDialog* dialog, const Path& defaultPath)
	{
		WString pathStr = UTF8::toWide(defaultPath.toString());
		const wchar_t* defaultPathW = pathStr.c_str();

		IShellItem* folder;
		HRESULT result = SHCreateItemFromParsingName(defaultPathW, NULL, IID_PPV_ARGS(&folder));

		// Valid non results.
		if (result == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND) || result == HRESULT_FROM_WIN32(ERROR_INVALID_DRIVE))
			return;

		if (!SUCCEEDED(result))
			return;

		dialog->SetFolder(folder);
		folder->Release();
	}