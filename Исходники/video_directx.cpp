BOOL dx9vid_init()
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);    // create the Direct3D interface
	D3DCAPS9 d3dCaps;
	d3d->GetDeviceCaps( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &d3dCaps );
	d3d->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm );

	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.Windowed               = TRUE;
	d3dpp.SwapEffect             = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat       = d3ddm.Format;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.PresentationInterval   = D3DPRESENT_INTERVAL_IMMEDIATE;

	d3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hwnd,
						D3DCREATE_SOFTWARE_VERTEXPROCESSING,
						&d3dpp, &d3ddev );

	// Create the screen texture
	D3DXCreateTexture( d3ddev, 256, 256, D3DX_FILTER_NONE, D3DUSAGE_DYNAMIC, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &g_screenTex);

	// Create the screen sprite (ignores 3d perspective)
	D3DXCreateSprite( d3ddev, &g_screenSprite );

	// Scale our matrix to match the screen
	D3DXMatrixIdentity( &pTransform );
	spritePos = D3DXVECTOR2( 0.f, 0.f );
	rotCenter = D3DXVECTOR2( 0.f, 0.f);
	D3DXVECTOR2 vscale = D3DXVECTOR2( float(3.0f), float(3.0f));
	D3DXMatrixTransformation2D( &pTransform, NULL, 0.0f, &vscale, &rotCenter, 0.f, &spritePos );
	g_screenSprite->SetTransform(&pTransform);

	return TRUE;
}