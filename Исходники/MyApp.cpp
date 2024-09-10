void MyApp::renderScene() 
{
	static float time = 0.0f;

	if (!m_bPaused)
		time += 0.001f;

    // Clear the back buffer 
	float clearColor[3] = { 0.4f, 0.4f, 0.7f };
	float clearColorBlack[3] = { 0.f, 0.f, 0.f };
    _dxImmedDC->ClearRenderTargetView(_renderTargetView, (float*)&clearColorBlack);
    _dxImmedDC->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH, 1, 0);

	_dxImmedDC->OMSetBlendState(0, 0, 0xffffffff);
	_dxImmedDC->RSSetState(0);

    // Bind the input layout
	_dxImmedDC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	
	XMMATRIX mVP = m_camera.getViewMatrix()*m_camera.getProjectionMatrix();

	//_______I m p l i c i t    O b j e c t s_____________
	drawImplicitToTexture();

	setMatrixVar(m_fxQuads, (void*)&mVP, "mViewProj");
	setSrvArrayVar(m_fxQuads, &m_srvImplicit, "texarrObjects", 0, 5);

	_dxImmedDC->IASetInputLayout(0);
	_dxImmedDC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	ID3DX11EffectTechnique* tech;
	tech = m_fxQuads->GetTechniqueByIndex(0);
	tech->GetPassByIndex(0)->Apply(0, _dxImmedDC);
	_dxImmedDC->Draw(4, 0);
	
	//_______T e s s e l l a t e d   O b j e c t s _______
	
	if (glb_bWireframe)
		_dxImmedDC->RSSetState(rs_Wireframe);

	// Scene - Spheres
	for (unsigned int i=0; i<m_spheres.size(); i++) {
		drawTessSphereFromOct(&(m_spheres[i]));
	}

	
	myAlien.setPos(0,30,0);
	if (myAlien.type == AlienTypes::GS_ALIEN)
	drawMesh(myAlien.mesh, m_fxAlienGS, myAlien.getMatrix());
	else if (myAlien.type == AlienTypes::EXP_ALIEN) {
		drawMesh(myAlien.mesh, m_fxExplosion, myAlien.getMatrix(), myAlien.expl_time);
		myAlien.expl_time += 0.001f;
	}

	XMFLOAT4X4 mI;
	XMStoreFloat4x4(&mI, XMMatrixIdentity());

	// Scene - Aliens
	for (unsigned int i=0; i<m_aliens.size(); i++) 
	{
		if (m_aliens[i].type == AlienTypes::VS_ALIEN)
			drawMesh(m_aliens[i].mesh, m_fxAlienVS, m_aliens[i].getMatrix());

		else if (m_aliens[i].type == AlienTypes::GS_ALIEN)
			drawMesh(m_aliens[i].mesh, m_fxAlienGS, m_aliens[i].getMatrix());

		else if (m_aliens[i].type == AlienTypes::HS_ALIEN)
			drawTessMesh(m_aliens[i].getMatrix());

		else if (m_aliens[i].type == AlienTypes::EXP_ALIEN) {
			drawMesh(m_aliens[i].mesh, m_fxExplosion, m_aliens[i].getMatrix(), m_aliens[i].expl_time);
			m_aliens[i].expl_time += 0.001f;
		}
		else if (m_aliens[i].type == AlienTypes::BEZ_ALIEN) // BEZ_ALIEN
			drawTessBezierSurface(m_aliens[i].getPos(), m_aliens[i].getTargetPos());
		else // PSP_ALIEN
			drawPSPSurface(m_aliens[i].getPos(), m_aliens[i].getTargetPos());

	}

	// PSP Surface
	if (glb_bSphereMesh)
		drawTessSphereFromMesh();


	// Terrain
	editTerrain();
	drawTessTerrain();


	//_______ G U I ______________________________________
	TwDraw();

	// Swap Buffer
	_swapChain->Present(0, 0);
}