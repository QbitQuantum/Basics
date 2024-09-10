	bool PlatformD3D11::InitDeviceAndSwapChain(bool fullscreen)
	{
		IDXGIFactory* factory = NULL;
		IDXGIAdapter* adapter = NULL;
		IDXGIOutput* adapter_output = NULL;
		HRESULT hresult = S_OK;

		// Determine the resolution of the clients desktop screen.
		UInt32 screen_width  = GetSystemMetrics(SM_CXSCREEN);
		UInt32 screen_height = GetSystemMetrics(SM_CYSCREEN);

		UInt32 numerator = 0;
		UInt32 denominator = 1;

		// Create a DirectX graphics interface factory.
		hresult = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
		if(SUCCEEDED(hresult))
		{
			// Use the factory to create an adapter for the primary graphics interface (video card).
			hresult = factory->EnumAdapters(0, &adapter);
		}


		// Enumerate the primary adapter output (monitor).
		if(SUCCEEDED(hresult))
			hresult = adapter->EnumOutputs(0, &adapter_output);

		// Get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM display format for the adapter output (monitor).
		UInt32 num_modes = 0;
		if(SUCCEEDED(hresult))
			hresult = adapter_output->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &num_modes, NULL);

		if(SUCCEEDED(hresult))
		{
			// Create a list to hold all the possible display modes for this monitor/video card combination.
			DXGI_MODE_DESC* display_mode_list = new DXGI_MODE_DESC[num_modes];

			// Now fill the display mode list structures.
			hresult = adapter_output->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &num_modes, display_mode_list);
			if(SUCCEEDED(hresult))
			{	
				// Now go through all the display modes and find the one that matches the screen width and height.
				// When a match is found store the numerator and denominator of the refresh rate for that monitor.
				for(UInt32 i=0; i<num_modes; i++)
				{
					if(display_mode_list[i].Width == (unsigned int)screen_width)
					{
						if(display_mode_list[i].Height == (unsigned int)screen_height)
						{
							numerator = display_mode_list[i].RefreshRate.Numerator;
							denominator = display_mode_list[i].RefreshRate.Denominator;
						}
					}
				}
			}
			// Release the display mode list.
			delete [] display_mode_list;
			display_mode_list = 0;
		}

		// Release the adapter output.
		ReleaseNull(adapter_output);
		ReleaseNull(adapter);
		ReleaseNull(factory);

		UINT create_device_flags = 0;
	#ifdef _DEBUG
		// causes a crash on lab PCs
		//create_device_flags |= D3D11_CREATE_DEVICE_DEBUG;
	#endif

		D3D_DRIVER_TYPE driver_types[] =
		{
			D3D_DRIVER_TYPE_HARDWARE,
			D3D_DRIVER_TYPE_REFERENCE,
		};
		UINT num_driver_types = sizeof( driver_types ) / sizeof( driver_types[0] );

		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory( &sd, sizeof( sd ) );
		sd.BufferCount = 1;
		sd.BufferDesc.Width = window_->width();
		sd.BufferDesc.Height = window_->height();
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		if(vsync_enabled_)
		{
			sd.BufferDesc.RefreshRate.Numerator = numerator;
			sd.BufferDesc.RefreshRate.Denominator = denominator;
		}
		else
		{
			sd.BufferDesc.RefreshRate.Numerator = 0;
			sd.BufferDesc.RefreshRate.Denominator = 1;
		}
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = window_->hwnd();
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = fullscreen ? FALSE : TRUE;

		// Set the feature level to DirectX 11.
		D3D_FEATURE_LEVEL feature_levels[] =
		{
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
		};
		UINT num_feature_levels = sizeof( feature_levels ) / sizeof( feature_levels[0] );
	
		for( UINT driver_type_index = 0; driver_type_index < num_driver_types; driver_type_index++ )
		{
			driver_type_ = driver_types[driver_type_index];
			hresult = D3D11CreateDeviceAndSwapChain( NULL, this->driver_type_, NULL, create_device_flags, feature_levels, num_feature_levels,
				D3D11_SDK_VERSION, &sd, &swap_chain_, &device_, NULL, &device_context_);
			if( SUCCEEDED( hresult ) )
				break;
		}
    
		if SUCCEEDED( hresult )
			return true;
		else
		{