bool File::Write(const File& _file, const char* _path)
{
	if (!_path) {
		_path = _file.getPath();
	}
	APT_ASSERT(_path);

	bool  ret  = false;
	char* data = nullptr;
	DWORD err  = 0;
	
 	HANDLE h = CreateFile(
		_path,
		GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);
	if (h == INVALID_HANDLE_VALUE) {
		err = GetLastError();
		if (err == ERROR_PATH_NOT_FOUND) {
			if (FileSystem::CreateDir(_path)) {
				return Write(_file, _path);
			} else {
				return false;
			}
		} else {
			goto File_Write_end;
		}
	}

	DWORD bytesWritten;
	if (!WriteFile(h, _file.getData(), (DWORD)_file.getDataSize(), &bytesWritten, NULL)) {
		goto File_Write_end;
	}
	APT_ASSERT(bytesWritten == _file.getDataSize());

	ret = true;

File_Write_end:
	if (!ret) {
		APT_LOG_ERR("Error writing '%s':\n\t%s", _path, GetPlatformErrorString((uint64)err));
		APT_ASSERT(false);
	}
	if (h != INVALID_HANDLE_VALUE) {
		APT_PLATFORM_VERIFY(CloseHandle(h));
	}
	return ret;
}