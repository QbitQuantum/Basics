BOOL factor_vm::windows_stat(vm_char *path)
{
	BY_HANDLE_FILE_INFORMATION bhfi;
	HANDLE h = CreateFileW(path,
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_FLAG_BACKUP_SEMANTICS,
			NULL);

	if(h == INVALID_HANDLE_VALUE)
	{
		// FindFirstFile is the only call that can stat c:\pagefile.sys
		WIN32_FIND_DATA st;
		HANDLE h;

		if(INVALID_HANDLE_VALUE == (h = FindFirstFile(path, &st)))
			return false;
		FindClose(h);
		return true;
	}
	BOOL ret = GetFileInformationByHandle(h, &bhfi);
	CloseHandle(h);
	return ret;
}