void ShowUserStreams( PVOID pMiniDump, int streamNum ) 
{
	// Check parameters 

	if( pMiniDump == 0 ) 
	{
		_ASSERTE( !_T("Invalid parameter.") ); 
		return; 
	}


	// Show the contents of user data streams 

		// First stream 

	ULONG StreamID = cFirstStreamID + streamNum; 

	PMINIDUMP_DIRECTORY  pMiniDumpDir  = 0; 
	PVOID                pStream       = 0; 
	ULONG                StreamSize    = 0; 

	if( !MiniDumpReadDumpStream( pMiniDump, StreamID, &pMiniDumpDir, 
	                             &pStream, &StreamSize ) ) 
	{
		DWORD ErrCode = GetLastError(); 
		if( ErrCode != 0 ) // 0 -> no such stream in the dump 
			_tprintf( _T("Error: MiniDumpReadDumpStream failed. Error: %u \n"), ErrCode ); 
		else 
			_tprintf( _T("Stream (id %u) not found in the minidump.\n"), StreamID ); 
	}
	else 
	{
		// Show the contents 

		if( ( pStream == 0 ) || ( StreamSize == 0 ) ) 
		{
			_tprintf( _T("Invalid stream (id %u).\n"), StreamID ); 
		}
		else if( IsBadStringPtrA( (LPCSTR)pStream, StreamSize ) ) 
		{
			_tprintf( _T("Invalid stream data (id %u).\n"), StreamID ); 
		}
		else 
		{
			_tprintf( _T("%s\n"), pStream ); 
		}
	}

}