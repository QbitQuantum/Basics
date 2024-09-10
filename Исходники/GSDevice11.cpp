bool GSDevice11::Create(GSWnd* wnd)
{
	if(!__super::Create(wnd))
	{
		return false;
	}

	HRESULT hr = E_FAIL;

	DXGI_SWAP_CHAIN_DESC scd;
	D3D11_BUFFER_DESC bd;
	D3D11_SAMPLER_DESC sd;
	D3D11_DEPTH_STENCIL_DESC dsd;
	D3D11_RASTERIZER_DESC rd;
	D3D11_BLEND_DESC bsd;

	CComPtr<IDXGIAdapter1> adapter;
	D3D_DRIVER_TYPE driver_type = D3D_DRIVER_TYPE_HARDWARE;

	std::string adapter_id = theApp.GetConfig("Adapter", "default");

	if (adapter_id == "default")
		;
	else if (adapter_id == "ref")
	{
		driver_type = D3D_DRIVER_TYPE_REFERENCE;
	}
	else
	{
		CComPtr<IDXGIFactory1> dxgi_factory;
		CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&dxgi_factory);
		if (dxgi_factory)
			for (int i = 0;; i++)
			{
				CComPtr<IDXGIAdapter1> enum_adapter;
				if (S_OK != dxgi_factory->EnumAdapters1(i, &enum_adapter))
					break;
				DXGI_ADAPTER_DESC1 desc;
				hr = enum_adapter->GetDesc1(&desc);
				if (S_OK == hr && GSAdapter(desc) == adapter_id)
				{
					adapter = enum_adapter;
					driver_type = D3D_DRIVER_TYPE_UNKNOWN;
					break;
				}
			}
	}

	memset(&scd, 0, sizeof(scd));

	scd.BufferCount = 2;
	scd.BufferDesc.Width = 1;
	scd.BufferDesc.Height = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//scd.BufferDesc.RefreshRate.Numerator = 60;
	//scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = (HWND)m_wnd->GetHandle();
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;

	// Always start in Windowed mode.  According to MS, DXGI just "prefers" this, and it's more or less
	// required if we want to add support for dual displays later on.  The fullscreen/exclusive flip
	// will be issued after all other initializations are complete.

	scd.Windowed = TRUE;

	spritehack = !!theApp.GetConfig("UserHacks", 0) ? theApp.GetConfig("UserHacks_SpriteHack", 0) : 0;
	// NOTE : D3D11_CREATE_DEVICE_SINGLETHREADED
	//   This flag is safe as long as the DXGI's internal message pump is disabled or is on the
	//   same thread as the GS window (which the emulator makes sure of, if it utilizes a
	//   multithreaded GS).  Setting the flag is a nice and easy 5% speedup on GS-intensive scenes.

	uint32 flags = D3D11_CREATE_DEVICE_SINGLETHREADED;

#ifdef DEBUG
	flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL level;

	const D3D_FEATURE_LEVEL levels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};

	hr = D3D11CreateDeviceAndSwapChain(adapter, driver_type, NULL, flags, levels, countof(levels), D3D11_SDK_VERSION, &scd, &m_swapchain, &m_dev, &level, &m_ctx);

	if(FAILED(hr)) return false;

	if(!SetFeatureLevel(level, true))
	{
		return false;
	}

	D3D11_FEATURE_DATA_D3D10_X_HARDWARE_OPTIONS options;

	hr = m_dev->CheckFeatureSupport(D3D11_FEATURE_D3D10_X_HARDWARE_OPTIONS, &options, sizeof(D3D11_FEATURE_D3D10_X_HARDWARE_OPTIONS));

	// msaa

	for(uint32 i = 2; i <= D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT; i++)
	{
		uint32 quality[2] = {0, 0};

		if(SUCCEEDED(m_dev->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, i, &quality[0])) && quality[0] > 0
		&& SUCCEEDED(m_dev->CheckMultisampleQualityLevels(DXGI_FORMAT_D32_FLOAT_S8X24_UINT, i, &quality[1])) && quality[1] > 0)
		{
			m_msaa_desc.Count = i;
			m_msaa_desc.Quality = std::min<uint32>(quality[0] - 1, quality[1] - 1);

			if(i >= m_msaa) break;
		}
	}

	if(m_msaa_desc.Count == 1)
	{
		m_msaa = 0;
	}

	// convert

	D3D11_INPUT_ELEMENT_DESC il_convert[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	vector<unsigned char> shader;
	theApp.LoadResource(IDR_CONVERT_FX, shader);
	CompileShader((const char *)shader.data(), shader.size(), "convert.fx", nullptr, "vs_main", nullptr, &m_convert.vs, il_convert, countof(il_convert), &m_convert.il);

	for(size_t i = 0; i < countof(m_convert.ps); i++)
	{
		CompileShader((const char *)shader.data(), shader.size(), "convert.fx", nullptr, format("ps_main%d", i).c_str(), nullptr, &m_convert.ps[i]);
	}

	memset(&dsd, 0, sizeof(dsd));

	dsd.DepthEnable = false;
	dsd.StencilEnable = false;

	hr = m_dev->CreateDepthStencilState(&dsd, &m_convert.dss);

	memset(&bsd, 0, sizeof(bsd));

	bsd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = m_dev->CreateBlendState(&bsd, &m_convert.bs);

	// merge

	memset(&bd, 0, sizeof(bd));

	bd.ByteWidth = sizeof(MergeConstantBuffer);
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	hr = m_dev->CreateBuffer(&bd, NULL, &m_merge.cb);

	theApp.LoadResource(IDR_MERGE_FX, shader);
	for(size_t i = 0; i < countof(m_merge.ps); i++)
	{
		CompileShader((const char *)shader.data(), shader.size(), "merge.fx", nullptr, format("ps_main%d", i).c_str(), nullptr, &m_merge.ps[i]);
	}

	memset(&bsd, 0, sizeof(bsd));

	bsd.RenderTarget[0].BlendEnable = true;
	bsd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bsd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bsd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bsd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bsd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bsd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bsd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = m_dev->CreateBlendState(&bsd, &m_merge.bs);

	// interlace

	memset(&bd, 0, sizeof(bd));

	bd.ByteWidth = sizeof(InterlaceConstantBuffer);
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	hr = m_dev->CreateBuffer(&bd, NULL, &m_interlace.cb);

	theApp.LoadResource(IDR_INTERLACE_FX, shader);
	for(size_t i = 0; i < countof(m_interlace.ps); i++)
	{
		CompileShader((const char *)shader.data(), shader.size(), "interlace.fx", nullptr, format("ps_main%d", i).c_str(), nullptr, &m_interlace.ps[i]);
	}

	// Shade Boost	

	int ShadeBoost_Contrast = theApp.GetConfig("ShadeBoost_Contrast", 50);
	int ShadeBoost_Brightness = theApp.GetConfig("ShadeBoost_Brightness", 50);
	int ShadeBoost_Saturation = theApp.GetConfig("ShadeBoost_Saturation", 50);
		
	string str[3];		
		
	str[0] = format("%d", ShadeBoost_Saturation);
	str[1] = format("%d", ShadeBoost_Brightness);
	str[2] = format("%d", ShadeBoost_Contrast);

	D3D_SHADER_MACRO macro[] =
	{			
		{"SB_SATURATION", str[0].c_str()},
		{"SB_BRIGHTNESS", str[1].c_str()},
		{"SB_CONTRAST", str[2].c_str()},
		{NULL, NULL},
	};

	memset(&bd, 0, sizeof(bd));

	bd.ByteWidth = sizeof(ShadeBoostConstantBuffer);
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	hr = m_dev->CreateBuffer(&bd, NULL, &m_shadeboost.cb);

	theApp.LoadResource(IDR_SHADEBOOST_FX, shader);
	CompileShader((const char *)shader.data(), shader.size(), "shadeboost.fx", nullptr, "ps_main", macro, &m_shadeboost.ps);

	// External fx shader

	memset(&bd, 0, sizeof(bd));

	bd.ByteWidth = sizeof(ExternalFXConstantBuffer);
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	hr = m_dev->CreateBuffer(&bd, NULL, &m_shaderfx.cb);

	// Fxaa

	memset(&bd, 0, sizeof(bd));

	bd.ByteWidth = sizeof(FXAAConstantBuffer);
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	hr = m_dev->CreateBuffer(&bd, NULL, &m_fxaa.cb);

	//

	memset(&rd, 0, sizeof(rd));

	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_NONE;
	rd.FrontCounterClockwise = false;
	rd.DepthBias = false;
	rd.DepthBiasClamp = 0;
	rd.SlopeScaledDepthBias = 0;
	rd.DepthClipEnable = false; // ???
	rd.ScissorEnable = true;
	rd.MultisampleEnable = true;
	rd.AntialiasedLineEnable = false;

	hr = m_dev->CreateRasterizerState(&rd, &m_rs);

	m_ctx->RSSetState(m_rs);

	//

	memset(&sd, 0, sizeof(sd));

	sd.Filter = theApp.GetConfig("MaxAnisotropy", 0) && !theApp.GetConfig("paltex", 0) ? D3D11_FILTER_ANISOTROPIC : D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sd.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.MinLOD = -FLT_MAX;
	sd.MaxLOD = FLT_MAX;
	sd.MaxAnisotropy = theApp.GetConfig("MaxAnisotropy", 0);
	sd.ComparisonFunc = D3D11_COMPARISON_NEVER;

	hr = m_dev->CreateSamplerState(&sd, &m_convert.ln);

	sd.Filter = theApp.GetConfig("MaxAnisotropy", 0) && !theApp.GetConfig("paltex", 0) ? D3D11_FILTER_ANISOTROPIC : D3D11_FILTER_MIN_MAG_MIP_POINT;

	hr = m_dev->CreateSamplerState(&sd, &m_convert.pt);

	//

	Reset(1, 1);

	//

	CreateTextureFX();

	//

	memset(&dsd, 0, sizeof(dsd));

	dsd.DepthEnable = false;
	dsd.StencilEnable = true;
	dsd.StencilReadMask = 1;
	dsd.StencilWriteMask = 1;
	dsd.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	dsd.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
	dsd.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsd.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	dsd.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	dsd.BackFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
	dsd.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsd.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;

	m_dev->CreateDepthStencilState(&dsd, &m_date.dss);

	D3D11_BLEND_DESC blend;

	memset(&blend, 0, sizeof(blend));

	m_dev->CreateBlendState(&blend, &m_date.bs);

	// Exclusive/Fullscreen flip, issued for legacy (managed) windows only.  GSopen2 style
	// emulators will issue the flip themselves later on.

	if(m_wnd->IsManaged())
	{
		SetExclusive(!theApp.GetConfig("windowed", 1));
	}

	return true;
}