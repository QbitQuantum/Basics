BOOL CNeighbour::Connect(LPCTSTR lpPipeName, DWORD nMaxInstances, DWORD nTimeOut)
{
	if ( m_hPipe != INVALID_HANDLE_VALUE ) return FALSE;
	
	SECURITY_ATTRIBUTES sa;
	PSECURITY_DESCRIPTOR pSD;
	
	pSD = (PSECURITY_DESCRIPTOR) LocalAlloc(LPTR,SECURITY_DESCRIPTOR_MIN_LENGTH);
	if ( ! InitializeSecurityDescriptor(pSD, SECURITY_DESCRIPTOR_REVISION) )
	{
		LocalFree( (HLOCAL)pSD ); return FALSE;
	}
	if ( ! SetSecurityDescriptorDacl(pSD, TRUE, (PACL) NULL, FALSE) )
	{
		LocalFree( (HLOCAL)pSD ); return FALSE;
	}
	
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = pSD; 
	sa.bInheritHandle = TRUE;

	m_hPipe = CreateNamedPipe( lpPipeName, PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
		PIPE_TYPE_BYTE | PIPE_READMODE_BYTE, nMaxInstances, TEMP_BUFFER, TEMP_BUFFER, nTimeOut, &sa );
	
	if ( m_hPipe == INVALID_HANDLE_VALUE ) return FALSE;
	
	ZeroMemory( &m_pOverlapped, sizeof(OVERLAPPED) );
	m_pOverlapped.hEvent = m_pWakeup;
	
	ConnectNamedPipe( m_hPipe, &m_pOverlapped );
TRACE("CreateNamedPipe: %s\n", lpPipeName);
	
	StartThread();
	return TRUE;
}