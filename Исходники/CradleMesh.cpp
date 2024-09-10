CradleMesh::CradleMesh(std::wstring _name, CradleFileManager* fm, CradleVertexDeclarations::VertexPosTex* verts, int numVerts /* */)
	: CradleResource(_name, fm)
{
	m_vertices = verts;
	m_numVertices = numVerts;

	m_indices = 0;

	wprintf_s(L"Creating Mesh with %d verts\n", numVerts);
	


	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.ByteWidth = sizeof(CradleVertexDeclarations::VertexPosTex) * m_numVertices;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA subData;
	ZeroMemory(&subData, sizeof(subData));
	subData.pSysMem = m_vertices;

	HRESULT hr = m_fileManager->GetCD3D()->m_d3dDevice->CreateBuffer(&bufferDesc, &subData, &m_vertexBuffer);
	HRPRINT(hr, L"Failed to create vertex buffer\n", L"Vertex buffer created\n");
	
	fm->AddMesh(this);
}