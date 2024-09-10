// Wrap the textures, starting at a poly index
void CRVTrackerTextureWrap::WrapTexture(CTWPolyInfo *pPoly, const CVector &vWrapDir, CTextExtents &cExtents) const
{
	// Mark this poly as wrapped
	pPoly->m_bTouched = TRUE;

	CTexturedPlane& Texture = pPoly->m_pPoly->GetTexture(GetCurrTexture());

	// Get the texture space
	LTVector vWrapO = Texture.GetO();
	LTVector vWrapP = Texture.GetP();
	LTVector vWrapQ = Texture.GetQ();

	// Get the texture offset projections
	float fWrapOdotP = vWrapO.Dot(vWrapP);
	float fWrapOdotQ = vWrapO.Dot(vWrapQ);

	// Update the texturing extents
	for (uint32 nExtentLoop = 0; nExtentLoop < pPoly->m_aEdges.GetSize(); ++nExtentLoop)
	{
		LTVector vEdgePt = pPoly->m_aEdges[nExtentLoop]->m_aPt[0];

		float fCurU = vWrapP.Dot(vEdgePt) - fWrapOdotP;
		float fCurV = vWrapQ.Dot(vEdgePt) - fWrapOdotQ;

		cExtents.m_fMinU = LTMIN(fCurU, cExtents.m_fMinU);
		cExtents.m_fMaxU = LTMAX(fCurU, cExtents.m_fMaxU);
		cExtents.m_fMinV = LTMIN(fCurV, cExtents.m_fMinV);
		cExtents.m_fMaxV = LTMAX(fCurV, cExtents.m_fMaxV);
	}

	CMoArray<uint32> aNeighbors;
	CMoArray<float> aDots;

	// Insert the neighbors into a list in dot-product order
	for (uint32 nNeighborLoop = 0; nNeighborLoop < pPoly->m_aNeighbors.GetSize(); ++nNeighborLoop)
	{
		CTWPolyInfo *pNeighbor = pPoly->m_aNeighbors[nNeighborLoop];

		// Skip edges that don't have a neighbor
		if (!pNeighbor)
			continue;

		// Skip neighbors that are already wrapped
		if (pNeighbor->m_bTouched)
			continue;

		// Get our dot product
		float fCurDot = vWrapDir.Dot(pPoly->m_aEdges[nNeighborLoop]->m_Plane.m_Normal);

		if ((m_bRestrictWalkDir) && (fCurDot < 0.707f))
			continue;

		// Mark this neighbor as touched (to avoid later polygons pushing it onto the stack)
		pNeighbor->m_bTouched = TRUE;

		// Insert it into the list
		for (uint32 nInsertLoop = 0; nInsertLoop < aNeighbors.GetSize(); ++nInsertLoop)
		{
			if (fCurDot > aDots[nInsertLoop])
				break;
		}
		aDots.Insert(nInsertLoop, fCurDot);
		aNeighbors.Insert(nInsertLoop, nNeighborLoop);
	}

	// Recurse through its neighbors
	for (uint32 nWrapLoop = 0; nWrapLoop < aNeighbors.GetSize(); ++nWrapLoop)
	{
		CTWPolyInfo *pNeighbor = pPoly->m_aNeighbors[aNeighbors[nWrapLoop]];
		CTWEdgeInfo *pEdge = pPoly->m_aEdges[aNeighbors[nWrapLoop]];

		//////////////////////////////////////////////////////////////////////////////
		// Wrap this neighbor

		// Create a matrix representing the basis of the polygon in relation to this edge
		LTMatrix mPolyBasis;
		mPolyBasis.SetTranslation(0.0f, 0.0f, 0.0f);
		mPolyBasis.SetBasisVectors(&pEdge->m_vDir, &pPoly->m_pPoly->m_Plane.m_Normal, &pEdge->m_Plane.m_Normal);

		// Create a new basis for the neighbor polygon
		LTMatrix mNeighborBasis;
		LTVector vNeighborForward;
		vNeighborForward = pNeighbor->m_pPoly->m_Plane.m_Normal.Cross(pEdge->m_vDir);
		// Just to be sure..
		vNeighborForward.Norm();
		mNeighborBasis.SetTranslation(0.0f, 0.0f, 0.0f);
		mNeighborBasis.SetBasisVectors(&pEdge->m_vDir, &pNeighbor->m_pPoly->m_Plane.m_Normal, &vNeighborForward);

		// Create a rotation matrix from here to there
		LTMatrix mRotation;
		mRotation = mNeighborBasis * ~mPolyBasis;

		// Rotate the various vectors
		LTVector vNewP;
		LTVector vNewQ;
		LTVector vNewDir;

		mRotation.Apply3x3(vWrapP, vNewP);
		mRotation.Apply3x3(vWrapQ, vNewQ);
		mRotation.Apply3x3(vWrapDir, vNewDir);

		// Rotate the texture basis if we're following a path
		if (m_nWrapStyle == k_WrapPath)
		{
			LTVector vNeighborEdgeDir;
			if (GetSimilarEdgeDir(pNeighbor, vNewDir, vNeighborEdgeDir, 0.707f))
			{
				LTMatrix mRotatedNeighbor;
				LTVector vNeighborRight;
				vNeighborRight = vNeighborEdgeDir.Cross(pNeighbor->m_pPoly->m_Plane.m_Normal);
				vNeighborRight.Norm();
				// Make sure we're pointing the right way...
				if (vNeighborRight.Dot(pEdge->m_vDir) < 0.0f)
					vNeighborRight = -vNeighborRight;
				mRotatedNeighbor.SetTranslation(0.0f, 0.0f, 0.0f);
				mRotatedNeighbor.SetBasisVectors(&vNeighborRight, &pNeighbor->m_pPoly->m_Plane.m_Normal, &vNeighborEdgeDir);
				// Build a basis based on an edge from the current polygon 
				LTVector vBestPolyEdge;
				GetSimilarEdgeDir(pPoly, vWrapDir, vBestPolyEdge);
				LTVector vPolyRight = vBestPolyEdge.Cross(pNeighbor->m_pPoly->m_Plane.m_Normal);
				vPolyRight.Norm();
				// Make sure we're pointing the right way...
				if (vPolyRight.Dot(pEdge->m_vDir) < 0.0f)
					vPolyRight = -vPolyRight;
				// Build the poly edge matrix
				LTMatrix mPolyEdgeBasis;
				mPolyEdgeBasis.SetTranslation(0.0f, 0.0f, 0.0f);
				mPolyEdgeBasis.SetBasisVectors(&vPolyRight, &pNeighbor->m_pPoly->m_Plane.m_Normal, &vBestPolyEdge);

				// Get a matrix from here to there
				LTMatrix mRotator;
				mRotator = mRotatedNeighbor * ~mPolyEdgeBasis;
				// Rotate the texture basis
				mRotator.Apply3x3(vNewP);
				mRotator.Apply3x3(vNewQ);
				// And use the new edge as the new direction
				vNewDir = vNeighborEdgeDir;
			}

			// Remove skew from vNewP/vNewQ
			if ((float)fabs(vNewP.Dot(vNewQ)) > 0.001f)
			{
				float fMagP = vNewP.Mag();
				float fMagQ = vNewQ.Mag();
				vNewQ *= 1.0f / fMagQ;
				vNewP -= vNewQ * vNewQ.Dot(vNewP);
				vNewP.Norm(fMagP);
				vNewQ *= fMagQ;
			}
		}

		// Get the first edge point..
		CVector vEdgePt = pEdge->m_aPt[0];

		// Calculate the texture coordinate at this point
		float fWrapU = vWrapP.Dot(vEdgePt) - fWrapOdotP;
		float fWrapV = vWrapQ.Dot(vEdgePt) - fWrapOdotQ;

		// Build the new offset
		float fNewOdotP = vNewP.Dot(vEdgePt) - fWrapU;
		float fNewOdotQ = vNewQ.Dot(vEdgePt) - fWrapV;
		LTVector vNewO;
		vNewO.Init();
		float fNewPMag = vNewP.MagSqr();
		if (fNewPMag > 0.0f)
			vNewO += vNewP * (fNewOdotP / fNewPMag);
		float fNewQMag = vNewQ.MagSqr();
		if (fNewQMag > 0.0f)
			vNewO += vNewQ * (fNewOdotQ / fNewQMag);

		pNeighbor->m_pPoly->SetTextureSpace(GetCurrTexture(), vNewO, vNewP, vNewQ);

		// Recurse into this neighbor
		WrapTexture(pNeighbor, vNewDir, cExtents);
	}
}