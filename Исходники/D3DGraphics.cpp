    //-----------------------------------------------------------------------------
    //  Initialize
    //  Performs any API specific initialization tasks (wind order, etc)
    //-----------------------------------------------------------------------------
    Result CD3DDevice::Initialize( CWindow* pWindow )
    {
        HRESULT hr = S_OK;
        HWND hWnd = static_cast<HWND>( pWindow->GetWindow() );

        // Get the actual client size of the window
        RECT rcClient;
        GetClientRect( hWnd, &rcClient );
        unsigned int nWidth = rcClient.right - rcClient.left;
        unsigned int nHeight = rcClient.bottom - rcClient.top;

        // TODO: Don't use these hardcoded values
        int     nAACount = 1,
                nAAQuality = 0;
        bool    bWindowed = true;

        /////////////////////////////////////////
        // Create the swap chain description
        DXGI_SWAP_CHAIN_DESC tSwapChainDesc = {0};
        tSwapChainDesc.BufferCount          = 2;         // buffer count
        tSwapChainDesc.BufferDesc.Width     = nWidth;    // width of the window
        tSwapChainDesc.BufferDesc.Height    = nHeight;   // height of the window
        tSwapChainDesc.BufferDesc.Format    = DXGI_FORMAT_R8G8B8A8_UNORM;   // Back buffer format
        // TODO: Don't hardcode this
        tSwapChainDesc.BufferDesc.RefreshRate.Numerator     = 60;   // Refresh rate
        tSwapChainDesc.BufferDesc.RefreshRate.Denominator   = 1;    // Refresh rate
        tSwapChainDesc.BufferUsage          = DXGI_USAGE_RENDER_TARGET_OUTPUT; // Its a render target!
        tSwapChainDesc.OutputWindow         = hWnd;       // Window to attach to
        tSwapChainDesc.SampleDesc.Count     = nAACount;   // AA count
        tSwapChainDesc.SampleDesc.Quality   = nAAQuality; // AA quality
        tSwapChainDesc.Windowed             = bWindowed;  // Windowed!! Yay!
        tSwapChainDesc.Flags                = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;   // TODO: Fix the fullscreen 'ding'.
                                                                                        // DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH isn't what causes it...


        /////////////////////////////////////////
        // Create the DX device
        D3D_FEATURE_LEVEL FeatureLevel;
        unsigned int nFlags = 0;
#ifdef DEBUG
        nFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

        hr = D3D11CreateDeviceAndSwapChain(    
            0,                        // physical adapter to try
            D3D_DRIVER_TYPE_HARDWARE, // TODO: Add support for software/warp
            0,                        // TODO: Add support for software/warp
            nFlags,                   // Creation flags
            NULL,                     // Feature levels to try
            0,                        // Number of feature levels
            D3D11_SDK_VERSION,        // The SDK version
            &tSwapChainDesc,          // The Swap chain description
            &m_pSwapChain,            // The swap chain
            &m_pDevice,               // the device
            &FeatureLevel,            // The feature level being used
            &m_pContext );            // The context!

        if( FAILED( hr ) )
        {
            // TODO: Handle gracefully
            ASSERT( FALSE );
            MessageBox( 0, L"Could not create DX device/swap chain", L"Error", 0 );
            return rResultFailure;
        }

        ///////////////////////////////////////////////
        // Do any feature level specific stuff
        switch( FeatureLevel )
        {
        case D3D_FEATURE_LEVEL_11_0:
            {
                strcpy( m_szVSProfile, "vs_5_0" );
                strcpy( m_szPSProfile, "ps_5_0" );
                break;
            }
        case D3D_FEATURE_LEVEL_10_1:
            {
                strcpy( m_szVSProfile, "vs_4_1" );
                strcpy( m_szPSProfile, "ps_4_1" );
                break;
            }
        case D3D_FEATURE_LEVEL_10_0:
            {
                strcpy( m_szVSProfile, "vs_4_0" );
                strcpy( m_szPSProfile, "ps_4_0" );
                break;
            }
        case D3D_FEATURE_LEVEL_9_3:
            {
                strcpy( m_szVSProfile, "vs_3_0" );
                strcpy( m_szPSProfile, "ps_3_0" );
                break;
            }
        default:
            {
                break;
            }
        };

        // Resize everything
        Resize( nWidth, nHeight );

        // Create the rasterizer states
        D3D11_RASTERIZER_DESC rd;
        Memset( &rd, 0, sizeof(rd) );

        // Solid
        rd.CullMode = D3D11_CULL_BACK;
        rd.FillMode = D3D11_FILL_SOLID;
        rd.DepthClipEnable = TRUE;

        hr = m_pDevice->CreateRasterizerState( &rd, &m_pSolidRasterizerState );

        // wireframe
        rd.FillMode = D3D11_FILL_WIREFRAME;
        rd.CullMode = D3D11_CULL_NONE;

        hr = m_pDevice->CreateRasterizerState( &rd, &m_pWireframeRasterizerState );

        //////////////////////////////////////////
        // Create depth states
        D3D11_DEPTH_STENCIL_DESC dsd;
        dsd.DepthEnable = true;
        dsd.StencilEnable = false;
        dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
        dsd.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

        hr = m_pDevice->CreateDepthStencilState( &dsd, &m_pDepthWriteTest );
        ASSERT( hr == S_OK );

        dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;

        hr = m_pDevice->CreateDepthStencilState( &dsd, &m_pDepthNoWriteTest );
        ASSERT( hr == S_OK );

        dsd.DepthEnable = false;
        dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;

        hr = m_pDevice->CreateDepthStencilState( &dsd, &m_pDepthWriteNoTest );
        ASSERT( hr == S_OK );

        dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;

        hr = m_pDevice->CreateDepthStencilState( &dsd, &m_pDepthNoWriteNoTest );
        ASSERT( hr == S_OK );

        //////////////////////////////////////////
        //  Blend states
        D3D11_BLEND_DESC bd = { 0 };
        bd.AlphaToCoverageEnable = false;
        bd.IndependentBlendEnable = false;
        bd.RenderTarget[0].RenderTargetWriteMask = 0;

        hr = m_pDevice->CreateBlendState( &bd, &m_pColorDisableBlendState );
        ASSERT( hr == S_OK );

        bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
        hr = m_pDevice->CreateBlendState( &bd, &m_pColorEnableBlendState );
        ASSERT( hr == S_OK );


        return rResultSuccess;
    }