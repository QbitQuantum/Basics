	static std::string FindUserDir()
	{
		wchar_t appdata_path[MAX_PATH];
		if (SHGetFolderPathW(0, CSIDL_PERSONAL, 0, SHGFP_TYPE_CURRENT, appdata_path) != S_OK) {
			Output("Couldn't get user documents folder path\n");
			exit(-1);
		}

		std::wstring path(appdata_path);
		path += L"/Pioneersp";

		if (!PathFileExistsW(path.c_str())) {
			if (SHCreateDirectoryExW(0, path.c_str(), 0) != ERROR_SUCCESS) {
				std::string utf8path = transcode_utf16_to_utf8(path);
				Output("Couldn't create user game folder '%s'", utf8path.c_str());
				exit(-1);
			}
		}

		return transcode_utf16_to_utf8(path);
	}