	// temporary folder for current user.
	DKLIB_API DKString DKTemporaryDirectory(void)
	{
		wchar_t path[MAX_PATH];
		DWORD ret = ::GetTempPathW(MAX_PATH, path);
		if (ret > MAX_PATH || ret == 0)
		{
			// error?
			ITEMIDLIST* pidl;
			if (SHGetSpecialFolderLocation(NULL, CSIDL_LOCAL_APPDATA | CSIDL_FLAG_CREATE, &pidl) == NOERROR &&
				SHGetPathFromIDListW(pidl, path))
			{
				return DKString(path);
			}
			DKERROR_THROW("Cannot get location of temporary directory!");
			return L"C:\\";
		}
		return DKString(path);
	}