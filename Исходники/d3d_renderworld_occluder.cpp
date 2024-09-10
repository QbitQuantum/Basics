void COccluder_Frustum::InitFrustum(const ViewParams& Params)
{
	// Clear!
	Init();

	// Get the points of the near plane in order
	const uint32 k_nNumScreenPts = 4;
	LTVector aScreenPts[k_nNumScreenPts];
	aScreenPts[0] = Params.m_ViewPoints[2];
	aScreenPts[1] = Params.m_ViewPoints[3];
	aScreenPts[2] = Params.m_ViewPoints[1];
	aScreenPts[3] = Params.m_ViewPoints[0];

	// Gimmie some room
	m_aEdgePlanes.reserve(k_nNumScreenPts);
	m_aWorldEdgePlanes.reserve(k_nNumScreenPts);

	// Remember the near plane
	m_cPolyPlane = Params.m_ClipPlanes[CPLANE_NEAR_INDEX];
	m_ePolyPlaneCorner = GetAABBPlaneCorner(m_cPolyPlane.m_Normal);

	// Build the occluder
	LTVector vPrevWorld = aScreenPts[3];
	LTVector vPrevScr;
	MatVMul_H(&vPrevScr, &Params.m_FullTransform, &vPrevWorld);
	for (const LTVector *pCurVert = aScreenPts; pCurVert != &aScreenPts[k_nNumScreenPts]; ++pCurVert)
	{
		const LTVector &vNextWorld = *pCurVert;
		LTVector vNextScr;
		MatVMul_H(&vNextScr, &Params.m_FullTransform, &vNextWorld);
		float fXDiff = (vNextScr.x - vPrevScr.x);
		float fYDiff = (vNextScr.y - vPrevScr.y);
		if ((fXDiff * fXDiff + fYDiff * fYDiff) > 0.001f)
		{
			LTPlane cScreenPlane;
			LTVector vEdgeScr = vNextScr - vPrevScr;
			cScreenPlane.m_Normal.Init(vEdgeScr.y, -vEdgeScr.x, 0.0f);
			cScreenPlane.m_Normal.Normalize();
			cScreenPlane.m_Dist = cScreenPlane.m_Normal.x * vNextScr.x + cScreenPlane.m_Normal.y * vNextScr.y;

			LTPlane cWorldPlane;
			LTVector vEdgeWorld = vNextWorld - vPrevWorld;
			cWorldPlane.m_Normal = vEdgeWorld.Cross(vNextWorld - Params.m_Pos);
			cWorldPlane.m_Normal.Normalize();
			cWorldPlane.m_Dist = cWorldPlane.m_Normal.Dot(vNextWorld);

			AddPlane(cScreenPlane, cWorldPlane);
		}

		vPrevWorld = vNextWorld;
		vPrevScr = vNextScr;
	}
}