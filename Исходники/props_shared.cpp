void CGameGibManager::AddGibToLRU( CBaseAnimating *pEntity )
{
	int i, next;

	if ( pEntity == NULL )
		return;

	//Find stale gibs.
	for ( i = m_LRU.Head(); i < m_LRU.InvalidIndex(); i = next )
	{
		next = m_LRU.Next(i);

		if ( m_LRU[i].Get() == NULL )
		{
			m_LRU.Remove(i);
		}
	}

	// We're not tracking gibs at the moment
	if ( m_iCurrentMaxPieces <= 0 )
		return;

	while ( m_LRU.Count() >= m_iCurrentMaxPieces )
	{
		i = m_LRU.Head();

		//TODO: Make this fade out instead of pop.
		UTIL_Remove( m_LRU[i] );
		m_LRU.Remove(i);
	}
	
	m_LRU.AddToTail( pEntity );
	m_iLastFrame = gpGlobals->framecount;
}