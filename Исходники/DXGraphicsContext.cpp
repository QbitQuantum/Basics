bool CDXGraphicsContext::Initialize(HWND hWnd, HWND hWndStatus,
									 uint32 dwWidth, uint32 dwHeight,
									 BOOL bWindowed )
{
	HRESULT hr;

	if( g_GraphicsInfo.hStatusBar )
	{
		SetWindowText(g_GraphicsInfo.hStatusBar,"Initializing DirectX Device, please wait");
	}

	Lock();

	// Create the Direct3D object
	m_pD3D = Direct3DCreate9( D3D_SDK_VERSION );
	if( m_pD3D == NULL )
	{
		Unlock();
		DisplayD3DErrorMsg( D3DAPPERR_NODIRECT3D, MSGERR_APPMUSTEXIT );
		return false;
	}

	CGraphicsContext::Initialize(hWnd, hWndStatus, dwWidth, dwHeight, bWindowed );
	
	hr = Create3D( bWindowed );

	// Clear/Update a few times to ensure that all of the buffers are cleared
	if ( m_pd3dDevice )
	{
		Clear(CLEAR_COLOR_AND_DEPTH_BUFFER);
		m_pd3dDevice->BeginScene();
		m_pd3dDevice->EndScene();
		UpdateFrame();
	}

	D3DVIEWPORT9 vp = {
		0, 
			windowSetting.toolbarHeightToUse, 
			windowSetting.uDisplayWidth, 
			windowSetting.uDisplayHeight, 0, 1
	};
	gD3DDevWrapper.SetViewport(&vp);
	
	Unlock();

	g_pD3DDev->GetDeviceCaps(&g_D3DDeviceCaps);

	if( g_GraphicsInfo.hStatusBar )
	{
		SetWindowText(g_GraphicsInfo.hStatusBar,"DirectX device is ready");
	}

	return hr==S_OK;
}