void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(47, 121, 112),
		//D3DCOLOR_XRGB(0, 0, 255),
		1.0f, 0);

	g_pD3DDevice->BeginScene();

	// 그림을 그린다.
	m_pGrid->Render();

// 
// 	for each(D3DXVECTOR3 v in m_vecSpherePosition)
// 	{
// 		if(!m_pFrustum->IsIn(v, 1.0f))
// 			continue;
// 
// 		D3DXMATRIXA16 matWorld;
// 		D3DXMatrixTranslation(&matWorld, v.x, v.y, v.z);
// 		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
// 		g_pD3DDevice->SetMaterial(&m_stWhiteMtl);
// 		m_pSphere->DrawSubset(0);
// 	}
// 	for each(auto p in m_vecDijkstraNode)
// 	{
// 		p->Render(m_pSphere);
// 	}
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_pSkinnedMesh->Render();

	if(m_pFont)
	{
		RECT rc;
		SetRect(&rc, 100, 100, 101, 101);
		char szTemp[1024] = "ABC 123 ?!";
		sprintf(szTemp, "%d", g_pTimeManager->GetFPS());
		m_pFont->DrawTextA(NULL,
			szTemp,
			strlen(szTemp),
			&rc,
			DT_LEFT | DT_TOP | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 255, 0));
	}

	if(!m_vecEdge.empty())
	{
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
		D3DXMATRIXA16 matWorld;
		D3DXMatrixIdentity(&matWorld);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
		g_pD3DDevice->SetTexture(0, NULL);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST,
			m_vecEdge.size() / 2, 
			&m_vecEdge[0],
			sizeof(ST_PC_VERTEX));

	}
	
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}