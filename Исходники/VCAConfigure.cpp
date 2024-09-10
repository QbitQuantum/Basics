HRESULT CVCAConfigure::LoadZones(DWORD dwEngId, VCA5_APP_ZONES *pZones)
{
	HRESULT hr = E_FAIL;
	USES_CONVERSION;

	//---------------------------------------------------------------
	// Zones
	VCA_ZONES_T		tZones;

	if( LIBVCA_ERROR != libvca_retrieve_ZONEinfo( &tZones, dwEngId ) )
	{
		pZones->ulTotalZones	= tZones.uiTotalZones;

		int idx = 0;
		for( unsigned int i = 0; i < MAX_NUM_ZONES; i++ )
		{
			if( IsZoneUsed( &tZones.pZones[i] ) )
			{
				VCA5_APP_ZONE	*pZone = &(pZones->pZones[idx++]);
				pZone->usZoneId		= tZones.pZones[i].usZoneId;
				pZone->usZoneType	= tZones.pZones[i].usZoneType;
				pZone->usZoneStyle	= tZones.pZones[i].usZoneStyle;
				pZone->uiColor		= _byteswap_ulong( tZones.pZones[i].uiColor << 8 ); // RGB -> BGR
				strcpy( pZone->szZoneName, tZones.pZones[i].strZoneName );

				pZone->ulTotalPoints	= tZones.pZones[i].uiTotalPoints;
				for( unsigned int j = 0; j < tZones.pZones[i].uiTotalPoints; j++ )
				{
					pZone->pPoints[j].x	= tZones.pZones[i].pPoints[j].x;
					pZone->pPoints[j].y	= tZones.pZones[i].pPoints[j].y;
				}
			}
		}

		hr = S_OK;
	}

	return hr;
}