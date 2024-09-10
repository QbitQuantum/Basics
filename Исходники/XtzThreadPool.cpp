	CXtzThreadPool::CXtzThreadPool( ) : m_nThread( 0 )
	{
		SYSTEM_INFO sysInfo;
		GetSystemInfo( &sysInfo );

		CreateThreadPool( sysInfo.dwNumberOfProcessors );
	}