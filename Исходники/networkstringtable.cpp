//-----------------------------------------------------------------------------
// Purpose: Parse string update
//-----------------------------------------------------------------------------
void CNetworkStringTable::ParseUpdate( bf_read &buf, int entries )
{
	int lastEntry = -1;

	CUtlVector< StringHistoryEntry > history;

	for (int i=0; i<entries; i++)
	{
		int entryIndex = lastEntry + 1;

		if ( !buf.ReadOneBit() )
		{
			entryIndex = buf.ReadUBitLong( GetEntryBits() );
		}

		lastEntry = entryIndex;
		
		if ( entryIndex < 0 || entryIndex >= GetMaxStrings() )
		{
			Host_Error( "Server sent bogus string index %i for table %s\n", entryIndex, GetTableName() );
		}

		const char *pEntry = NULL;
		char entry[ 1024 ]; 
		char substr[ 1024 ];

		if ( buf.ReadOneBit() )
		{
			bool substringcheck = buf.ReadOneBit() ? true : false;

			if ( substringcheck )
			{
				int index = buf.ReadUBitLong( 5 );
				int bytestocopy = buf.ReadUBitLong( SUBSTRING_BITS );
				Q_strncpy( entry, history[ index ].string, bytestocopy + 1 );
				buf.ReadString( substr, sizeof(substr) );
				Q_strncat( entry, substr, sizeof(entry), COPY_ALL_CHARACTERS );
			}
			else
			{
				buf.ReadString( entry, sizeof( entry ) );
			}

			pEntry = entry;
		}
		
		// Read in the user data.
		unsigned char tempbuf[ CNetworkStringTableItem::MAX_USERDATA_SIZE ];
		memset( tempbuf, 0, sizeof( tempbuf ) );
		const void *pUserData = NULL;
		int nBytes = 0;

		if ( buf.ReadOneBit() )
		{
			if ( IsUserDataFixedSize() )
			{
				// Don't need to read length, it's fixed length and the length was networked down already.
				nBytes = GetUserDataSize();
				Assert( nBytes > 0 );
				tempbuf[nBytes-1] = 0; // be safe, clear last byte
				buf.ReadBits( tempbuf, GetUserDataSizeBits() );
			}
			else
			{
				nBytes = buf.ReadUBitLong( CNetworkStringTableItem::MAX_USERDATA_BITS );
				ErrorIfNot( nBytes <= sizeof( tempbuf ),
					("CNetworkStringTableClient::ParseUpdate: message too large (%d bytes).", nBytes)
				);

				buf.ReadBytes( tempbuf, nBytes );
			}

			pUserData = tempbuf;
		}

		// Check if we are updating an old entry or adding a new one
		if ( entryIndex < GetNumStrings() )
		{
			SetStringUserData( entryIndex, nBytes, pUserData );
#ifdef _DEBUG
			if ( pEntry )
			{
				Assert( !Q_strcmp( pEntry, GetString( entryIndex ) ) ); // make sure string didn't change
			}
#endif
			pEntry = GetString( entryIndex ); // string didn't change
		}
		else
		{
			// Grow the table (entryindex must be the next empty slot)
			Assert( (entryIndex == GetNumStrings()) && (pEntry != NULL) );
				
			if ( pEntry == NULL )
			{
				Msg("CNetworkStringTable::ParseUpdate: NULL pEntry, table %s, index %i\n", GetTableName(), entryIndex );
				pEntry = "";// avoid crash because of NULL strings
			}

			AddString( true, pEntry, nBytes, pUserData );
		}

		if ( history.Count() > 31 )
		{
			history.Remove( 0 );
		}

		StringHistoryEntry she;
		Q_strncpy( she.string, pEntry, sizeof( she.string ) );
		history.AddToTail( she );
	}
}