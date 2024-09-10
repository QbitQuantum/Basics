void CBlockMember::SetData( void *data, int size, CIcarus* icarus)
{
	IGameInterface* game = icarus->GetGame();
	if ( m_data )
		game->Free( m_data );

	m_data = game->Malloc( size );
	memcpy( m_data, data, size );
	m_size = size;
}