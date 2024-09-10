bool DirectX11Graphics::Initialise()
{
	if ( _is_initialised )
	{
		//LogError( "F11", "Cannot initialise F11Graphics; F11Graphics is currently initialised." );
		return false;
	}

	// Return false if no game has been set.
	if ( !GetGame() )
	{
		//LogError( "F11", "Cannot initialise F11Graphics; F11Graphics has no graphics message listener set." );
		return false;
	}

	// Get the dimensions of the screen.

	RECT rectangle;
	GetClientRect( HWND(GetGame()->GetHWND()), &rectangle );

	unsigned int width = rectangle.right - rectangle.left;
	unsigned int height = rectangle.bottom - rectangle.top;

	if ( VRIsEnabled() )
	{	
		GetGame()->GetVRTextureDimensions( width, height );
	}

	// Use the default adapter and hardware drivers.

	IDXGIFactory* factory = nullptr;
	IDXGIAdapter* adapter = nullptr;

	auto f = CreateDXGIFactory( __uuidof(IDXGIFactory), (void**)&factory );

	auto a = factory->EnumAdapters( 0, &adapter );
	
	// Create a debug device if in debug mode.

#ifdef _DEBUG
	unsigned int device_flags = D3D11_CREATE_DEVICE_DEBUG;
#else
	unsigned int device_flags = 0;
#endif

	// Create a swap chain description.

	DXGI_SWAP_CHAIN_DESC swap_chain_desc;
	
	memset( &swap_chain_desc, 0, sizeof(swap_chain_desc) );
	swap_chain_desc.BufferDesc.Width = width;
	swap_chain_desc.BufferDesc.Height = height;
	swap_chain_desc.BufferDesc.RefreshRate.Numerator = 0;
	swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
	swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//swap_chain_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	//swap_chain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_CENTERED;
	swap_chain_desc.SampleDesc.Count = 1;
	swap_chain_desc.SampleDesc.Quality = 0;
	swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap_chain_desc.BufferCount = 2;
	swap_chain_desc.OutputWindow = HWND(GetGame()->GetHWND());
	swap_chain_desc.Windowed = true;
	swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_SEQUENTIAL;
	swap_chain_desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	// Create the swap chain, device and immediate device context.
	
	if ( FAILED( D3D11CreateDevice(	adapter,
									adapter ? D3D_DRIVER_TYPE_UNKNOWN : D3D_DRIVER_TYPE_HARDWARE,
									nullptr,
									device_flags,
									nullptr,
									0,
									D3D11_SDK_VERSION,
									&_device,
									nullptr,
									&_immediate_device_context ) ) )
	{
		//LogError( "F11", "Cannot initialise F11Graphics; cannot create device and swapchain." );
		return false;
	}

	if ( adapter )
	{
		adapter->Release();
	}

	if ( FAILED( factory->CreateSwapChain( _device, &swap_chain_desc, &_swap_chain ) ) )
	{
		return false;
	}
	ID3D11Texture2D* backbuffer = nullptr;
    HRESULT hr = _swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backbuffer);
    if (FAILED(hr))
        return false;

    hr = _device->CreateRenderTargetView(backbuffer, nullptr, &_back_buffer);
    if (FAILED(hr))
        return false;

	SetWidth( width );
	SetHeight( height );

	if ( backbuffer )
	{
		backbuffer->Release();
	}

	if ( factory )
	{
		factory->Release();
	}

	if ( VRIsEnabled() )
	{
		{
			D3D11_BUFFER_DESC cbuffer_desc;
			cbuffer_desc.ByteWidth = sizeof(OculusBlit_cbuffer);
			cbuffer_desc.Usage = D3D11_USAGE_DYNAMIC;
			cbuffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			cbuffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			cbuffer_desc.MiscFlags = 0;
			cbuffer_desc.StructureByteStride = sizeof(OculusBlit_cbuffer);

			if ( FAILED( Device()->CreateBuffer( &cbuffer_desc, nullptr, &_oculus_blit_cbuffer ) ) )
			{
				return false;
			}
		}
		
		_swap_chain->SetFullscreenState( 1, nullptr );
	}


	if (0)
	{
		// Get the dxgi factory and disable fullscreen toggling with alt+enter.

		IDXGIDevice* dxgi_device = nullptr;
		if ( FAILED( _device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgi_device) ) )
		{
			//LogError( "F11", "Cannot initialise F11Graphics; cannot get DXGI device." );
			return false;
		}

		if ( FAILED( dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void **)&adapter) ) )
		{
			//LogError( "F11", "Cannot initialise F11Graphics; cannot get DXGI adapter." );
			return false;
		}

		IDXGIFactory * factory = nullptr;
		if ( FAILED( adapter->GetParent(__uuidof(IDXGIFactory), (void **)&factory) ) )
		{
			//LogError( "F11", "Cannot initialise F11Graphics; cannot get DXGI factory." );
			return false;
		}

		factory->MakeWindowAssociation( HWND(GetGame()->GetHWND()), DXGI_MWA_NO_WINDOW_CHANGES );

		dxgi_device->Release();
		adapter->Release();
		factory->Release();
	}
	
	// Create the back buffer by resizing
	//Resize( width, height );

	_resources.SetConfig(GetGraphicsSettings());
	if ( !_resources.Initialise() )
	{
		return false;
	}
		
	Resize( width, height );

	_is_initialised = true;
	
	return true;
}