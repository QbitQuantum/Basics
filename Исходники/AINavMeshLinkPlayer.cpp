bool AINavMeshLinkPlayer::FindNearestNavMeshPos( CAI* pAI, const LTVector& vPos, LTVector* pvNavMeshPos, ENUM_NMPolyID* peNavMeshPoly )
{
	// Sanity check.

	if( !( pAI && pvNavMeshPos && peNavMeshPoly ) )
	{
		return false;
	}

	// Bail if Link's poly is invalid.

	CAINavMeshPoly* pPoly = g_pAINavMesh->GetNMPoly( m_eNMPolyID );
	if( !pPoly )
	{
		return false;
	}

	// Iterate over Link's edges, searching for edge nearest 
	// to the specified position.

	ENUM_NMPolyID eNeighborPoly;
	CAINavMeshEdge* pEdge;
	CAINavMeshEdge* pEdgeNearest = NULL;
	float fDistSqr;
	float fMinDistSqr = FLT_MAX;
	uint32 cEdges = pPoly->GetNumNMPolyEdges();
	for( uint32 iEdge=0; iEdge < cEdges; ++iEdge )
	{
		// Skip edge if doesn't exist.

		pEdge = pPoly->GetNMPolyEdge( iEdge );
		if( !pEdge )
		{
			continue;
		}

		// Skip edge if AI cannot pathfind to the neighboring poly.

		eNeighborPoly = ( pEdge->GetNMPolyIDA() != m_eNMPolyID ) ? pEdge->GetNMPolyIDA() : pEdge->GetNMPolyIDB();
		if( ( eNeighborPoly == kNMPoly_Invalid ) ||
			( !g_pAIPathMgrNavMesh->HasPath( pAI, pAI->GetCharTypeMask(), eNeighborPoly ) ) )
		{
			continue;
		}

		// Keep track of the edge nearest to the specified position.

		fDistSqr = vPos.DistSqr( pEdge->GetNMEdgeMidPt() );
		if( fDistSqr < fMinDistSqr )
		{
			fMinDistSqr = fDistSqr;
			pEdgeNearest = pEdge;
		}
	}

	// Bail if no valid edge was found.

	if( !pEdgeNearest )
	{
		return false;
	}

	// Return success.

	if( FindNearestPointOnLine( pEdgeNearest->GetNMEdge0(), pEdgeNearest->GetNMEdge1(), vPos, pvNavMeshPos ) )
	{
		// Push the point a small amount out of the link.
		
		LTVector vDir = *pvNavMeshPos - vPos;
		vDir.Normalize();
		*pvNavMeshPos += vDir * 1.f;

		*peNavMeshPoly = ( pEdgeNearest->GetNMPolyIDA() != m_eNMPolyID ) ? pEdgeNearest->GetNMPolyIDA() : pEdgeNearest->GetNMPolyIDB();
		return true;
	}

	// No intersection found.

	return false;
}