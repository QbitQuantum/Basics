	bool H3DRenderer::Initialize(int screen_width, int screen_height, bool vsync,
						HWND hwnd, bool full_screen, float screen_depth, float screen_near)
	{
		HRESULT							result = S_OK;
		IDXGIFactory*					factory = NULL;
		IDXGIAdapter*					adapter = NULL;
		IDXGIOutput*					adapter_output = NULL;
		unsigned int					num_modes, i, numerator, denominator;
		DXGI_MODE_DESC*					display_mode_list;
		DXGI_SWAP_CHAIN_DESC			swap_chain_desc;
		D3D_FEATURE_LEVEL				feature_level;
		ID3D11Texture2D*				back_buffer;
		D3D11_TEXTURE2D_DESC			depth_buffer_desc;
		D3D11_DEPTH_STENCIL_DESC		depth_stencil_desc;				// 用来设置ds缓冲区state的desc结构体
		D3D11_DEPTH_STENCIL_VIEW_DESC	depth_stencil_view_desc;
		D3D11_RASTERIZER_DESC			rasterDesc;
		D3D11_VIEWPORT					viewport;
		D3D11_DEPTH_STENCIL_DESC		depth_disable_stencil_desc;
		D3D11_BLEND_DESC				blend_state_desc;

		// 垂直同步是否开启
		vsync_enabled_ = vsync;
		sync_interval_ = vsync_enabled_ ? 1 : 0;

		// Create a DirectX graphics interface factory.
		result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
		if(FAILED(result))
		{
			return false;
		}

		// Use the factory to create an adapter for the primary graphics interface (video card).
		result = factory->EnumAdapters(0, &adapter);
		if(FAILED(result))
		{
			return false;
		}

		// Enumerate the primary adapter output (monitor).
		result = adapter->EnumOutputs(0, &adapter_output);
		if(FAILED(result))
		{
			return false;
		}

		// directx11时代，只枚举RGBA32位颜色模式，不需要搞其他了
		result = adapter_output->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, 
												DXGI_ENUM_MODES_INTERLACED, &num_modes, NULL);
		if(FAILED(result))
		{
			return false;
		}

		// Create a list to hold all the possible display modes for this monitor/video card combination.
		display_mode_list = new DXGI_MODE_DESC[num_modes];
		if(!display_mode_list)
		{
			return false;
		}

		// Now fill the display mode list structures.
		result = adapter_output->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &num_modes, display_mode_list);
		if(FAILED(result))
		{
			return false;
		}

		// Now go through all the display modes and find the one that matches the screen width and height.
		// When a match is found store the numerator and denominator of the refresh rate for that monitor.
		for(i=0; i<num_modes; i++)
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

		// Release the display mode list.
		delete [] display_mode_list;
		display_mode_list = 0;

		// Release the adapter output.
		adapter_output->Release();
		adapter_output = 0;

		// Release the adapter.
		adapter->Release();
		adapter = 0;

		// Release the factory.
		factory->Release();
		factory = 0;

		// 填充swap chain结构，这个swap chain将和main backbuffer关联
		ZeroMemory(&swap_chain_desc, sizeof(swap_chain_desc));

		// 仅设置本swap chain的backbuffer为1个，如果想在多窗口使用
		// 同一个renderer的话，这里就要指定多个bufferCount了
		swap_chain_desc.BufferCount = 1;
		swap_chain_desc.BufferDesc.Width = screen_width;
		swap_chain_desc.BufferDesc.Height = screen_height;
		swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		// Set the refresh rate of the back buffer.
		if(vsync_enabled_)
		{
			swap_chain_desc.BufferDesc.RefreshRate.Numerator = numerator;
			swap_chain_desc.BufferDesc.RefreshRate.Denominator = denominator;
		}
		else
		{
			swap_chain_desc.BufferDesc.RefreshRate.Numerator = 0;
			swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
		}

		//  指定这个render target是用来output用的
		swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swap_chain_desc.OutputWindow = hwnd;
		swap_chain_desc.SampleDesc.Count = 1;  // 关闭多重采样
		swap_chain_desc.SampleDesc.Quality = 0;
		swap_chain_desc.Windowed = (full_screen) ? false : true;
		swap_chain_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; // Set the scan line ordering and scaling to unspecified.
		swap_chain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // Discard the back buffer contents after presenting.
		swap_chain_desc.Flags = 0; // Don't set the advanced flags.

		// Set the feature level to DirectX 11.
		// 设置
		feature_level = D3D_FEATURE_LEVEL_11_0;

		// 一口气创建main swap chain，d3d device d3d device context
		result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &feature_level, 1, 
			D3D11_SDK_VERSION, &swap_chain_desc, &swap_chain_, &d3d_device_, NULL, &d3d_device_context_);

		if(FAILED(result))
		{
			return false;
		}

		// 获取到backbuffer的指针
		result = swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&back_buffer);
		if(FAILED(result))
		{
			return false;
		}

		// 通过backbuffer的指针创建到back buffer的render target.
		result = d3d_device_->CreateRenderTargetView(back_buffer, NULL, &back_buffer_view_);
		if(FAILED(result))
		{
			return false;
		}

		// 这个指针不用了要记得释放
		back_buffer->Release();
		back_buffer = 0;
// ----------------------
		// 填充深度缓冲区结构
		ZeroMemory(&depth_buffer_desc, sizeof(depth_buffer_desc));

		depth_buffer_desc.Width = screen_width;
		depth_buffer_desc.Height = screen_height;
		depth_buffer_desc.MipLevels = 1;
		depth_buffer_desc.ArraySize = 1;
		depth_buffer_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depth_buffer_desc.SampleDesc.Count = 1;
		depth_buffer_desc.SampleDesc.Quality = 0;
		depth_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
		depth_buffer_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL; // 指定所使用的buffer为深度和模板缓冲区
		depth_buffer_desc.CPUAccessFlags = 0;
		depth_buffer_desc.MiscFlags = 0;

		// 初始化深度和模板缓冲区view
		ZeroMemory(&depth_stencil_view_desc, sizeof(depth_stencil_view_desc));
		depth_stencil_view_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		depth_stencil_view_desc.Texture2D.MipSlice = 0;

		bool ret = depth_stencil_zone_.Create(&depth_buffer_desc,&depth_stencil_view_desc);

		if(!ret)
		{
			return false;
		}

		// 把作为backbuffer的render target view和depth_stenci view进行
		depth_stencil_zone_.AttachToRenderTarget( &back_buffer_view_,1);

// ----------------------
		// 初始化模板缓冲区渲染状态描述结构体
		ZeroMemory(&depth_stencil_desc, sizeof(depth_stencil_desc));
		depth_stencil_desc.DepthEnable = true;
		depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depth_stencil_desc.DepthFunc = D3D11_COMPARISON_LESS;		// 比较函数为“小于”
		depth_stencil_desc.StencilEnable = true;			
		depth_stencil_desc.StencilReadMask = 0xFF;
		depth_stencil_desc.StencilWriteMask = 0xFF;

		// 当像素是front-facing的时候执行的模板操作
		depth_stencil_desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depth_stencil_desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		depth_stencil_desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depth_stencil_desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		// 当像素是back-facing的时候执行的模板操作
		depth_stencil_desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depth_stencil_desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		depth_stencil_desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depth_stencil_desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		result = d3d_device_->CreateDepthStencilState(&depth_stencil_desc, &depth_stencil_state_);
		if(FAILED(result))
		{
			return false;
		}

		d3d_device_context_->OMSetDepthStencilState(depth_stencil_state_, 1);


// ----------------------

		// 描述光栅化状态
		rasterDesc.AntialiasedLineEnable = false;
		rasterDesc.CullMode = D3D11_CULL_BACK;
		rasterDesc.DepthBias = 0;
		rasterDesc.DepthBiasClamp = 0.0f;
		rasterDesc.DepthClipEnable = true;
		rasterDesc.FillMode = D3D11_FILL_SOLID;
		rasterDesc.FrontCounterClockwise = false;
		rasterDesc.MultisampleEnable = false;
		rasterDesc.ScissorEnable = false;
		rasterDesc.SlopeScaledDepthBias = 0.0f;

		// 创建光栅化状态对象
		result = d3d_device_->CreateRasterizerState(&rasterDesc, &rasterizer_state_);
		if(FAILED(result))
		{
			return false;
		}

		// 把刚才创建的状态对象设置
		d3d_device_context_->RSSetState(rasterizer_state_);

		// 创建并设置主视口
		viewport.Width = (float)screen_width;
		viewport.Height = (float)screen_height;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;

		d3d_device_context_->RSSetViewports(1, &viewport);

		//// Clear the second depth stencil state before setting the parameters.
		//ZeroMemory(&depth_disable_stencil_desc, sizeof(depth_disable_stencil_desc));

		//// Now create a second depth stencil state which turns off the Z buffer for 2D rendering.  The only difference is 
		//// that DepthEnable is set to false, all other parameters are the same as the other depth stencil state.
		//depth_disable_stencil_desc.DepthEnable = false;
		//depth_disable_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		//depth_disable_stencil_desc.DepthFunc = D3D11_COMPARISON_LESS;
		//depth_disable_stencil_desc.StencilEnable = true;
		//depth_disable_stencil_desc.StencilReadMask = 0xFF;
		//depth_disable_stencil_desc.StencilWriteMask = 0xFF;
		//depth_disable_stencil_desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		//depth_disable_stencil_desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		//depth_disable_stencil_desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		//depth_disable_stencil_desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		//depth_disable_stencil_desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		//depth_disable_stencil_desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		//depth_disable_stencil_desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		//depth_disable_stencil_desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		//// Create the state using the device.
		//result = d3d_device_->CreateDepthStencilState(&depth_disable_stencil_desc, &depth_disable_stencil_state_);
		//if(FAILED(result))
		//{
		//	return false;
		//}

		// 创建alpha blend状态对象，并且指定这个对象所作用的0号render target的相关混合操作属性
		ZeroMemory(&blend_state_desc, sizeof(D3D11_BLEND_DESC));
		blend_state_desc.RenderTarget[0].BlendEnable = TRUE;
		blend_state_desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blend_state_desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blend_state_desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blend_state_desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blend_state_desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blend_state_desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blend_state_desc.RenderTarget[0].RenderTargetWriteMask = 0x0f;

		result = d3d_device_->CreateBlendState(&blend_state_desc, &alpha_enable_blending_state_);

		if(FAILED(result))
		{
			return false;
		}

		// 创建一个关闭alpha blend的状态对象
		blend_state_desc.RenderTarget[0].BlendEnable = FALSE;
		result = d3d_device_->CreateBlendState(&blend_state_desc, &alpha_disable_blending_state_);

		if(FAILED(result))
		{
			return false;
		}

		return true;
	}