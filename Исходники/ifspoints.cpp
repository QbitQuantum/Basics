void ifs_render(float t)
{

	if(ifs_loaded!=(int)(ifs_number)) ifs_load((int)ifs_number);
//	if(ifs_loaded!=(int)(angles[254])) ifs_load((int)angles[254]);

	g_pd3dDevice->BeginScene();
//	g_pd3dDevice->Clear( 0L, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL, 0xff000000, 1.0f, 0L );

	ifs_clear();


	g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, FALSE );
	g_pd3dDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_ALWAYS);

//	render_bg(g_pd3dDevice, bg);


	D3DXMATRIX matWorld;
	D3DXMatrixIdentity( &matWorld );
//	D3DXMatrixScaling(&matWorld, ifs_z,ifs_z,ifs_z); 
	g_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );

	// Set up our view matrix. A view matrix can be defined given an eye point,
	// a point to lookat, and a direction for which way is up. Here, we set the
	// eye five units back along the z-axis and up three units, look at the
	// origin, and define "up" to be in the y-direction.
	D3DXMATRIX matView;
	D3DXMatrixLookAtLH( &matView, &D3DXVECTOR3( 0.0f, 0.0f,-3.0f+ifs_z),
		&D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
		&D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) );
	g_pd3dDevice->SetTransform( D3DTS_VIEW, &matView );

	// For the projection matrix, we set up a perspective transform (which
	// transforms geometry from 3D view space to 2D viewport space, with
	// a perspective divide making objects smaller in the distance). To build
	// a perpsective transform, we need the field of view (1/4 pi is common),
	// the aspect ratio, and the near and far clipping planes (which define at
	// what distances geometry should be no longer be rendered).
	D3DXMATRIX matProj;
	//D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.0f, 1.0f, 100.0f );
	D3DXMatrixPerspectiveFovLH( &matProj, 1, 4.f/3.f, 0.1f, 100.0f );
	g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );


	g_pd3dDevice->SetTexture(3, m_pParticleTexture );

	int alpha=(int)(255*fade);
	m_pd3dDevice->SetRenderState( D3DRS_TEXTUREFACTOR, 0x01010101*(alpha));

	m_pd3dDevice->SetTextureStageState( 3, D3DTSS_TEXCOORDINDEX, 0);
    m_pd3dDevice->SetTextureStageState( 3, D3DTSS_COLOROP,   D3DTOP_MODULATE );
    m_pd3dDevice->SetTextureStageState( 3, D3DTSS_COLORARG2, D3DTA_CURRENT);
    m_pd3dDevice->SetTextureStageState( 3, D3DTSS_COLORARG1, D3DTA_TEXTURE );
    m_pd3dDevice->SetTextureStageState( 3, D3DTSS_ALPHAOP,   D3DTOP_MODULATE );
    m_pd3dDevice->SetTextureStageState( 3, D3DTSS_ALPHAARG2, D3DTA_TFACTOR);
    m_pd3dDevice->SetTextureStageState( 3, D3DTSS_ALPHAARG1, D3DTA_CURRENT );


	// Set the render states for using point sprites
	g_pd3dDevice->SetRenderState( D3DRS_POINTSPRITEENABLE, TRUE);
	g_pd3dDevice->SetRenderState( D3DRS_POINTSCALEENABLE,  FALSE );
	g_pd3dDevice->SetRenderState( D3DRS_POINTSIZE,     FtoDW(8.0f) );
	g_pd3dDevice->SetRenderState( D3DRS_POINTSIZE_MIN, FtoDW(0.01f) );
	g_pd3dDevice->SetRenderState( D3DRS_POINTSCALE_A,  FtoDW(0.00f) );
	g_pd3dDevice->SetRenderState( D3DRS_POINTSCALE_B,  FtoDW(0.00f) );
	g_pd3dDevice->SetRenderState( D3DRS_POINTSCALE_C,  FtoDW(1.00f) );


	// Set up the vertex buffer to be rendered
	//    pd3dDevice->SetStreamSource( 0, ifs_vb, 0, sizeof(POINTVERTEX) );
	g_pd3dDevice->SetVertexShader( D3DFVF_XYZ | D3DFVF_DIFFUSE );
/*
g_pd3dDevice->SetRenderState (D3DRS_POINTSCALEENABLE, FALSE);
// All textures must be turned off.
g_pd3dDevice->SetTexture (0, NULL); 
g_pd3dDevice->SetTextureStageState(1, D3DTSS_COLOROP,  D3DTOP_DISABLE);
// The point size render state must be set to any value between 0.0-1.0
g_pd3dDevice->SetRenderState(D3DRS_POINTSIZE, 1.0);
*/

	g_pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
	g_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	g_pd3dDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	g_pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );

    // Turn off culling
    g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

    // Turn off D3D lighting
    g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

	//	printf("%4.2f\n", t);
	g_anim.time = fmodf(t, g_anim.getEndTime());
	g_anim.renderFlame();

	g_pd3dDevice->SetTexture(3, NULL);
	g_pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );
	g_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );
	g_pd3dDevice->SetRenderState( D3DRS_POINTSPRITEENABLE, FALSE);

	g_pd3dDevice->EndScene();
//	g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}