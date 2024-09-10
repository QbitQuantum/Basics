///////////////////////////////////////////////////////////////////////////////
// Note: on Unix/Linux, the file ID is a string encoding the combination of
// device number and inode; on Windows the file ID is simply the value
// _fullpath() returns on the path we're given.  The Unix/Linux version
// is preferable because it will work correctly even if there are hard
// links to log files; but there are no inodes on Windows, so we're
// doing what we can.
bool
GetFileID( const MyString &filename, MyString &fileID,
			CondorError &errstack )
{

		// Make sure the log file exists.  Even though we may later call
		// InitializeFile(), we have to make sure the file exists here
		// first so we make sure that the file exists and we can therefore
		// get an inode or real path for it.
		// We *don't* want to truncate the file here, though, because
		// we don't know for sure whether it's the first time we're seeing
		// it.
	if ( access( filename.Value(), F_OK ) != 0 ) {
		if ( !MultiLogFiles::InitializeFile( filename.Value(),
					false, errstack ) ) {
			errstack.pushf( "ReadMultipleUserLogs", UTIL_ERR_LOG_FILE,
						"Error initializing log file %s", filename.Value() );
			return false;
		}
	}

#ifdef WIN32
	char *tmpRealPath = realpath( filename.Value(), NULL );
	if ( !tmpRealPath ) {
		errstack.pushf( "ReadMultipleUserLogs", UTIL_ERR_LOG_FILE,
					"Error (%d, %s) getting real path for specified path %s",
					errno, strerror( errno ), filename.Value() );
		return false;
	}

	fileID = tmpRealPath;
	free( tmpRealPath );
#else
	StatWrapper swrap;
	if ( swrap.Stat( filename.Value() ) != 0 ) {
		errstack.pushf( "ReadMultipleUserLogs", UTIL_ERR_LOG_FILE,
					"Error getting inode for log file %s",
					filename.Value() );
		return false;
	}
	fileID.formatstr( "%llu:%llu", (unsigned long long)swrap.GetBuf()->st_dev,
				(unsigned long long)swrap.GetBuf()->st_ino );
#endif

	return true;
}