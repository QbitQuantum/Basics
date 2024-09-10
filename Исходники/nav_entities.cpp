//-----------------------------------------------------------------------------------------------------
int CFuncNavBlocker::DrawDebugTextOverlays( void )
{
	int offset = BaseClass::DrawDebugTextOverlays();

	if (m_debugOverlays & OVERLAY_TEXT_BIT) 
	{
		CFmtStr str;

		// FIRST_GAME_TEAM skips TEAM_SPECTATOR and TEAM_UNASSIGNED, so we can print
		// useful team names in a non-game-specific fashion.
		for ( int i=FIRST_GAME_TEAM; i<FIRST_GAME_TEAM + MAX_NAV_TEAMS; ++i )
		{
			if ( IsBlockingNav( i ) )
			{
				CTeam *team = GetGlobalTeam( i );
				if ( team )
				{
					EntityText( offset++, str.sprintf( "blocking team %s", team->GetName() ), 0 );
				}
				else
				{
					EntityText( offset++, str.sprintf( "blocking team %d", i ), 0 );
				}
			}
		}

		NavAreaCollector collector( true );
		Extent extent;
		extent.Init( this );
		TheNavMesh->ForAllAreasOverlappingExtent( collector, extent );

		for ( int i=0; i<collector.m_area.Count(); ++i )
		{
			CNavArea *area = collector.m_area[i];
			Extent areaExtent;
			area->GetExtent( &areaExtent );
			debugoverlay->AddBoxOverlay( vec3_origin, areaExtent.lo, areaExtent.hi, vec3_angle, 0, 255, 0, 10, NDEBUG_PERSIST_TILL_NEXT_SERVER );
		}
	}

	return offset;
}