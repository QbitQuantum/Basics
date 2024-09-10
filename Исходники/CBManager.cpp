void CCBManager::Update()
{
	//チョコボールを生成していく。
	const float deltaTime = 1.0f / 60.0f;
	m_timer += deltaTime;
	if (m_interval < m_timer){
		int createCount = 0;
		while ( m_numCreate < CHOCO_NUM ){
			if (createCount == 10){
				break;
			}
			float rate = 100.0f / (rand() % 100 + 1);
			rate /= 50.0f;
			if (rand() % 2){
				rate *= -1.0f;
			}
			D3DXVECTOR3 pos(GetStartPosition());
			pos.x += rate;
			pos.z += fabsf(rate);
			pos.y += rate;
			D3DXVECTOR3 Epos(GetEndPosition());
			Epos.x += rate;
			Epos.z += fabsf(rate);
			Epos.y += rate;
			m_Choco[m_numCreate].Initialize(pos, Epos);
			//if (m_IsFirst){
			//	D3DXMESHCONTAINER_DERIVED* pMeshContainer = static_cast<D3DXMESHCONTAINER_DERIVED*>(m_Choco[m_numCreate].GetImage()->pModel->GetFrameRoot()->pMeshContainer);
			//	LPDIRECT3DVERTEXBUFFER9 buffer;
			//	pMeshContainer->MeshData.pMesh->GetVertexBuffer(&buffer)/*->GetBufferPointer()*/;
			//	VOID* pVertices;
			//	buffer->Lock(0, sizeof(buffer), (void**)&pVertices, 0);
			//	D3DVERTEXBUFFER_DESC desc;
			//	buffer->GetDesc(&desc);
			//	int stride = D3DXGetFVFVertexSize(desc.FVF);
			//	char* p = (char*)pVertices;
			//	int offset = -1;
			//	D3DVERTEXELEMENT9 pDecl[MAX_FVF_DECL_SIZE];
			//	memset(pDecl, -1, sizeof(pDecl));
			//	pMeshContainer->MeshData.pMesh->GetDeclaration(pDecl);
			//	for (int idx = 0; idx < MAX_FVF_DECL_SIZE; idx++){
			//		if (pDecl[idx].Stream == 255){
			//			//終わり
			//			break;
			//		}
			//		if (pDecl[idx].Usage == D3DDECLUSAGE_BINORMAL){
			//			offset = pDecl[idx].Offset;
			//		}
			//	}
			//	for (int vertNo = 0; vertNo < pMeshContainer->MeshData.pMesh->GetNumVertices(); vertNo++){
			//		D3DXVECTOR3* pBinomal = (D3DXVECTOR3*)&p[offset];
			//		pBinomal->x = 
			//		p += stride;
			//	}
			//	
			//	
			//	//buffer
			//	//m_pVertexBuffer->
			//	//memcpy(pVertices, buffer, sizeof(buffer));
			//	//pVertices
			//	buffer->Unlock();

			//	(*graphicsDevice()).CreateVertexBuffer(sizeof(buffer), 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &m_pVertexBuffer, nullptr);
			//	m_IsFirst = false;
			//}
			SINSTANCE(CShadowRender)->Entry(&m_Choco[m_numCreate]);
			createCount++;
			m_numCreate++;
		}
	}
	for (int i = 0; i < m_numCreate; i++)
	{
		m_Choco[i].Update();
	}
}