static void CreateServerExitMark(const CLIENTWEAPONFX & theStruct)
{
	SURFACE* pSurf = g_pSurfaceMgr->GetSurface((SurfaceType)theStruct.nSurfaceType);
	if (!pSurf || !pSurf->bCanShootThrough) return;

	int nMaxThickness = pSurf->nMaxShootThroughThickness;
	if (nMaxThickness < 1) return;

	// Determine if there is an "exit" surface...

	IntersectQuery qInfo;
	IntersectInfo iInfo;

    LTVector vDir = theStruct.vPos - theStruct.vFirePos;
	vDir.Normalize();

    qInfo.m_From = theStruct.vPos + (vDir * (LTFLOAT)(nMaxThickness + 1));
	qInfo.m_To   = theStruct.vPos;

	qInfo.m_Flags = INTERSECT_OBJECTS | IGNORE_NONSOLID | INTERSECT_HPOLY;

	SurfaceType eType = ST_UNKNOWN;

    if (g_pLTServer->IntersectSegment(&qInfo, &iInfo))
	{
		eType = GetSurfaceType(iInfo);
		if (ShowsMark(eType))
		{
            LTRotation rNormRot(iInfo.m_Plane.m_Normal, LTVector(0.0f, 1.0f, 0.0f));

			CLIENTWEAPONFX exitStruct = theStruct;
			exitStruct.vPos = iInfo.m_Point + vDir;
			exitStruct.vSurfaceNormal = iInfo.m_Plane.m_Normal;

            CreateServerMark(exitStruct);
		}
	}
}