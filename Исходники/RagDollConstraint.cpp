void CRagDollAbovePlaneOnEdgeConstraint::Apply(uint32 nPosIndex)
{
	const LTVector& vPtInPlane = m_pPt1->m_vPosition[nPosIndex];

	LTVector vEdge = m_pPt2->m_vPosition[nPosIndex] - vPtInPlane;

	//we first off need to caclulate the normal of the plane
	LTVector vNormal = vEdge.Cross(m_pPt3->m_vPosition[nPosIndex] - vPtInPlane);
	vNormal.Normalize();

	//now we need to take that plane, and find the perpindicular plane that passes through the first edge
	LTVector vEdgeNormal = vNormal.Cross(vEdge) * m_fNormalScale;
	vEdgeNormal.Normalize();

	//ok, now we see if the point is above the plane
	LTVector& vConstrain = m_pConstrain->m_vPosition[nPosIndex];
	float fDot = vEdgeNormal.Dot(vConstrain - vPtInPlane);

	if(fDot < 0.0f)
	{
		vConstrain -= fDot * vEdgeNormal;
	}
}