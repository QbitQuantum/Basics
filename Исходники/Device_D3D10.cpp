bool Device_D3D10::initD3D( void )
{
	HRESULT hr = S_OK;

	// `获得窗口大小`
	RECT rc;
	GetClientRect( m_hWnd, &rc );
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D10_CREATE_DEVICE_DEBUG;
#endif

	// `设置Frontbuffer/Backbuffer大小及格式`
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory( &sd, sizeof(sd) );
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = m_hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	//sd.SwapEffect = DXGI_SWAP_EFFECT_SEQUENTIAL;
	//sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	sd.Windowed = TRUE;

	// `打开Frontbuffer/Backbuffer`
	hr = D3D10CreateDeviceAndSwapChain( NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, D3D10_SDK_VERSION, &sd, &m_pSwapChain, &m_pd3dDevice );
	if( FAILED(hr) ) 
		return false;

	// `取出第一个display buffer`
	ID3D10Texture2D *pBuffer = NULL;
	hr = m_pSwapChain->GetBuffer( 0, __uuidof( ID3D10Texture2D ), (LPVOID*)&pBuffer );
	if( FAILED(hr) ) 
		return false;
	// `打开一个合乎display buffer格式的RenderTargetView`
	hr = m_pd3dDevice->CreateRenderTargetView( pBuffer, NULL, &m_pRenderTargetView );

	pBuffer->Release();
	if( FAILED( hr ) ) 
		return false;

	// `设置Depth/Stencil buffer的数据格式`
	D3D10_TEXTURE2D_DESC descDepth;
	descDepth.Width = width;
	descDepth.Height = height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D10_USAGE_DEFAULT;
	descDepth.BindFlags = D3D10_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	// `分配Depth/Stencil buffer的空间`
	hr = m_pd3dDevice->CreateTexture2D( &descDepth, NULL, &m_pDepthStencil );
	if( FAILED(hr) )
		return false;

	// `设置Depth/Stencil View的格式`
	D3D10_DEPTH_STENCIL_VIEW_DESC descDSV;
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	// `打开DepthStencil Buffer的View`
	hr = m_pd3dDevice->CreateDepthStencilView( m_pDepthStencil, &descDSV, &m_pDepthStencilView );
	if( FAILED(hr) )
		return false;

	setDefaultState();

	// `设置绘图的结果会存放在什么地方`
	// RenderTargetView = RGBA Color Buffer resource
	// DepthStencilView = Depth/Stencil Buffer resource
	m_pd3dDevice->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

	setDefaultState();

	// `Viewport用来指定3D绘图的画布范围, 在此把Viewport设置成和整个窗口一样大`
	D3D10_VIEWPORT vp;

	vp.Width = width;
	vp.Height = height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;

	m_pd3dDevice->RSSetViewports( 1, &vp );

	return true;
}