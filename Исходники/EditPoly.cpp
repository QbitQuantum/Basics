//determines if this polygon is concave or not
bool CEditPoly::IsConcave()
{
	uint32 nNumPts = NumVerts();

	if(nNumPts <= 3)
	{
		return false;
	}

	//get the normal for this polygon
	LTVector vNormal = Normal();

	//now go through every edge
	uint32 nPrevPt = nNumPts - 1;
	for(uint32 nCurrPt = 0; nCurrPt < nNumPts; nPrevPt = nCurrPt, nCurrPt++)
	{
		//build the edge normal
		LTVector vEdge = m_pBrush->m_Points[Index(nCurrPt)] - m_pBrush->m_Points[Index(nPrevPt)];

		//find the normal
		LTVector vEdgeNorm = vNormal.Cross(vEdge);
		vEdgeNorm.Norm();

		//now run through all the other points
		for(uint32 nTestPt = 0; nTestPt < nNumPts; nTestPt++)
		{
			//ignore the points on the edge
			if((nTestPt == nCurrPt) || (nTestPt == nPrevPt))
				continue;

			//see if it is on the correct side
			if(vEdgeNorm.Dot(m_pBrush->m_Points[Index(nTestPt)] - m_pBrush->m_Points[Index(nCurrPt)]) > 0.001f)
			{
				return true;
			}
		}
	}

	return false;

}