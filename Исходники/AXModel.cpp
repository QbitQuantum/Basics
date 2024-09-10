bool CAXModel::Load(const char* strFileName)
{
	this->Unload();

	m_strFile = strFileName;

	LPD3DXBUFFER pAdjacencyBuffer = NULL;
	LPD3DXBUFFER pMtrlBuffer = NULL;
	if (FAILED(D3DXLoadMeshFromXA(m_strFile.c_str(), D3DXMESH_MANAGED, APROJECT_WINDOW->GetD3DDevice(), &pAdjacencyBuffer, &pMtrlBuffer, NULL, &m_dwNumMaterials, &m_pMeshObject)))
		return false;

	// Optimize the mesh for performance
	if (FAILED(m_pMeshObject->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE, (DWORD*)pAdjacencyBuffer->GetBufferPointer(), NULL, NULL, NULL)))
	{
		SAFE_RELEASE(pAdjacencyBuffer);
		SAFE_RELEASE(pMtrlBuffer);
		return false;
	}

	D3DXMATERIAL* d3dxMtrls = (D3DXMATERIAL*)pMtrlBuffer->GetBufferPointer();
	do
	{
		if (d3dxMtrls && m_dwNumMaterials > 0)
		{
			// Allocate memory for the materials and textures
			m_pMaterials = new D3DMATERIAL9[m_dwNumMaterials];
			if (m_pMaterials == NULL)
				break;

			m_pTextures = new LPDIRECT3DBASETEXTURE9[m_dwNumMaterials];
			if (m_pTextures == NULL)
				break;

			m_strMaterials = new CHAR[m_dwNumMaterials][MAX_PATH];
			if (m_strMaterials == NULL)
				break;

			// Copy each material and create its texture
			for (DWORD i = 0; i < m_dwNumMaterials; i++)
			{
				// Copy the material
				m_pMaterials[i] = d3dxMtrls[i].MatD3D;
				m_pTextures[i] = NULL;

				// Create a texture
				if (d3dxMtrls[i].pTextureFilename)
				{
					strcpy_s(m_strMaterials[i], MAX_PATH, d3dxMtrls[i].pTextureFilename);

					CHAR strTexture[MAX_PATH];
					D3DXIMAGE_INFO ImgInfo;

					// First attempt to look for texture in the same folder as the input folder.
					int p = 0;
					strcpy_s(strTexture, MAX_PATH, m_strFile.c_str());
					for (DWORD j = 0; j < strlen(strTexture); j++)
					{
						if (strTexture[j] == '/')
							p = j;
					}
					strTexture[p + 1] = 0;
					strcat_s(strTexture, MAX_PATH, d3dxMtrls[i].pTextureFilename);

					// Inspect the texture file to determine the texture type.
					if (FAILED(D3DXGetImageInfoFromFileA(strTexture, &ImgInfo)))
						continue;

					// Call the appropriate loader according to the texture type.
					switch (ImgInfo.ResourceType)
					{
						case D3DRTYPE_TEXTURE:
						{
							IDirect3DTexture9* pTex;
							if (SUCCEEDED(D3DXCreateTextureFromFileA(APROJECT_WINDOW->GetD3DDevice(), strTexture, &pTex)))
							{
								pTex->QueryInterface(IID_IDirect3DBaseTexture9, (LPVOID*)&m_pTextures[i]);
								pTex->Release();
							}
							break;
						}

						case D3DRTYPE_CUBETEXTURE:
						{
							IDirect3DCubeTexture9* pTex;
							if (SUCCEEDED(D3DXCreateCubeTextureFromFileA(APROJECT_WINDOW->GetD3DDevice(), strTexture, &pTex)))
							{
								pTex->QueryInterface(IID_IDirect3DBaseTexture9, (LPVOID*)&m_pTextures[i]);
								pTex->Release();
							}
							break;
						}

						case D3DRTYPE_VOLUMETEXTURE:
						{
							IDirect3DVolumeTexture9* pTex;
							if (SUCCEEDED(D3DXCreateVolumeTextureFromFileA(APROJECT_WINDOW->GetD3DDevice(), strTexture, &pTex)))
							{
								pTex->QueryInterface(IID_IDirect3DBaseTexture9, (LPVOID*)&m_pTextures[i]);
								pTex->Release();
							}
							break;
						}
					}
				}
			}
		}
	} while (0);

	// Extract data from m_pMesh for easy access
	D3DVERTEXELEMENT9 decl[MAX_FVF_DECL_SIZE];
	m_dwNumVertices = m_pMeshObject->GetNumVertices();
	m_dwNumFaces = m_pMeshObject->GetNumFaces();
	m_dwBytesPerVertex = m_pMeshObject->GetNumBytesPerVertex();
	m_pMeshObject->GetIndexBuffer(&m_pIB);
	m_pMeshObject->GetVertexBuffer(&m_pVB);
	m_pMeshObject->GetDeclaration(decl);
	APROJECT_WINDOW->GetD3DDevice()->CreateVertexDeclaration(decl, &m_pDecl);

	SAFE_RELEASE(pAdjacencyBuffer);
	SAFE_RELEASE(pMtrlBuffer);

	return true;
}