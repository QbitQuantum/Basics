void FileStreamBuf::open(const std::string& path, std::ios::openmode mode)
{
	poco_assert (_handle == INVALID_HANDLE_VALUE);

	_path = path;
	_pos = 0;
	setMode(mode);
	resetBuffers();

	DWORD access = 0;
	if (mode & std::ios::in)
		access |= GENERIC_READ;
	if (mode & std::ios::out)
		access |= GENERIC_WRITE;

	DWORD shareMode = FILE_SHARE_READ;
	if (!(mode & std::ios::out))
		shareMode |= FILE_SHARE_WRITE;
		
	DWORD creationDisp = OPEN_EXISTING;
	if (mode & std::ios::trunc)
		creationDisp = CREATE_ALWAYS;
	else if (mode & std::ios::out)
		creationDisp = OPEN_ALWAYS;

	DWORD flags = FILE_ATTRIBUTE_NORMAL;
	
#if defined (POCO_WIN32_UTF8)
	std::wstring utf16Path;
	UnicodeConverter::toUTF16(path, utf16Path);
	_handle = CreateFile2(utf16Path.c_str(), access, shareMode, creationDisp, NULL);
#else
	_handle = CreateFileA(path.c_str(), access, shareMode, NULL, creationDisp, flags, NULL);
#endif

	if (_handle == INVALID_HANDLE_VALUE)
		File::handleLastError(_path);
		
	if ((mode & std::ios::ate) || (mode & std::ios::app))
		seekoff(0, std::ios::end, mode);
}