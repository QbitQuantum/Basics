std::uint64_t GetCompressedFileSize_filename( const std::wstring path ) {
	ULARGE_INTEGER ret;
	const auto last_err_old = GetLastError( );
	ret.QuadPart = 0;//zero initializing this is critical!
	ret.LowPart = GetCompressedFileSizeW( path.c_str( ), &ret.HighPart );
	const auto last_err = GetLastError( );
	if ( ret.LowPart == INVALID_FILE_SIZE ) {
		if ( ret.HighPart != NULL ) {
			if ( ( last_err != NO_ERROR ) && ( last_err != last_err_old ) ) {
				fwprintf( stderr, L"Error! Filepath: %s, Filepath length: %i, GetLastError: %s\r\n", path.c_str( ), int( path.length( ) ), handyDandyErrMsgFormatter( last_err ).c_str( ) );
				return UINT64_MAX;// IN case of an error return size from CFileFind object
				}
			fwprintf( stderr, L"WTF ERROR! Filepath: %s, Filepath length: %i, GetLastError: %s\r\n", path.c_str( ), int( path.length( ) ), handyDandyErrMsgFormatter( last_err ).c_str( ) );
			return UINT64_MAX;
			}
		else {
			if ( ( last_err != NO_ERROR ) && ( last_err != last_err_old ) ) {
				fwprintf( stderr, L"Error! Filepath: %s, Filepath length: %i, GetLastError: %s\r\n", path.c_str( ), int( path.length( ) ), handyDandyErrMsgFormatter( last_err ).c_str( ) );
				return UINT64_MAX;
				}
			return ret.QuadPart;
			}
		}
	return ret.QuadPart;
	}