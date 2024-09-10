axStatus axFile::unlock() {
	if( ! isValid() ) { assert(false);	return axStatus_Std::not_initialized; }

    DWORD len = 0xffffffff;
	OVERLAPPED offset;
	ax_memset( offset, 0 );

	if (!UnlockFileEx( h_, 0, len, len, &offset)) {
		DEBUG_ax_log_win32_error("File::unlock");
		assert(false);
		return axStatus_Std::File_lock_error;
	}
	return 0;
}