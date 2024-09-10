void CNPC_Portal_FloorTurret::RopesOn( void )
{
	for ( int iRope = 0; iRope < PORTAL_FLOOR_TURRET_NUM_ROPES; ++iRope )
	{
		// Make a rope if it doesn't exist
		if ( !m_hRopes[ iRope ] )
		{
			CFmtStr str;

			int iStartIndex = LookupAttachment( str.sprintf( "Wire%i_start", iRope + 1 ) );
			int iEndIndex = LookupAttachment( str.sprintf( "Wire%i_end", iRope + 1 ) );

			m_hRopes[ iRope ] = CRopeKeyframe::Create( this, this, iStartIndex, iEndIndex );
			if ( m_hRopes[ iRope ] )
			{
				m_hRopes[ iRope ]->m_Width = 0.7;
				m_hRopes[ iRope ]->m_nSegments = ROPE_MAX_SEGMENTS;
				m_hRopes[ iRope ]->EnableWind( false );
				m_hRopes[ iRope ]->SetupHangDistance( 9.0f );
				m_hRopes[ iRope ]->m_bConstrainBetweenEndpoints = true;;
			}
		}
	}
}