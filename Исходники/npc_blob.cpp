void CNPC_Blob::FormShapeFromPath( string_t iszPathName )
{
	Vector vertex[ BLOB_MAX_VERTS ];

	int i;
	int iNumVerts = 0;

	for ( i = 0 ; i < BLOB_MAX_VERTS ; i++ )
	{
		if( iszPathName == NULL_STRING )
		{
			//Msg("Terminal path\n");
			break;
		}

		CBaseEntity *pEntity = gEntList.FindEntityByName( NULL, iszPathName );

		if( pEntity != NULL )
		{
			bool bClosedPath = false;

			for( int j = 0 ; j < i ; j++ )
			{
				// Stop if we reach a vertex that's already in the array (closed path)
				if( vertex[ j ] == pEntity->GetAbsOrigin() )
				{
					//Msg("Closed path!\n");
					bClosedPath = true;
					break;
				}
			}

			vertex[ i ] = pEntity->GetAbsOrigin();
			iszPathName = pEntity->m_target;
			iNumVerts++;

			if( bClosedPath )
				break;
		}
	}

	//Msg("%d verts found in path!\n", iNumVerts);

	float flPathLength = 0.0f;
	float flDistribution;

	for( i = 0 ; i < iNumVerts - 1 ; i++ )
	{
		Vector vecDiff = vertex[ i ] - vertex[ i + 1 ];

		flPathLength += vecDiff.Length();
	}

	flDistribution = flPathLength / m_iNumElements;
	Msg("Path length is %f, distribution is %f\n", flPathLength, flDistribution );

	int element = 0;
	for( i = 0 ; i < iNumVerts - 1 ; i++ )
	{
		//NDebugOverlay::Line( vertex[ i ], vertex[ i + 1 ], 0, 255, 0, false, 10.0f );
		Vector vecDiff = vertex[ i + 1 ] - vertex[ i ];
		Vector vecStart = vertex[ i ];

		float flSegmentLength = VectorNormalize( vecDiff );

		float flStep;

		for( flStep = 0.0f ; flStep < flSegmentLength ; flStep += flDistribution )
		{
			//NDebugOverlay::Cross3D( vecStart + vecDiff * flStep, 16, 255, 255, 255, false, 10.0f );
			m_Elements[ element ]->SetTargetLocation( vecStart + vecDiff * flStep );
			m_Elements[ element ]->SetActiveMovementRule( BLOB_MOVE_TO_TARGET_LOCATION );
			element++;

			if( element == m_iNumElements )
				return;
		}
	}
}