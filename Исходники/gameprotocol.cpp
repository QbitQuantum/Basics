BYTEARRAY CGameProtocol :: SEND_W3GS_INCOMING_ACTION( queue<CIncomingAction*> actions, uint16_t sendInterval )
{
	BYTEARRAY packet;
	packet.push_back( W3GS_HEADER_CONSTANT );				// W3GS header constant
	packet.push_back( W3GS_INCOMING_ACTION );				// W3GS_INCOMING_ACTION
	packet.push_back( 0 );									// packet length will be assigned later
	packet.push_back( 0 );									// packet length will be assigned later
	UTIL_AppendByteArray( packet, sendInterval, false );	// send interval

	// create subpacket
	if( !actions.empty() )
	{
		BYTEARRAY subpacket;

		while( !actions.empty() )
		{
			CIncomingAction* Action = actions.front( );
			actions.pop( );
			subpacket.push_back( Action->GetPID() );
			UTIL_AppendByteArray( subpacket, static_cast<uint16_t>( Action->GetAction()->size() ), false );
			UTIL_AppendByteArrayFast( subpacket, *Action->GetAction() );
		}

		// calculate crc (we only care about the first 2 bytes though)
		BYTEARRAY crc32 = UTIL_CreateByteArray( m_GHost->m_CRC->FullCRC( (unsigned char*)( string( subpacket.begin(), subpacket.end() ).c_str() ), subpacket.size() ), false );
		crc32.resize( 2 );

		// finish subpacket
		UTIL_AppendByteArrayFast( packet, crc32 );			// crc
		UTIL_AppendByteArrayFast( packet, subpacket );		// subpacket
	}

	AssignLength( packet );
	
	return packet;
}