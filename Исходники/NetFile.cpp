BOOL CNetFile::DoThread(LPVOID pData)
{_STT();
	if ( !m_bUpload )
	{
		m_dwTransferStatus = NETFILE_DS_DOWNLOADING;

		// Post callback
		DoCallback( (WPARAM)m_dwTransferStatus, (LPARAM)this );

		DWORD ready = 0;

		// Get available data
		if ( !InternetQueryDataAvailable( m_hFile, &ready, 0, 0 ) )
		{	m_dwTransferError = GetLastError();
			return FALSE;
		} // end if

		// Quit if no more data
		if ( ready == 0 ) return FALSE;

		// Get total length if needed
		if ( m_bGetTotalLength )
		{	m_bGetTotalLength = FALSE;

			// Send the query command
			char bufQuery[ 32 ] = "0";
			DWORD dwLengthBufQuery = sizeof( bufQuery );
			DWORD dwHeaderIndex = 0;
			HttpQueryInfo( m_hFile, HTTP_QUERY_CONTENT_LENGTH,
							bufQuery, &dwLengthBufQuery, &dwHeaderIndex );

			// Did we find the header?
			if ( dwHeaderIndex != ERROR_HTTP_HEADER_NOT_FOUND )

				// Convert length from ASCII string to a DWORD.
				m_dwTotalLength = (DWORD)atol( bufQuery );

		} // end if

		while ( ready )
		{
			// Don't byte of more than this computer can chew
			DWORD size = ( ready < m_dwBlockSize ) ? ready : m_dwBlockSize;

			// Allocate a buffer to save new data
			LPBYTE buf = new BYTE[ size + 1 ];
			if ( buf == NULL )
			{
				m_dwTransferError = ERROR_NOT_ENOUGH_MEMORY;
				return FALSE;
			} // end if

			// Attempt to read new data
			DWORD	read = 0;
			if ( !InternetReadFile( m_hFile, buf, size, &read ) )
			{			   
				delete [] buf;
				m_dwTransferError = GetLastError();
				return FALSE;
			} // end if

			// Check for end of file
			if ( read == 0 )
			{
				m_dwTransferStatus = NETFILE_DS_DONE;
				return FALSE;
			} // end if

			if ( m_bMem )
			{
				if ( m_pMem != NULL )
				{
					LPBYTE temp = new BYTE[ m_dwDataRead + size + 1 ];
					if ( temp == NULL )
					{
						m_dwTransferError = ERROR_NOT_ENOUGH_MEMORY;
						return FALSE;
					} // end if
					memcpy( temp, m_pMem, m_dwDataRead );
					memcpy( &temp[ m_dwDataRead ], buf, size );
					temp[ m_dwDataRead + size ] = NULL;
					delete [] m_pMem;
					m_pMem = temp;
				} // end if
				else
				{
					m_pMem = new BYTE[ size + 1 ];
					if ( m_pMem == NULL )
					{
						m_dwTransferError = ERROR_NOT_ENOUGH_MEMORY;
						return FALSE;
					} // end if
					memcpy( m_pMem, buf, size );
					m_pMem[ size ] = NULL;
				} // end else
			} // end if

			// Write the data to the file
			else if ( !m_local.Write( buf, read ) )
			{
				delete [] buf;
				m_dwTransferError = GetLastError();
				return FALSE;
			} // end if

			// Delete buffer
			delete [] buf;

			// Add this to data received
			m_dwDataRead += size;

			// Read the next block
			ready -= size;

		} // end while

	}

	else
	{		
		// Do we have any memory
		if ( m_pMem == NULL || m_dwMemSize == 0 )
		{	m_dwTransferStatus = NETFILE_DS_ERROR;
			return FALSE;
		} // end if

		m_dwTransferStatus = NETFILE_DS_UPLOADING;

		// Post callback
		DoCallback( (WPARAM)m_dwTransferStatus, (LPARAM)this );

		// Don't byte of more than this computer can chew
		DWORD left = m_dwMemSize - m_dwDataWritten;
		DWORD write = ( left < m_dwBlockSize ) ? left : m_dwBlockSize;
		DWORD written = 0;
		
		// Attempt to write some data
		if ( !InternetWriteFile( m_hFile, &m_pMem[ m_dwDataWritten ], write, &written ) )
		{
			m_dwTransferStatus = NETFILE_DS_ERROR;
			m_dwTransferError = GetLastError();
			return FALSE;
		} // end if

		// Count this data
		m_dwDataWritten += written;

		// Have we written all the data?
		if ( m_dwDataWritten == m_dwMemSize )
		{
			m_dwTransferStatus = NETFILE_DS_DONE;
			return FALSE;
		} // end if

	} // end else

	// Wait a bit
	Sleep( 15 );

	// Keep going
	return TRUE; 
}