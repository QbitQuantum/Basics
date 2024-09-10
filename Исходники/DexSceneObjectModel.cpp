//-----------------------------------------------------------------------------
//Desc: 生成蒙皮网格模型(含有每个顶点的混合权重、索引和一个骨骼组合表)
//-----------------------------------------------------------------------------
HRESULT DexAllocateHierarchy::GenerateGameSkinMesh(LPDIRECT3DDEVICE9 device, stDexMeshContainerEx *pMeshContainer)
{
	getLog()->BeginLog();
	HRESULT hr = S_OK;

	if (pMeshContainer->pSkinInfo == NULL)
		return hr;

	_SafeRelease( pMeshContainer->MeshData.pMesh );
	_SafeRelease( pMeshContainer->pBoneCombinationBuf );

	D3DCAPS9 d3dCaps;
	device->GetDeviceCaps( &d3dCaps );

	UINT MaxMatrices = 26; 
	pMeshContainer->NumPaletteEntries = min(MaxMatrices, pMeshContainer->pSkinInfo->GetNumBones());

	DWORD Flags = D3DXMESHOPT_VERTEXCACHE;
	if (d3dCaps.VertexShaderVersion >= D3DVS_VERSION(1, 1))
	{
		Flags |= D3DXMESH_MANAGED;
	}
	else
	{
		getLog()->Log(log_allert, ".X Animation file shader 錯誤！");
	}


	//_SafeRelease(pMeshContainer->MeshData.pMesh);

	if(1)
	{
		DWORD NumMaxFaceInfl;
		DWORD Flags = D3DXMESHOPT_VERTEXCACHE;

		LPDIRECT3DINDEXBUFFER9 pIB;
		hr = pMeshContainer->pOrigMesh->GetIndexBuffer( &pIB );
		if( FAILED( hr ) )
			return hr;

		hr = pMeshContainer->pSkinInfo->GetMaxFaceInfluences( pIB,
			pMeshContainer->pOrigMesh->GetNumFaces(),
			&NumMaxFaceInfl );
		pIB->Release();
		if( FAILED( hr ) )
			return hr;

		// 12 entry palette guarantees that any triangle (4 independent influences per vertex of a tri)
		// can be handled
		NumMaxFaceInfl = min( NumMaxFaceInfl, 12 );

		if( d3dCaps.MaxVertexBlendMatrixIndex + 1 < NumMaxFaceInfl )
		{
			// HW does not support indexed vertex blending. Use SW instead
			pMeshContainer->NumPaletteEntries = min( 256, pMeshContainer->pSkinInfo->GetNumBones() );
			Flags |= D3DXMESH_SYSTEMMEM;
		}
		else
		{
			// using hardware - determine palette size from caps and number of bones
			// If normals are present in the vertex data that needs to be blended for lighting, then 
			// the number of matrices is half the number specified by MaxVertexBlendMatrixIndex.
			pMeshContainer->NumPaletteEntries = min( ( d3dCaps.MaxVertexBlendMatrixIndex + 1 ) / 2,
				pMeshContainer->pSkinInfo->GetNumBones() );
			Flags |= D3DXMESH_MANAGED;
		}

		hr = pMeshContainer->pSkinInfo->ConvertToIndexedBlendedMesh
			(
			pMeshContainer->pOrigMesh,
			Flags,
			pMeshContainer->NumPaletteEntries,
			pMeshContainer->pAdjacency,
			NULL, NULL, NULL,
			&pMeshContainer->NumInfl,
			&pMeshContainer->NumAttributeGroups,
			&pMeshContainer->pBoneCombinationBuf,
			&pMeshContainer->MeshData.pMesh );
		if( FAILED( hr ) )
			return hr;
		return 1;
	}

	//生成蒙皮网格模型
	hr = pMeshContainer->pSkinInfo->ConvertToIndexedBlendedMesh
		(
		pMeshContainer->pOrigMesh,
		Flags, 
		pMeshContainer->NumPaletteEntries, 
		pMeshContainer->pAdjacency, 
		NULL, NULL, NULL,             
		&pMeshContainer->NumInfl,
		&pMeshContainer->NumAttributeGroups, 
		&pMeshContainer->pBoneCombinationBuf, 
		&pMeshContainer->MeshData.pMesh);
	if (FAILED(hr))
		return hr;


	// FVF has to match our declarator. Vertex shaders are not as forgiving as FF pipeline
	DWORD NewFVF = (pMeshContainer->MeshData.pMesh->GetFVF() & D3DFVF_POSITION_MASK) | D3DFVF_NORMAL | D3DFVF_TEX1 | D3DFVF_LASTBETA_UBYTE4;
	if (NewFVF != pMeshContainer->MeshData.pMesh->GetFVF())
	{
		LPD3DXMESH pMesh;
		hr = pMeshContainer->MeshData.pMesh->CloneMeshFVF(pMeshContainer->MeshData.pMesh->GetOptions(), NewFVF, device, &pMesh);
		if (!FAILED(hr))
		{
			pMeshContainer->MeshData.pMesh->Release();
			pMeshContainer->MeshData.pMesh = pMesh;
			pMesh = NULL;
		}
	}

	D3DVERTEXELEMENT9 pDecl[MAX_FVF_DECL_SIZE];
	LPD3DVERTEXELEMENT9 pDeclCur;
	hr = pMeshContainer->MeshData.pMesh->GetDeclaration(pDecl);
	if (FAILED(hr))
		return hr;

	// the vertex shader is expecting to interpret the UBYTE4 as a D3DCOLOR, so update the type 
	//   NOTE: this cannot be done with CloneMesh, that would convert the UBYTE4 data to float and then to D3DCOLOR
	//          this is more of a "cast" operation
	pDeclCur = pDecl;
	while (pDeclCur->Stream != 0xff)
	{
		if ((pDeclCur->Usage == D3DDECLUSAGE_BLENDINDICES) && (pDeclCur->UsageIndex == 0))
			pDeclCur->Type = D3DDECLTYPE_D3DCOLOR;
		pDeclCur++;
	}

	hr = pMeshContainer->MeshData.pMesh->UpdateSemantics(pDecl);
	if (FAILED(hr))
		return hr;

	// allocate a buffer for bone matrices, but only if another mesh has not allocated one of the same size or larger
	if( m_NumBoneMatricesMax < pMeshContainer->pSkinInfo->GetNumBones() )
	{
		m_NumBoneMatricesMax = pMeshContainer->pSkinInfo->GetNumBones();

		// Allocate space for blend matrices
		delete[] m_pBoneMatrices; 
		m_pBoneMatrices  = new D3DXMATRIX[m_NumBoneMatricesMax];
		if( m_pBoneMatrices == NULL )
		{
			hr = E_OUTOFMEMORY;
			return hr;
		}
	}
	return hr;
}