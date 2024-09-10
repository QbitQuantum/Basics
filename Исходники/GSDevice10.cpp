bool GSDevice10::Create(HWND hWnd, bool vsync)
{
	if(!__super::Create(hWnd, vsync))
	{
		return false;
	}

	HRESULT hr;

	DXGI_SWAP_CHAIN_DESC scd;
	D3D10_BUFFER_DESC bd;
	D3D10_SAMPLER_DESC sd;
	D3D10_DEPTH_STENCIL_DESC dsd;
    D3D10_RASTERIZER_DESC rd;
	D3D10_BLEND_DESC bsd;

	memset(&scd, 0, sizeof(scd));

	scd.BufferCount = 2;
	scd.BufferDesc.Width = 1;
	scd.BufferDesc.Height = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//scd.BufferDesc.RefreshRate.Numerator = 60;
	//scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = hWnd;
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.Windowed = TRUE;

	UINT flags = 0;

#ifdef DEBUG
	flags |= D3D10_CREATE_DEVICE_DEBUG;
#endif

	hr = D3D10CreateDeviceAndSwapChain(NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, flags, D3D10_SDK_VERSION, &scd, &m_swapchain, &m_dev);

	if(FAILED(hr)) return false;

	// font
/*
	// TODO: the driver crashes on alt-enter when using a font...

	D3DX10_FONT_DESC fd;
	memset(&fd, 0, sizeof(fd));
	_tcscpy(fd.FaceName, _T("Arial"));
	fd.Height = 20;
	D3DX10CreateFontIndirect(m_dev, &fd, &m_font);
*/
	// convert

	D3D10_INPUT_ELEMENT_DESC il_convert[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 16, D3D10_INPUT_PER_VERTEX_DATA, 0},
	};

	hr = CompileShader(IDR_CONVERT10_FX, "vs_main", NULL, &m_convert.vs, il_convert, countof(il_convert), &m_convert.il);

	for(int i = 0; i < countof(m_convert.ps); i++)
	{
		CStringA main;
		main.Format("ps_main%d", i);
		hr = CompileShader(IDR_CONVERT10_FX, main, NULL, &m_convert.ps[i]);
	}

	memset(&bd, 0, sizeof(bd));

	bd.Usage = D3D10_USAGE_DEFAULT;
	bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.ByteWidth = 4 * sizeof(GSVertexPT1);

	hr = m_dev->CreateBuffer(&bd, NULL, &m_convert.vb);

	memset(&dsd, 0, sizeof(dsd));

	dsd.DepthEnable = false;
	dsd.StencilEnable = false;

	hr = m_dev->CreateDepthStencilState(&dsd, &m_convert.dss);

	memset(&bsd, 0, sizeof(bsd));

	bsd.BlendEnable[0] = false;
	bsd.RenderTargetWriteMask[0] = D3D10_COLOR_WRITE_ENABLE_ALL;

	hr = m_dev->CreateBlendState(&bsd, &m_convert.bs);

	// merge

	memset(&bd, 0, sizeof(bd));

    bd.ByteWidth = sizeof(MergeConstantBuffer);
    bd.Usage = D3D10_USAGE_DEFAULT;
    bd.BindFlags = D3D10_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;

    hr = m_dev->CreateBuffer(&bd, NULL, &m_merge.cb);

	for(int i = 0; i < countof(m_merge.ps); i++)
	{
		CStringA main;
		main.Format("ps_main%d", i);
		hr = CompileShader(IDR_MERGE10_FX, main, NULL, &m_merge.ps[i]);
	}

	memset(&bsd, 0, sizeof(bsd));

	bsd.BlendEnable[0] = true;
	bsd.BlendOp = D3D10_BLEND_OP_ADD;
	bsd.SrcBlend = D3D10_BLEND_SRC_ALPHA;
	bsd.DestBlend = D3D10_BLEND_INV_SRC_ALPHA;
	bsd.BlendOpAlpha = D3D10_BLEND_OP_ADD;
	bsd.SrcBlendAlpha = D3D10_BLEND_ONE;
	bsd.DestBlendAlpha = D3D10_BLEND_ZERO;
	bsd.RenderTargetWriteMask[0] = D3D10_COLOR_WRITE_ENABLE_ALL;

	hr = m_dev->CreateBlendState(&bsd, &m_merge.bs);

	// interlace

	memset(&bd, 0, sizeof(bd));

    bd.ByteWidth = sizeof(InterlaceConstantBuffer);
    bd.Usage = D3D10_USAGE_DEFAULT;
    bd.BindFlags = D3D10_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;

    hr = m_dev->CreateBuffer(&bd, NULL, &m_interlace.cb);

	for(int i = 0; i < countof(m_interlace.ps); i++)
	{
		CStringA main;
		main.Format("ps_main%d", i);
		hr = CompileShader(IDR_INTERLACE10_FX, main, NULL, &m_interlace.ps[i]);
	}

	//

	memset(&rd, 0, sizeof(rd));

	rd.FillMode = D3D10_FILL_SOLID;
	rd.CullMode = D3D10_CULL_NONE;
	rd.FrontCounterClockwise = false;
	rd.DepthBias = false;
	rd.DepthBiasClamp = 0;
	rd.SlopeScaledDepthBias = 0;
	rd.DepthClipEnable = false; // ???
	rd.ScissorEnable = true;
	rd.MultisampleEnable = false;
	rd.AntialiasedLineEnable = false;

	hr = m_dev->CreateRasterizerState(&rd, &m_rs);

	m_dev->RSSetState(m_rs);

	//

	memset(&sd, 0, sizeof(sd));

	sd.Filter = D3D10_FILTER_MIN_MAG_MIP_LINEAR;
	sd.AddressU = D3D10_TEXTURE_ADDRESS_CLAMP;
	sd.AddressV = D3D10_TEXTURE_ADDRESS_CLAMP;
	sd.AddressW = D3D10_TEXTURE_ADDRESS_CLAMP;
	sd.MaxLOD = FLT_MAX;
	sd.MaxAnisotropy = 16; 
	sd.ComparisonFunc = D3D10_COMPARISON_NEVER;

	hr = m_dev->CreateSamplerState(&sd, &m_convert.ln);

	sd.Filter = D3D10_FILTER_MIN_MAG_MIP_POINT;

	hr = m_dev->CreateSamplerState(&sd, &m_convert.pt);

	//

	Reset(1, 1, true);

	//
/*
	if(!m_mergefx.Create(this))
	{
		return false;
	}
*/
	//

	return true;
}