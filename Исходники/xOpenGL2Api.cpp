bool xGL2RenderApi::__createD10Device()
{
      HRESULT hr = S_OK;;

      UINT width  = m_Width;
      UINT height = m_Height;

      if(width == 0 || height == 0)
      {
            RECT rc;
            GetClientRect( m_hMainWnd, &rc );
            width = rc.right - rc.left;
            height = rc.bottom - rc.top;
            m_Width  = width;
            m_Height = height;

      }
      UINT createDeviceFlags = 0;
#ifdef _DEBUG
      createDeviceFlags |= GL2_CREATE_DEVICE_DEBUG;
#endif

      GL2_DRIVER_TYPE driverTypes[] = 
      {
            GL2_DRIVER_TYPE_HARDWARE,            
            GL2_DRIVER_TYPE_REFERENCE,
            GL2_DRIVER_TYPE_REFERENCE,
            GL2_DRIVER_TYPE_REFERENCE,
            GL2_DRIVER_TYPE_REFERENCE,
            GL2_DRIVER_TYPE_REFERENCE,
      };
      HMODULE hDriverModule[]=
      {
            NULL,
            LoadLibraryA( "GL2WARP_beta.DLL" ),
            LoadLibraryW( _XEVOL_ABSPATH_(L"GL2WARP_beta.DLL") ),
            LoadLibraryA( "GL2WARP.DLL" ),
            LoadLibraryW( _XEVOL_ABSPATH_(L"GL2WARP.DLL" ) ),
            NULL,
      };

      UINT numDriverTypes = sizeof(driverTypes) / sizeof(driverTypes[0]);


      m_Width   = width;
      m_Height  = height;
      ZeroMemory( &m_swapChainDesc, sizeof(m_swapChainDesc) );
      m_swapChainDesc.BufferCount = 1;
      m_swapChainDesc.BufferDesc.Width = width;
      m_swapChainDesc.BufferDesc.Height = height;
      m_swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
      m_swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
      m_swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
      m_swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
      m_swapChainDesc.OutputWindow = m_hMainWnd;
      m_swapChainDesc.SampleDesc.Count = 1;
      m_swapChainDesc.SampleDesc.Quality = 0;
      m_swapChainDesc.Windowed = TRUE;

      //Find all Adapter
      IDXGIAdapter * pAdapter;
      std::vector<IDXGIAdapter*> vAdapters;
      IDXGIFactory* pDXGIFactory = NULL;
       hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&pDXGIFactory) );

      while(pDXGIFactory->EnumAdapters(vAdapters.size(), &pAdapter) != DXGI_ERROR_NOT_FOUND)
      {
            vAdapters.push_back(pAdapter);
      }


      for(int i = 0 ; i < vAdapters.size() ; i ++)
      {
            IDXGIAdapter* pAdapter = vAdapters[i];
            DXGI_ADAPTER_DESC desc;
            pAdapter->GetDesc(&desc);

            std::vector<IDXGIOutput*> vOutputers;
            IDXGIOutput* pOutputer = NULL;
            while(pAdapter->EnumOutputs(vOutputers.size(), &pOutputer) != DXGI_ERROR_NOT_FOUND)
            {
                  vOutputers.push_back(pOutputer);
                  DXGI_OUTPUT_DESC odesc;
                  pOutputer->GetDesc(&odesc);
                  continue;
            }

            for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
            {
                  m_driverType = driverTypes[driverTypeIndex];
                  HMODULE hModule = hDriverModule[driverTypeIndex];
                  hr = GL2CreateDeviceAndSwapChain( pAdapter, m_driverType, hModule , createDeviceFlags, GL2_SDK_VERSION, &m_swapChainDesc, &m_pSwapChain, &m_pGL2Device );
                  if( SUCCEEDED( hr ) )
                        break;
            }
            if(m_pGL2Device && m_pSwapChain)
            {
                  break;
            }
      }
   


      if( FAILED(hr) )
            return false;


      m_RenderWindow = new xGL2RenderWindow(m_hMainWnd , this);
      m_RenderWindow->create(m_pSwapChain , width , height);
      __resetViewPort();
      setRenderView(m_RenderWindow);

      GL2_BLEND_DESC BlendState;
      ZeroMemory(&BlendState, sizeof(GL2_BLEND_DESC));
      BlendState.BlendEnable[0] = FALSE;
      BlendState.RenderTargetWriteMask[0] = GL2_COLOR_WRITE_ENABLE_ALL;

      ID3D10BlendState*       g_pBlendStateNoBlend = NULL;
      ID3D10RasterizerState*	g_pRasterizerStateNoCull = NULL;
      m_pGL2Device->CreateBlendState(&BlendState, &g_pBlendStateNoBlend) ;

      // Create a rasterizer state to disable culling
      GL2_RASTERIZER_DESC RSDesc;
      RSDesc.FillMode = GL2_FILL_SOLID;
      RSDesc.CullMode = GL2_CULL_NONE;
      RSDesc.FrontCounterClockwise = TRUE;
      RSDesc.DepthBias = 0;
      RSDesc.DepthBiasClamp = 0;
      RSDesc.SlopeScaledDepthBias = 0;
      RSDesc.ScissorEnable = FALSE;
      RSDesc.MultisampleEnable = TRUE;
      RSDesc.AntialiasedLineEnable = FALSE;
      m_pGL2Device->CreateRasterizerState(&RSDesc, &g_pRasterizerStateNoCull) ;

      m_pGL2Device->OMSetBlendState(g_pBlendStateNoBlend, 0, 0xffffffff);
      m_pGL2Device->RSSetState(g_pRasterizerStateNoCull);
      return true;
}