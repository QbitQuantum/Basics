FileWatchdog::~FileWatchdog() {
	memset( m_WorkingDirectory, 0, FILENAME_MAX * sizeof( char ) );

	CancelIoEx( m_Watchdog, nullptr );
	CloseHandle( m_Watchdog );
	m_Watchdog = nullptr;

	if( m_ToReload.size() ) {
		file_watched_t* file = m_ToReload.front();

		while( file ) {
			m_ToReload.pop();
			SAFE_DELETE( file )
			if( !m_ToReload.size() ) break;
			file = m_ToReload.front();
		}

		file = nullptr;
	}