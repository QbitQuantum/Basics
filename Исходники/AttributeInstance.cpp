BOOL CAttributeInstance::GetHeight(float fx, float fy, float * pfHeight)
{	
	if(IsEmpty())
		return FALSE;

	fy *= -1.0f;

	if (!IsInHeight(fx, fy))
		return FALSE;

	BOOL bFlag = FALSE;

	for (DWORD i = 0; i < m_v3HeightDataVector.size(); ++i)
	for (DWORD j = 0; j < m_v3HeightDataVector[i].size(); j+=3)
	{
		const D3DXVECTOR3 & c_rv3Vertex0 = m_v3HeightDataVector[i][j];
		const D3DXVECTOR3 & c_rv3Vertex1 = m_v3HeightDataVector[i][j+1];
		const D3DXVECTOR3 & c_rv3Vertex2 = m_v3HeightDataVector[i][j+2];

		if (
			fx<c_rv3Vertex0.x && fx<c_rv3Vertex1.x && fx<c_rv3Vertex2.x ||
			fx>c_rv3Vertex0.x && fx>c_rv3Vertex1.x && fx>c_rv3Vertex2.x ||
			fy<c_rv3Vertex0.y && fy<c_rv3Vertex1.y && fy<c_rv3Vertex2.y ||
			fy>c_rv3Vertex0.y && fy>c_rv3Vertex1.y && fy>c_rv3Vertex2.y
			)
			continue;

		if (IsInTriangle2D(c_rv3Vertex0.x, c_rv3Vertex0.y,
						   c_rv3Vertex1.x, c_rv3Vertex1.y,
						   c_rv3Vertex2.x, c_rv3Vertex2.y, fx, fy))
		{
			D3DXVECTOR3 v3Line1 = c_rv3Vertex1 - c_rv3Vertex0;
			D3DXVECTOR3 v3Line2 = c_rv3Vertex2 - c_rv3Vertex0;
			D3DXVECTOR3 v3Cross;

			D3DXVec3Cross(&v3Cross, &v3Line1, &v3Line2);
			D3DXVec3Normalize(&v3Cross, &v3Cross);

			if (0.0f != v3Cross.z)
			{
				float fd = (v3Cross.x*c_rv3Vertex0.x + v3Cross.y*c_rv3Vertex0.y + v3Cross.z*c_rv3Vertex0.z);
				float fm = (v3Cross.x*fx + v3Cross.y*fy);
				*pfHeight = fMAX((fd - fm) / v3Cross.z, *pfHeight);

				bFlag = TRUE;
			}
		}
	}

	return bFlag;
}