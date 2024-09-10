bool D3D11RHI::Init(WindowsWindow& window)
{
#ifdef _DEBUG
	const UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_SINGLETHREADED;
#else
	const UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_SINGLETHREADED;
#endif
	auto windowSize = window.GetWindowSize();

	DXGI_SWAP_CHAIN_DESC scd = {};
	scd.BufferDesc.Width = windowSize.x;
	scd.BufferDesc.Height = windowSize.y;
	scd.BufferDesc.RefreshRate.Numerator = 0;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_STRETCHED;
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
	scd.BufferCount = 2;
	scd.OutputWindow = window.GetWindowHandle();
	scd.Windowed = true;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	ComPtr<IDXGIDevice> dxgiDevice;
	ComPtr<IDXGIAdapter> dxgiAdapter;
	ComPtr<IDXGIFactory> dxgiFactory;

	try
	{
		//デバイスの作成
		Assert(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
			flags, nullptr, 0, D3D11_SDK_VERSION, m_device.GetAddressOf(), nullptr, m_immContext.GetAddressOf()),
			"Failed: D3D11CreateDevice from D3D11RHI::Init");

		//DXGIスワップチェインの作成
		Assert(m_device.As(&dxgiDevice), "Failed: As from D3D11RHI::Init");
		Assert(dxgiDevice->GetAdapter(&dxgiAdapter), "Failed: GetAdapter from D3D11RHI::Init");
		Assert(dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory)), "Failed: GetParent from D3D11RHI::Init");

		Assert(dxgiFactory->CreateSwapChain(m_device.Get(), &scd, m_swapChain.GetAddressOf()),
			"Failed: CreateSwapChain from D3D11RHI::Init");

		//スワップチェインからレンダーターゲットを作成
		Assert(m_swapChain->GetBuffer(0, IID_PPV_ARGS(m_defRenderTarget.RTTex.GetAddressOf())),
			"Failed: GetBuffer from D3D11RHI::Init");
		Assert(m_device->CreateRenderTargetView(m_defRenderTarget.RTTex.Get(),
			nullptr, m_defRenderTarget.RTView.GetAddressOf()),
			"Failed: CreateRenderTargetView from D3D11RHI::Init");
		Assert(m_device->CreateShaderResourceView(m_defRenderTarget.RTTex.Get(),
			nullptr, m_defRenderTarget.RTResource.GetAddressOf()),
			"Failed: CreateShaderResourceView from D3D11RHI::Init");

		//深度バッファの作成
		D3D11_TEXTURE2D_DESC dstd = {};
		dstd.Width = windowSize.x;
		dstd.Height = windowSize.y;
		dstd.MipLevels = 1;
		dstd.ArraySize = 1;
		dstd.Format = DXGI_FORMAT_R24G8_TYPELESS;
		dstd.SampleDesc = scd.SampleDesc;
		dstd.Usage = D3D11_USAGE_DEFAULT;
		dstd.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
		Assert(m_device->CreateTexture2D(
			&dstd, nullptr, m_defRenderTarget.DSTex.GetAddressOf()),
			"Failed: CreateTexture2D from D3D11RHI::Init");

		D3D11_DEPTH_STENCIL_VIEW_DESC dsvd = {};
		dsvd.Format = dstd.Format;
		dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsvd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		Assert(m_device->CreateDepthStencilView(
			m_defRenderTarget.DSTex.Get(),
			&dsvd, m_defRenderTarget.DSView.GetAddressOf()),
			"Failed: CreateDepthStenvilView from D3D11RHI::Init");

		D3D11_SHADER_RESOURCE_VIEW_DESC srvd = {};
		srvd.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvd.Texture2D.MipLevels = 1;
		Assert(m_device->CreateShaderResourceView(
			m_defRenderTarget.DSTex.Get(),
			&srvd, m_defRenderTarget.DSResource.GetAddressOf()),
			"Failed: CreateShaderResourceView from D3D11RHI::Init");


		//ビューポートの設定
		D3D11_VIEWPORT viewPort;
		viewPort.TopLeftX = 0.f;
		viewPort.TopLeftY = 0.f;
		viewPort.MinDepth = 0.0f;
		viewPort.MaxDepth = 1.0f;
		viewPort.Width = (float)windowSize.x;
		viewPort.Height = (float)windowSize.y;
		m_immContext->RSSetViewports(1, &viewPort);

		//ラスタライザステートの設定
		D3D11RasterStateRef rasterState;
		D3D11_RASTERIZER_DESC rastDesc = {};
		rastDesc.CullMode = D3D11_CULL_BACK;
		rastDesc.FillMode = D3D11_FILL_SOLID;
		rastDesc.DepthClipEnable = true;
		rastDesc.FrontCounterClockwise = false;
		Assert(m_device->CreateRasterizerState(&rastDesc, rasterState.GetAddressOf()),
			"Failed: CreateRasterizerState from D3D11RHI::Init");
		m_immContext->RSSetState(rasterState.Get());

		//深度ステンシルステートの設定
		D3D11_DEPTH_STENCIL_DESC dsDesc = {};
		dsDesc.DepthEnable = true;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
		Assert(m_device->CreateDepthStencilState(&dsDesc, m_dsStateDepthEnable.GetAddressOf()),
			"Failed: CreateDepthStencilState from D3D11RHI::Init");
		m_immContext->OMSetDepthStencilState(m_dsStateDepthEnable.Get(), 0);
		dsDesc.DepthEnable = false;
		Assert(m_device->CreateDepthStencilState(&dsDesc, m_dsStateDepthDisable.GetAddressOf()),
			"Failed: CreateDepthStencilState from D3D11RHI::Init");

#pragma region 関数ポインタの初期化
		m_fpSetShaderResources[ShaderType_Vertex] = &ID3D11DeviceContext::VSSetShaderResources;
		m_fpSetShaderResources[ShaderType_Pixel] = &ID3D11DeviceContext::PSSetShaderResources;
		m_fpSetShaderResources[ShaderType_Geometry] = &ID3D11DeviceContext::GSSetShaderResources;
		m_fpSetShaderResources[ShaderType_Hull] = &ID3D11DeviceContext::HSSetShaderResources;
		m_fpSetShaderResources[ShaderType_Domain] = &ID3D11DeviceContext::DSSetShaderResources;
		m_fpSetShaderResources[ShaderType_Compute] = &ID3D11DeviceContext::CSSetShaderResources;

		m_fpSetSampler[ShaderType_Vertex] = &ID3D11DeviceContext::VSSetSamplers;
		m_fpSetSampler[ShaderType_Pixel] = &ID3D11DeviceContext::PSSetSamplers;
		m_fpSetSampler[ShaderType_Geometry] = &ID3D11DeviceContext::GSSetSamplers;
		m_fpSetSampler[ShaderType_Hull] = &ID3D11DeviceContext::HSSetSamplers;
		m_fpSetSampler[ShaderType_Domain] = &ID3D11DeviceContext::DSSetSamplers;
		m_fpSetSampler[ShaderType_Compute] = &ID3D11DeviceContext::CSSetSamplers;

		m_fpSetConstantBuffers[ShaderType_Vertex] = &ID3D11DeviceContext::VSSetConstantBuffers;
		m_fpSetConstantBuffers[ShaderType_Pixel] = &ID3D11DeviceContext::PSSetConstantBuffers;
		m_fpSetConstantBuffers[ShaderType_Geometry] = &ID3D11DeviceContext::GSSetConstantBuffers;
		m_fpSetConstantBuffers[ShaderType_Hull] = &ID3D11DeviceContext::HSSetConstantBuffers;
		m_fpSetConstantBuffers[ShaderType_Domain] = &ID3D11DeviceContext::DSSetConstantBuffers;
		m_fpSetConstantBuffers[ShaderType_Compute] = &ID3D11DeviceContext::CSSetConstantBuffers;
#pragma endregion

		//フォントレンダラの初期化
		m_spriteBatch.reset(new SpriteBatch(m_immContext.Get()));
		
	}
	catch (char* str)
	{
		DebugOutputMessageBoxError(str);
		return false;
	}
	catch (...)
	{
		DebugOutputMessageBoxError("予期せぬエラー(Init)");
		return false;
	}
	return true;
}