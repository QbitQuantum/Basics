bool CXMesh::PickPoly(D3DXVECTOR3* PickRayOrig, D3DXVECTOR3* PickRayDir)
{
	if(!m_BlendedMesh) return false;

	HRESULT res;

	DWORD FvfSize = D3DXGetFVFVertexSize(m_BlendedMesh->GetFVF());
	DWORD NumVertices = m_BlendedMesh->GetNumVertices();
	DWORD NumFaces = m_BlendedMesh->GetNumFaces();

	// lock vertex buffer
	BYTE* Points = NULL;
	res = m_BlendedMesh->LockVertexBufferUni(D3DLOCK_READONLY, &Points);
	if (FAILED(res)) return false;

	// lock index buffer
	WORD* Indices;
	res = m_BlendedMesh->LockIndexBufferUni(D3DLOCK_READONLY, &Indices);
	if (FAILED(res))
	{
		m_BlendedMesh->UnlockVertexBuffer();
		return false;
	}


	bool Found = false;
	D3DXVECTOR3 Intersection;

	for(DWORD i=0; i<NumFaces; i++)
	{
		WORD i1, i2, i3;
		i1 = Indices[3*i+0];
		i2 = Indices[3*i+1];
		i3 = Indices[3*i+2];

		D3DXVECTOR3 v0 = *(D3DXVECTOR3*)(Points + Indices[3*i+0] * FvfSize);
		D3DXVECTOR3 v1 = *(D3DXVECTOR3*)(Points + Indices[3*i+1] * FvfSize);
		D3DXVECTOR3 v2 = *(D3DXVECTOR3*)(Points + Indices[3*i+2] * FvfSize);

		if(_isnan(v0.x)) continue;

		Found = C3DUtils::IntersectTriangle(*PickRayOrig, *PickRayDir, v0, v1, v2, &Intersection.x, &Intersection.y, &Intersection.z) != FALSE;
		if(Found) break;
	}

	m_BlendedMesh->UnlockVertexBuffer();
	m_BlendedMesh->UnlockIndexBuffer();

	return Found;
}