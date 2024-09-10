BackgroundLoader::~BackgroundLoader()
{
	if( !g_bEnableBackgroundLoading )
		return;

	Abort();

	m_bShutdownThread = true;
	m_StartSem.Post();
	m_LoadThread.Wait();

	/* Delete all leftover cached files. */
	map<CString,int>::iterator it;
	for( it = m_FinishedRequests.begin(); it != m_FinishedRequests.end(); ++it )
		FILEMAN->Remove( GetCachePath( it->first ) );

	/* m_sCachePathPrefix should be filled with several empty directories.  Delete
	 * them and m_sCachePathPrefix, so we don't leak them. */
	DeleteEmptyDirectories( m_sCachePathPrefix );
}