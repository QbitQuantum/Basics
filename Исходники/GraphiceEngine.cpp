HRESULT KGraphicsEngine::InitializeWindowed(HWND hBaseWindow, HWND hRenderWindow)
{
	// Create the D3D object.
    if ( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
	{
		MessageBox(hBaseWindow,"Failed Create the D3D object!.","Failed Create the D3D object!",0);
        return E_FAIL;
	}
    // Get the current desktop display mode, so we can set up a back
    // buffer of the same format
	g_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,&g_D3DCaps);

    if ( FAILED( g_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &m_DisplayMode ) ) )
	{
		MessageBox(hBaseWindow,"Failed GetAdapterDisplayMode !.","Failed Create the D3D object!",0);
		return E_FAIL;
	}
     
    // Set up the structure used to create the D3DDevice
	D3DFORMAT  DepFormat;
	if (SUCCEEDED(g_pD3D->CheckDepthStencilMatch(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		m_DisplayMode.Format,
		m_DisplayMode.Format,
		D3DFMT_D24S8)))
	{
		DepFormat = D3DFMT_D24S8;
	}
	else
	{
		DepFormat = D3DFMT_D16;
	}

    memset( &m_PresentParam, 0, sizeof(D3DPRESENT_PARAMETERS) );

    memset(&m_RenderWindowRect, 0, sizeof(m_RenderWindowRect));	

	if(hRenderWindow)
		::GetWindowRect(hRenderWindow,&m_RenderWindowRect);
	else
	{
		::GetWindowRect(hBaseWindow,&m_RenderWindowRect);
		hRenderWindow = hBaseWindow;
	}
		
	//m_PresentParam.BackBufferWidth = m_RenderWindowRect.right-m_RenderWindowRect.left ;
    //m_PresentParam.BackBufferHeight= m_RenderWindowRect.bottom - m_RenderWindowRect.top;
	m_PresentParam.BackBufferWidth = m_DisplayMode.Width ;
	m_PresentParam.BackBufferHeight= m_DisplayMode.Height;

    m_PresentParam.Windowed = TRUE ;
    m_PresentParam.SwapEffect = D3DSWAPEFFECT_DISCARD;
    m_PresentParam.BackBufferFormat = m_DisplayMode.Format;
	m_PresentParam.EnableAutoDepthStencil = TRUE;
    m_PresentParam.AutoDepthStencilFormat = DepFormat;
    m_PresentParam.MultiSampleType = D3DMULTISAMPLE_NONE;
    m_PresentParam.hDeviceWindow = hBaseWindow;
    m_PresentParam.Flags = 0;
    m_PresentParam.FullScreen_RefreshRateInHz = 0;
    m_PresentParam.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	//just set camera's aspect
	m_cCamera.Aspect = m_PresentParam.BackBufferWidth*1.0f/m_PresentParam.BackBufferHeight; 

	HRESULT hr;

	// Set default settings
	UINT AdapterToUse=D3DADAPTER_DEFAULT;
	D3DDEVTYPE DeviceType=D3DDEVTYPE_HAL;
//#if SHIPPING_VERSION
	// When building a shipping version, disable NVPerfHUD (opt-out)
//#else
	// Look for 'NVIDIA NVPerfHUD' adapter
	// If it is present, override default settings
	for (UINT Adapter=0;Adapter<g_pD3D->GetAdapterCount();Adapter++)
	{
		D3DADAPTER_IDENTIFIER9 Identifier;
		HRESULT Res=g_pD3D->GetAdapterIdentifier(Adapter,0,&Identifier);
		if (strcmp(Identifier.Description,"NVIDIA NVPerfHUD")==0)
		{
			AdapterToUse=Adapter;
			DeviceType=D3DDEVTYPE_REF;
			break;
		}
	}
//#endif

    // Create the D3DDevice
    /*if ( FAILED(hr = g_pD3D->CreateDevice( AdapterToUse, DeviceType, hBaseWindow,
                                      D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                      &m_PresentParam, &g_pd3dDevice ) ) )
    {*/
		if ( FAILED(hr = g_pD3D->CreateDevice( AdapterToUse, DeviceType, hBaseWindow,
                                      D3DCREATE_MIXED_VERTEXPROCESSING,
                                      &m_PresentParam, &g_pd3dDevice ) ) )
		{
			if ( FAILED(hr = g_pD3D->CreateDevice( AdapterToUse, DeviceType, hBaseWindow,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &m_PresentParam, &g_pd3dDevice ) ) )
			{
				
				if (hr == D3DERR_INVALIDCALL)
					MessageBox(hBaseWindow,"The method call is invalid. For example, a method's parameter may have an invalid value.","Failed Create Device!",0);
				else if (hr == E_OUTOFMEMORY )
					MessageBox(hBaseWindow,"Direct3D could not allocate sufficient memory to complete the call.","Failed Create Device!",0);
				else if (hr == D3DERR_OUTOFVIDEOMEMORY)
					MessageBox(hBaseWindow,"Direct3D does not have enough display memory to perform the operation. ","Failed Create Device!",0);
				return E_FAIL;
			}
		}
	
  /*  }*/
    
//	D3DMULTISAMPLE_TYPE Mul = D3DMULTISAMPLE_4_SAMPLES;
//
//	if( FAILED(g_pD3D->CheckDeviceMultiSampleType( D3DADAPTER_DEFAULT, 
//			D3DDEVTYPE_HAL, m_PresentParam.BackBufferFormat, 
//			FALSE, Mul, NULL ) ) &&
//			SUCCEEDED(g_pD3D->CheckDeviceMultiSampleType( D3DADAPTER_DEFAULT, 
//			D3DDEVTYPE_HAL, m_PresentParam.AutoDepthStencilFormat, 
//			FALSE, Mul, NULL ) ) )
//	{
//		Mul = D3DMULTISAMPLE_3_SAMPLES; 
//
//		if( FAILED(g_pD3D->CheckDeviceMultiSampleType( D3DADAPTER_DEFAULT, 
//			D3DDEVTYPE_HAL, m_PresentParam.BackBufferFormat, 
//			FALSE, Mul, NULL ) ) &&
//			SUCCEEDED(g_pD3D->CheckDeviceMultiSampleType( D3DADAPTER_DEFAULT, 
//			D3DDEVTYPE_HAL, m_PresentParam.AutoDepthStencilFormat, 
//			FALSE, Mul, NULL ) ) )
//		{
//			Mul = D3DMULTISAMPLE_2_SAMPLES; 
//
//			if( FAILED(g_pD3D->CheckDeviceMultiSampleType( D3DADAPTER_DEFAULT, 
//				D3DDEVTYPE_HAL, m_PresentParam.BackBufferFormat, 
//				FALSE, Mul, NULL ) ) &&
//				SUCCEEDED(g_pD3D->CheckDeviceMultiSampleType( D3DADAPTER_DEFAULT, 
//				D3DDEVTYPE_HAL, m_PresentParam.AutoDepthStencilFormat, 
//				FALSE, Mul, NULL ) ) )
//			{
//				Mul = D3DMULTISAMPLE_NONE; 
//			}
//		}
//	}
//	if (Mul != D3DMULTISAMPLE_NONE)
//	{
//		m_PresentParam.MultiSampleType = Mul;
//		g_pd3dDevice->Reset( &m_PresentParam );
//	}
    
    // Device state would normally be set here
	// Turn off culling, so we see the front and back of the triangle
     g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW  );

    // Turn off D3D lighting, since we are providing our own vertex colors

    // Turn on the zbuffer
    g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
    //g_pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE , TRUE );
    g_pd3dDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL  );

	g_cGraphicsTool.SetCurCamera(&m_cCamera);
	
	PreRender(); 
	m_bWindowed = TRUE;
    
	if (m_bUseMotionBlur)
	{
		BackBufferCreate();
		
		g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL,
			0xff666666, 1.0f, 0 );
	}

	return S_OK;
}