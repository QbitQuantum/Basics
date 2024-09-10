void NoteField::CacheNoteSkin( const CString &sNoteSkin_ )
{
	CString sNoteSkin = sNoteSkin_;
	sNoteSkin.ToLower();

	if( m_NoteDisplays.find(sNoteSkin) != m_NoteDisplays.end() )
		return;

	LockNoteSkin l( sNoteSkin );
		
	LOG->Trace("NoteField::CacheNoteSkin: cache %s", sNoteSkin.c_str() );
	NoteDisplayCols *nd = new NoteDisplayCols( GAMESTATE->GetCurrentStyle()->m_iColsPerPlayer );
	for( int c=0; c<GAMESTATE->GetCurrentStyle()->m_iColsPerPlayer; c++ ) 
		nd->display[c].Load( c, m_pPlayerState, m_fYReverseOffsetPixels );
	nd->m_ReceptorArrowRow.Load( m_pPlayerState, m_fYReverseOffsetPixels );
	nd->m_GhostArrowRow.Load( m_pPlayerState, m_fYReverseOffsetPixels );

	m_NoteDisplays[ sNoteSkin ] = nd;
}