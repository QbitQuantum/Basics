/* map a file into system meory, return the file size */
size_t plat_mmap_create( plat_mmap *handle, const char *file, int fileAccessAttr )
{
	LARGE_INTEGER sizet;
	/* check error(s) */
	if ( ! handle )
		return 0;

	handle->fd_map = NULL;
	handle->address = NULL;

	if ( FLAG_ATTRIBUTE_READ & fileAccessAttr ) {
#ifdef _WIN32_WCE
		handle->fd_file = CreateFileForMappingA(
				file,
				GENERIC_READ,
				FILE_SHARE_READ,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL );
#else /* !_WIN32_WCE */
		handle->fd_file = CreateFileA(
				file,
				GENERIC_READ,
				FILE_SHARE_READ,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_READONLY | FILE_FLAG_RANDOM_ACCESS,
				0 );
#endif /* _WIN32_WCE */

		if ( INVALID_HANDLE_VALUE == handle->fd_file )
			return 0;

		sizet.LowPart = GetFileSize( handle->fd_file, (LPDWORD) &sizet.HighPart );
		handle->fd_map = CreateFileMappingA(
				handle->fd_file,
				NULL,
				PAGE_READONLY,
				sizet.HighPart,
				sizet.LowPart,
				0 );
	}
	else {
#ifdef _WIN32_WCE
		handle->fd_file = CreateFileForMappingA(
				file,
				GENERIC_WRITE | GENERIC_READ,
				FILE_SHARE_WRITE,
				NULL,
				CREATE_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
#else /* !_WIN32_WCE */
		handle->fd_file = CreateFileA(
				file,
				GENERIC_WRITE | GENERIC_READ,
				FILE_SHARE_WRITE,
				NULL,
				CREATE_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				0);
#endif /* _WIN32_WCE */

		if ( INVALID_HANDLE_VALUE == handle->fd_file )
			return 0;

		sizet.LowPart  = 0;
		sizet.HighPart = 1;
		handle->fd_map = CreateFileMapping(
				handle->fd_file,
				NULL,
				PAGE_READWRITE,
				0,
				sizet.LowPart,
				0 );
		sizet.LowPart  = 1024 * 1024 * 1024;
		sizet.HighPart = 0;

		while ( ! handle->fd_map ) {
			DWORD error;
			handle->fd_map = CreateFileMapping(
					handle->fd_file,
					NULL,
					PAGE_READWRITE,
					0,
					sizet.LowPart,
					0 );
			error = GetLastError();

			if ( ERROR_NOT_ENOUGH_MEMORY == error || ERROR_DISK_FULL == error )
				sizet.LowPart /= 2;
			else
				break;
		}
	}

	handle->fAccessAttr = fileAccessAttr;

	if ( FLAG_ATTRIBUTE_READ & fileAccessAttr || 16 * 1024 * 1024 <= sizet.LowPart ) {
		if ( handle->fd_map )
			return (size_t) sizet.QuadPart;
	}

	plat_mmap_close( handle );

	return 0;
}