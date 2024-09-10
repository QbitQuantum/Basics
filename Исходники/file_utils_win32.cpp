	std::string FileUtils::Dirname(std::string path)
	{
		wchar_t pathBuffer[_MAX_PATH];
		wchar_t drive[_MAX_DRIVE];
		wchar_t dir[_MAX_DIR];
		wchar_t fname[_MAX_FNAME];
		wchar_t ext[_MAX_EXT];

		std::wstring widePath = UTILS_NS::UTF8ToWide(path);
		wcsncpy(pathBuffer, widePath.c_str(), MAX_PATH - 1);
		pathBuffer[MAX_PATH - 1] = '\0';

		_wsplitpath(pathBuffer, drive, dir, fname, ext);
		if (dir[wcslen(dir)-1] == '\\')
			dir[wcslen(dir)-1] = '\0';

		std::wstring dirname = drive;
		dirname += std::wstring(dir);
		return UTILS_NS::WideToUTF8(dirname);
	}