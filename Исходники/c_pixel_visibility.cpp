void CPixelVisibilitySystem::FreeSet( unsigned short node )
{
	m_setList.Unlink( m_activeSetsList, node );
	m_setList.LinkToHead( m_freeSetsList, node );
	m_setList[node].serial++;
}