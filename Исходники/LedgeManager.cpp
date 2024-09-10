LedgeId CLedgeManager::FindNearestLedge( const Vec3 &referencePosition, const Vec3 &testDirection, float maxDistance /*= 2.0f*/, float angleRange /*= DEG2RAD(35.0f)*/, float extendedAngleRange /*= DEG2RAD(50.0f)*/ ) const
{
	if (m_editorManager.IsInEditorMode())
	{
		return m_editorManager.FindNearestLedge( referencePosition, testDirection, maxDistance, angleRange, extendedAngleRange );
	}
	else
	{
		LedgeId bestLedgeId;

		float closestDistanceSq = maxDistance* maxDistance;
		const float fCosMaxAngleTable[2] = { cosf(angleRange), cosf(extendedAngleRange) };
		const float side[2] = { 1.0f, -1.0f };

		SLedgeInfo ledgeInfo;

		const uint32 ledgeObjectCount = m_levelLedges.m_ledgeCount;
		for(uint32 objectIdx = 0; objectIdx < ledgeObjectCount; ++objectIdx)
		{
			const SLedgeObject& ledgeObject = m_levelLedges.m_pLedgeObjects[objectIdx];
			const uint32 startMarkerIdx = ledgeObject.m_markersStartIdx;
			const uint32 endMarkerIdx = ledgeObject.m_markersStartIdx + ledgeObject.m_markersCount;
			CRY_ASSERT ( endMarkerIdx <= m_levelLedges.m_markerCount );
			
			const uint32 sideCount = 1 + ((ledgeObject.m_ledgeFlags[LedgeSide_In] & kLedgeFlag_isDoubleSided) != 0);
			const bool enabled = (ledgeObject.m_ledgeFlags[LedgeSide_In] & kLedgeFlag_enabled) != 0;

			CRY_ASSERT(sideCount <= 2);

			uint32 currentSide = 0;
			do 
			{
				for (uint32 markerIdx = startMarkerIdx; markerIdx < (endMarkerIdx - 1); ++markerIdx)
				{
					ELedgeFlagBitfield flags = kLedgeFlag_none;

					if (m_levelLedges.m_pMarkers[markerIdx].m_endOrCorner)
					{
						flags |= kledgeRunTimeOnlyFlag_p0IsEndOrCorner;
					}
					if (m_levelLedges.m_pMarkers[markerIdx+1].m_endOrCorner)
					{
						flags |= kledgeRunTimeOnlyFlag_p1IsEndOrCorner;
					}

					ledgeInfo = SLedgeInfo( ledgeObject.m_entityId, m_levelLedges.m_pMarkers[markerIdx].m_worldPosition, m_levelLedges.m_pMarkers[markerIdx+1].m_worldPosition,
						m_levelLedges.m_pMarkers[markerIdx].m_facingDirection * side[currentSide], flags, ledgeObject.m_ledgeCornerEndAdjustAmount );

					// Explanation: (Please do not delete this comment)
					//	The item can be skipped if the angle is too big.
					//	Since only the cosine of angles are compared,
					//	bigger angles result in smaller values (hence the less_than comparison)
					const uint32 thresholdIdx = ((ledgeObject.m_ledgeFlags[currentSide] & (kLedgeFlag_useVault|kLedgeFlag_useHighVault)) != 0);
					CRY_ASSERT( thresholdIdx < 2 );

					const float fCosMaxAngle = fCosMaxAngleTable[thresholdIdx];

					const Vec3 vPosToLedge = _FindVectorToClosestPointOnLedge( referencePosition, ledgeInfo );

					float distanceSq;
					if( IsBestLedge( vPosToLedge, testDirection, ledgeInfo, closestDistanceSq, fCosMaxAngle, enabled, distanceSq ) == false )
						continue;
					
					bestLedgeId = LedgeId( objectIdx, (markerIdx - startMarkerIdx), currentSide );
					closestDistanceSq = distanceSq;
				}

				currentSide++;

			} while ( currentSide < sideCount );
		}

		return bestLedgeId;
	}
}