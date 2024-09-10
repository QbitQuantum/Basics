static HANDLE open_device(const char *path, BOOL enumerate)
{
	HANDLE handle;
	DWORD desired_access = (enumerate)? 0: (GENERIC_WRITE | GENERIC_READ);
	DWORD share_mode = (enumerate)?
	                      FILE_SHARE_READ|FILE_SHARE_WRITE:
	                      FILE_SHARE_READ;

	handle = CreateFileA(path,
		desired_access,
		share_mode,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_OVERLAPPED,/*FILE_ATTRIBUTE_NORMAL,*/
		0);

  CancelIo(handle);

	return handle;
}