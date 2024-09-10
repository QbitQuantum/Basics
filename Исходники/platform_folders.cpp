static std::string GetWindowsFolder(int folderId, const char* errorMsg) {
	wchar_t szPath[MAX_PATH];
	szPath[0] = 0;
	if ( !SUCCEEDED( SHGetFolderPathW( NULL, folderId, NULL, 0, szPath ) ) )
	{
		throw std::runtime_error(errorMsg);
	}
	return win32_utf16_to_utf8(szPath);
}