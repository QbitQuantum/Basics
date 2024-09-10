	bool CRenderDevice::DeviceAndSwapChain(HRESULT& hr, HWND hWnd)
	{
		RECT rc;
		ZeroMemory( &rc, sizeof(rc) );
		GetClientRect( hWnd, &rc );

		m_ViewWidth = rc.right - rc.left;
		m_ViewHeight = rc.bottom - rc.top;


		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory( &sd, sizeof( sd ) );
		sd.BufferCount = 1;
		sd.BufferDesc.Width = m_ViewWidth;             // Target window size
		sd.BufferDesc.Height = m_ViewHeight;           // --"--
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // Pixel format of target window
		sd.BufferDesc.RefreshRate.Numerator = 60;          // Refresh rate of monitor
		sd.BufferDesc.RefreshRate.Denominator = 1;         // --"--

		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.OutputWindow = hWnd;                          // Target window
		sd.Windowed = TRUE;                                // Whether to render in a window (TRUE) or go fullscreen (FALSE)
		hr = D3D10CreateDeviceAndSwapChain( NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, 0,
											D3D10_SDK_VERSION, &sd, &m_pSwapChain, &m_pd3dDevice );
		if( FAILED( hr ) )
		{
			MessageBox( NULL, "NO DEVICE OR SWAP CHAIN", "", NULL );
			return false;
		}

		return true;
	}