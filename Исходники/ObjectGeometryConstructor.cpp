void ContructSphereVertexBuffer(CRawModel *pRawModel)
{
	CRawMesh *pRawMesh = new CRawMesh(pRawModel, E_MESH_TYPE::SPHERE, E_MESH_TOPOLOGY::TRIANGLESTRIP, pRawModel->m_eRidigBodyFlag);

	float fRadius = XMVectorGetX(XMVector3Length(XMLoadFloat3(&pRawModel->m_vScale)));

	const DWORD dwSphereNumVertices = 64 * 32;

	int i = 0,
		nNumSlices = 32,
		nNumStacks = (dwSphereNumVertices / nNumSlices);
	nNumStacks = nNumStacks / 2 * 2;
	//dwSphereNumVertices = nNumStacks * nNumSlices;

	float
		fTheta = 0.0f,
		fPhi = 0.0f;

	for (int nStack = 0; nStack < nNumStacks; nStack++)
	{
		fPhi = 0.0f;

		for (int nSlice = 0; nSlice < nNumSlices; nSlice++)
		{
			CVertex v;

			v.vPosition = XMFLOAT3(
				cosf(fPhi) * sinf(fTheta) * fRadius,
				cosf(fTheta) * fRadius,
				sinf(fPhi) * sinf(fTheta) * fRadius
				);

			fPhi += XM_PI / nNumSlices * 2.0f;

			if (nSlice % 2)
				fTheta += XM_PI / nNumStacks * 2.0f;
			else
				fTheta -= XM_PI / nNumStacks * 2.0f;

			pRawMesh->m_Vertices.push_back(v);
		}

		fTheta += XM_PI / nNumStacks * 2.0f;
	}

	pRawModel->m_RawMeshes.push_back(pRawMesh);
}