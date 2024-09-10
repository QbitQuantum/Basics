//	this will Initialize DirectX graphics and its window
void TSRD3D11GraphicsSubSystem::InitGraphics( TSRScreenMode& _mode )
{
    DXGI_SWAP_CHAIN_DESC SwapChainDesc;

    ZeroMemory( &SwapChainDesc, sizeof( SwapChainDesc ) );

	unsigned int uiNumSamples = _mode.m_uiSamplesCountForMSAA;
    if ( uiNumSamples == 0 )
    {
        uiNumSamples = 1;
    }

    D3D_RTV_DIMENSION  RenderTargetViewDimension = D3D_RTV_DIMENSION_TEXTURE2D;
    D3D_DSV_DIMENSION  DepthStencilViewDimension = D3D_DSV_DIMENSION_TEXTURE2D;

    if ( uiNumSamples > 1 )
    {
        RenderTargetViewDimension = D3D_RTV_DIMENSION_TEXTURE2DMS;
        DepthStencilViewDimension = D3D_DSV_DIMENSION_TEXTURE2DMS;
    }


	if ( _mode.m_bBackBufferUsesDesktopResolution )
	{
		m_uiBackBufferWidth  = GetSystemMetrics( SM_CXFULLSCREEN );
		m_uiBackBufferHeight = GetSystemMetrics( SM_CYFULLSCREEN );
	}
	else
	{
		m_uiBackBufferWidth  = TSRSystem()->m_DisplayMode.m_uiWidth;
		m_uiBackBufferHeight = TSRSystem()->m_DisplayMode.m_uiHeight;
	}
       
    SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    SwapChainDesc.BufferDesc.Width = m_uiBackBufferWidth;
    SwapChainDesc.BufferDesc.Height = m_uiBackBufferHeight;
    SwapChainDesc.BufferDesc.RefreshRate.Denominator = 60;
    SwapChainDesc.BufferDesc.RefreshRate.Numerator   = 1;
   // SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_CENTERED;
   // SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;

    SwapChainDesc.SampleDesc.Count = uiNumSamples;
    SwapChainDesc.SampleDesc.Quality = 0;

    SwapChainDesc.BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_BACK_BUFFER;
    SwapChainDesc.BufferCount  = 1;
    SwapChainDesc.OutputWindow = SystemWin32()->GetMainHWND();
    SwapChainDesc.Windowed     = TSRSystem()->m_DisplayMode.m_bIsWindowed ? TRUE : FALSE;
    SwapChainDesc.SwapEffect   = DXGI_SWAP_EFFECT_DISCARD;
    SwapChainDesc.Flags        = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    /*UINT uiNumAdapters = 0; 
    IDXGIAdapter* pAdapter; 
    std::vector <IDXGIAdapter*> vAdapters;
    std::vector <DXGI_ADAPTER_DESC> vAdapterDescriptors;
    DXGI_ADAPTER_DESC adapterDesc;
    
    IDXGIFactory * pFactory;
    HRESULT hrr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&pFactory) );

    while(pFactory->EnumAdapters(uiNumAdapters, &pAdapter) != DXGI_ERROR_NOT_FOUND) 
    { 
	    vAdapters.push_back(pAdapter); 
        pAdapter->GetDesc( &adapterDesc );
        vAdapterDescriptors.push_back( adapterDesc );
	    ++uiNumAdapters; 
    } */


	unsigned int uiDeviceCreationFlags = 0;

#ifdef _DEBUG

	/// onwindows 10, deubg flag results in crash, so disabling it for now
	uiDeviceCreationFlags = 0;//D3D_CREATE_DEVICE_DEBUG;

#endif 


#ifdef D3D10_RENDERER

    HRESULT hr = D3D10CreateDeviceAndSwapChain( NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, uiDeviceCreationFlags, D3D10_SDK_VERSION, &SwapChainDesc, &m_pSwapChain, &m_pD3DDevice );

#endif 

#ifdef D3D11_RENDERER

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
    };
    UINT numFeatureLevels = ARRAYSIZE( featureLevels );
    HRESULT hr = D3D11CreateDeviceAndSwapChain( NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, uiDeviceCreationFlags, featureLevels, numFeatureLevels, D3D11_SDK_VERSION, &SwapChainDesc, &m_pSwapChain, &m_pD3DDevice, &m_FeatureLevel, &m_pD3DDeviceContext );

#endif 

    // Create a render target view
    ID3DTexture2D* pBuffer;
    hr = m_pSwapChain->GetBuffer( 0, __uuidof( ID3DTexture2D ), ( LPVOID* ) &pBuffer );
    if( FAILED( hr ) )
    {
        assert( 0 && "Failed to get the back buffer from the swap chain" );
    }

    D3D_RENDER_TARGET_VIEW_DESC DescRT;
    DescRT.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    DescRT.ViewDimension = RenderTargetViewDimension;
    DescRT.Texture2D.MipSlice = 0;
    hr = m_pD3DDevice->CreateRenderTargetView( pBuffer, &DescRT, &m_pColorBufferView );
    pBuffer->Release();
    if( FAILED( hr ) )
    {
        assert( 0 && "Failed to create render target view" );
    }

    // Create depth stencil texture
    D3D_TEXTURE2D_DESC descDepth;
    descDepth.Width = m_uiBackBufferWidth;
    descDepth.Height = m_uiBackBufferHeight;
    descDepth.MipLevels = 1;
    descDepth.ArraySize = 1;
    descDepth.Format = DXGI_FORMAT_D32_FLOAT;
    descDepth.SampleDesc.Count = uiNumSamples;
    descDepth.SampleDesc.Quality = 0;
    descDepth.Usage = D3D_USAGE_DEFAULT;
    descDepth.BindFlags = D3D_BIND_DEPTH_STENCIL;
    descDepth.CPUAccessFlags = 0;
    descDepth.MiscFlags = 0;
    hr = m_pD3DDevice->CreateTexture2D( &descDepth, NULL, &m_pDepthStencil );
    if ( FAILED( hr ) )
    {
        assert( 0 && "Failed to create the depth stencil target" );
    }

    // Create the depth stencil view
    D3D_DEPTH_STENCIL_VIEW_DESC descDSV;
    ZeroMemory( &descDSV, sizeof( D3D_DEPTH_STENCIL_VIEW_DESC ) );
    descDSV.Format = descDepth.Format;
    descDSV.ViewDimension = DepthStencilViewDimension;
    descDSV.Texture2D.MipSlice = 0;
    hr = m_pD3DDevice->CreateDepthStencilView( m_pDepthStencil, &descDSV, &m_pDepthStencilView );
    if ( FAILED( hr ) )
    {
        assert( 0 && "Failed to create the depth stencil view" );
    }

    m_pActiveColorBufferViews[ 0 ] = m_pColorBufferView;
    m_pActiveColorBufferViews[ 1 ] = NULL;
    m_pActiveColorBufferViews[ 2 ] = NULL;
    m_pActiveColorBufferViews[ 3 ] = NULL;
    m_pActiveDepthStencilView = m_pDepthStencilView;

    GetDeviceContext()->OMSetRenderTargets( 1, m_pActiveColorBufferViews, m_pActiveDepthStencilView );

    // set the projection matrix accordingly
    Resize( _mode.m_uiWidth, _mode.m_uiHeight );

    m_pColorBufferTexture = pBuffer;


    /// Create staging selection buffer texture
    D3D_TEXTURE2D_DESC descSelectionBuffer;
    descSelectionBuffer.Width = m_uiBackBufferWidth;
    descSelectionBuffer.Height = m_uiBackBufferHeight;
    descSelectionBuffer.MipLevels = 1;
    descSelectionBuffer.ArraySize = 1;
    descSelectionBuffer.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    descSelectionBuffer.SampleDesc.Count = 1;//uiNumSamples;
    descSelectionBuffer.SampleDesc.Quality = 0;
    descSelectionBuffer.Usage = D3D_USAGE_STAGING;
    descSelectionBuffer.BindFlags = 0;
    descSelectionBuffer.CPUAccessFlags = D3D_CPU_ACCESS_READ ;
    descSelectionBuffer.MiscFlags = 0;
    hr = m_pD3DDevice->CreateTexture2D( &descSelectionBuffer, NULL, &m_pCpuBackBufferCopy );
    if ( FAILED( hr ) )
    {
        assert( 0 && "Failed to create the selection buffer" );
    }

	m_pQueryIdleGPU = NULL;


	D3D_QUERY_DESC queryDesc;
	queryDesc.MiscFlags = 0;
	queryDesc.Query = D3D_QUERY_EVENT;
    m_pD3DDevice->CreateQuery( &queryDesc, &m_pQueryIdleGPU );


#ifdef D3D10_RENDERER
    TSRPrintln( "D3D10 initialized successfully" );
#endif 

    
#ifdef D3D11_RENDERER
    TSRPrintln( "D3D11 initialized successfully" );
#endif

#ifdef D3D10_RENDERER
    TSRPrintln( "D3D10 initialized successfully" );
#endif 
}