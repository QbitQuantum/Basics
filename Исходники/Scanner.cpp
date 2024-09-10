LTBOOL CScanner::CanSeePos(ObjectFilterFn ofn, const LTVector& vPos)
{
    LTVector vDir;
	vDir = vPos - GetScanPosition();

	if (VEC_MAGSQR(vDir) >= m_fVisualRange)
	{
        return LTFALSE;
	}

	vDir.Norm();

    LTRotation rRot = GetScanRotation();

    LTVector vUp, vRight, vForward;
    g_pLTServer->GetRotationVectors(&rRot, &vUp, &vRight, &vForward);

    LTFLOAT fDp = vDir.Dot(vForward);

	if (fDp < m_fFOV)
	{
        return LTFALSE;
	}

	// See if we can see the position in question

	IntersectQuery IQuery;
	IntersectInfo IInfo;

	VEC_COPY(IQuery.m_From, GetScanPosition());
	VEC_COPY(IQuery.m_To, vPos);
	IQuery.m_Flags	  = INTERSECT_OBJECTS | IGNORE_NONSOLID;
	IQuery.m_FilterFn = ofn;

    if (!g_pLTServer->IntersectSegment(&IQuery, &IInfo))
	{
        return LTTRUE;
	}

    return LTFALSE;
}