HRESULT SceneObjectGrid::InitializeMeshStreams(__in ISceneObjectMesh* pMesh, const XMVECTOR xAxis, const XMVECTOR yAxis, const XMFLOAT3& origin, UINT xResolution,
											   UINT yResolution, XMFLOAT4 color)
{
	if (xResolution == 0 || yResolution == 0 || pMesh == NULL)
	{
		return E_INVALIDARG;
	}

	HRESULT hr = S_OK;

    xResolution = max(1, xResolution);
    yResolution = max(1, yResolution);

    // Build grid geometry
    INT iLineCount = xResolution + yResolution + 2;
	VertexType* pLines = new VertexType[2 * iLineCount];

	if (!pLines)
	{
		hr = E_OUTOFMEMORY;
	}
	else
	{
		XMVECTOR vOrigin = XMLoadFloat3(&origin);

		for (UINT i = 0; i <= xResolution; i++)
		{
			FLOAT fPercent = (FLOAT)i / (FLOAT)xResolution;
			fPercent = (fPercent * 2.0f) - 1.0f;
			
            XMVECTOR vScale = XMVectorScale(xAxis, fPercent);
			vScale = XMVectorAdd( vScale, vOrigin );

			XMStoreFloat3(&pLines[(i * 2)].position, XMVectorSubtract(vScale, yAxis));
            pLines[(i * 2)].color = color;

			XMStoreFloat3(&pLines[(i * 2) + 1].position, XMVectorAdd(vScale, yAxis));
            pLines[(i * 2) + 1].color = color;
		}

		UINT iStartIndex = (xResolution + 1) * 2;
		for (UINT i = 0; i <= yResolution; i++)
		{
			FLOAT fPercent = (FLOAT)i / (FLOAT)yResolution;
			fPercent = (fPercent * 2.0f) - 1.0f;
			
            XMVECTOR vScale = XMVectorScale(yAxis, fPercent);
			vScale = XMVectorAdd(vScale, vOrigin);
			
            XMStoreFloat3(&pLines[(i * 2) + iStartIndex].position, XMVectorSubtract(vScale, xAxis));
            pLines[(i * 2) + iStartIndex].color = color;

			XMStoreFloat3(&pLines[(i * 2) + 1 + iStartIndex].position, XMVectorAdd(vScale, xAxis));
            pLines[(i * 2) + 1 + iStartIndex].color = color;
		}

		SmartPtr<IVertexStream> spVertexStream;
		hr = CreateVertexStream(2 * iLineCount, pLines, &spVertexStream);
		if (SUCCEEDED(hr))
		{
			hr = pMesh->SetMeshStream(MeshStreamType::MST_VERTEX_POSITIONS, spVertexStream.CastTo<IMeshStream>());		
		}

		pMesh->SetPrimitiveTopologyType(PrimitiveTopologyType::PTT_LINELIST);
	}

    delete[] pLines;

	return hr;
}