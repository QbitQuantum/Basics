bool D3D11RendererMesh::BuildBuffers(const GeoGen::MeshData& mesh)
{
	D3D11_BUFFER_DESC desc = { 0 };
	desc.ByteWidth = sizeof(VertexPositionNormalTexture) * mesh.vertices.size();
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.Usage = D3D11_USAGE_DEFAULT;
	m_nVBSize = mesh.vertices.size();
	m_nIBSize = mesh.indices.size();

	vertices.resize(mesh.vertices.size());
	float Infinity = FLT_MAX;
	XMFLOAT3 vMinf3(+Infinity, +Infinity, +Infinity);
	XMFLOAT3 vMaxf3(-Infinity, -Infinity, -Infinity);
	vMin = XMLoadFloat3(&vMinf3);
	vMax = XMLoadFloat3(&vMaxf3);

	for (UINT i = 0; i < mesh.vertices.size(); ++i)
	{
		vertices[i].position = mesh.vertices[i].pos;
		vertices[i].normal = mesh.vertices[i].normal;
		vertices[i].textureCoordinate = mesh.vertices[i].tex;
		XMVECTOR P = XMLoadFloat3(&vertices[i].position);
		vMin = XMVectorMin(vMin, P);
		vMax = XMVectorMax(vMax, P);
	}
	D3D11_SUBRESOURCE_DATA vData;
	vData.pSysMem = &vertices[0];
	vData.SysMemPitch = 0;
	vData.SysMemSlicePitch = 0;
	if (FAILED(m_d3dDevice->CreateBuffer(&desc, &vData, &m_VB)))
	{
		MessageBox(NULL, L"Create Vertex Buffer failed!", L"Error", MB_OK);
		return false;
	}

	D3D11_BUFFER_DESC iDesc = { 0 };
	iDesc.ByteWidth = sizeof(UINT) * mesh.indices.size();
	iDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	iDesc.Usage = D3D11_USAGE_DEFAULT;
	indices.resize(mesh.indices.size());
	for (UINT i = 0; i < mesh.indices.size(); ++i)
	{
		indices[i] = mesh.indices[i];
	}
	D3D11_SUBRESOURCE_DATA iData;
	iData.pSysMem = &indices[0];
	iData.SysMemPitch = 0;
	iData.SysMemSlicePitch = 0;
	if (FAILED(m_d3dDevice->CreateBuffer(&iDesc, &iData, &m_IB)))
	{
		MessageBox(NULL, L"Create Index Buffer failed!", L"Error", MB_OK);
		return false;
	}




	return true;
}