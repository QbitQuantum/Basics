	// build the final pool
	void GetTableAndPool( CUtlVector< unsigned int > &offsets, CUtlBuffer &buffer )
	{
		offsets.Purge();
		buffer.Purge();

		offsets.EnsureCapacity( m_StringMap.GetNumStrings() );
		buffer.EnsureCapacity( m_nOffset );

		unsigned int currentOffset = 0;
		for ( int i = 0; i < m_StringMap.GetNumStrings(); i++ )
		{
			offsets.AddToTail( currentOffset );

			const char *pString = m_StringMap.String( i );
			buffer.Put( pString, strlen( pString ) + 1 ); 

			currentOffset += strlen( pString ) + 1;
		}
		Assert( currentOffset == m_nOffset );

		// align string pool to end on dword boundary
		while ( buffer.TellMaxPut() & 0x03 )
		{
			buffer.PutChar( '\0' );
			m_nOffset++;
		}
	}