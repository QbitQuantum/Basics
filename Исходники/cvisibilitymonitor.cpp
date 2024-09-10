//---------------------------------------------------------
//---------------------------------------------------------
void CVisibilityMonitor::RemoveEntity( CBaseEntity *pEntity )
{
	Assert( pEntity != NULL );

	for( int i = 0 ; i < m_Entities.Count() ; i++ )
	{
		if( m_Entities[i].entity == pEntity )
		{
			m_Entities.Remove( i );

			if( debug_visibility_monitor.GetBool() )
			{
				Msg("VisMon: Removed Entity: %s (%s)\n", pEntity->GetClassname(), pEntity->GetDebugName() );
			}

			return;
		}
	}
}