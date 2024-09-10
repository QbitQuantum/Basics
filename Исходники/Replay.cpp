void CReplay :: AddTimeSlot( uint16_t timeIncrement, queue<CIncomingAction *> actions )
{
	BYTEARRAY Block;
	Block.push_back( REPLAY_TIMESLOT );
	UTIL_AppendByteArray( Block, (uint16_t)0, false );
	UTIL_AppendByteArray( Block, timeIncrement, false );

	while( !actions.empty( ) )
	{
		CIncomingAction *Action = actions.front( );
		actions.pop( );
		BYTEARRAY ActionData = Action->GetAction( );
		Block.push_back( Action->GetPID( ) );
		UTIL_AppendByteArray( Block, (uint16_t)ActionData.size( ), false );
		UTIL_AppendByteArray( Block, ActionData );
	}

	// assign length

	BYTEARRAY LengthBytes = UTIL_CreateByteArray( (uint16_t)( Block.size( ) - 3 ), false );
	Block[1] = LengthBytes[0];
	Block[2] = LengthBytes[1];
	m_Blocks.push( Block );
}