// picks a number of spawners randomly from this spawngroup
void CASW_Spawn_Group::PickSpawnersRandomly( int nNumSpawners, bool bIncludeRecentlySpawned, CUtlVector< CASW_Base_Spawner* > *pSpawners )
{
	pSpawners->RemoveAll();
	CUtlVector< CASW_Base_Spawner* > candidates;

	for ( int i = 0; i < m_hSpawners.Count(); i++ )
	{
		if ( !m_hSpawners[i].Get() || !m_hSpawners[i]->IsEnabled() )
			continue;

		if ( !bIncludeRecentlySpawned && m_hSpawners[i]->HasRecentlySpawned() )
			continue;

		candidates.AddToTail( m_hSpawners[i].Get() );
	}
	for ( int i = 0; ( (i < nNumSpawners) && (candidates.Count() > 0) ); i++ )
	{
		int nChosen = RandomInt( 0, candidates.Count() - 1 );
		pSpawners->AddToTail( candidates[ nChosen ] );
		candidates.Remove( nChosen );
	}
}