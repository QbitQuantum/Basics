CNetCom* CNetMgr::CreateNewSession()
{_STT();
	// Acquire lock
	CTlLocalLock ll( *this );
	if ( !ll.IsLocked() ) return NULL;

	// Delete invalid connections
	Cleanup();

	// Create specialized session object
	CNetCom* pNc = CreateSessionObject();
	if ( pNc == NULL ) return FALSE;

	// Initialize
	InitSession( pNc );

	return pNc;
}