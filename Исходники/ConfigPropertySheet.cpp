unsigned WINAPI
CConfigPropertySheet::WatchRegistry ( LPVOID inParam )
{
	bool done = false;

	CConfigPropertySheet * self = reinterpret_cast<CConfigPropertySheet*>(inParam);
	check( self );

	while ( !done )
	{
		RegNotifyChangeKeyValue( self->m_statusKey, TRUE, REG_NOTIFY_CHANGE_LAST_SET, NULL, FALSE );

		EnterCriticalSection( &self->m_lock );

		done = ( self->m_statusKey == NULL ) ? true : false;

		if ( !done )
		{
			self->PostMessage( WM_REGISTRYCHANGED, 0, 0 );
		}

		LeaveCriticalSection( &self->m_lock );
	}

	SetEvent( self->m_threadExited );

	return 0;
}