bool cInitDirect3D::Init()
{

	UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevel;
	HRESULT hr = D3D11CreateDevice(
		0,					// default adapter 사용할 IDXGIAdapter 인터페이스
		md3dDriverType,		//DirectX11 디바이스타입.
		0,					// no software device 보통 null
		createDeviceFlags,	//디바이스 플래그
		0, 0,				//  피처레벨을 사용할 배열, 피처레벨 수
		D3D11_SDK_VERSION,	//SDK버전
		&m_pD3dDevice,		//넘겨받을 디바이스 인터페이스
		&featureLevel,		//피처레벨을 얻어낼 포인터
		&m_pDeviceContext);	//넘겨받을 디바이스 컨텍스트 인터페이스

	if (FAILED(hr))
	{
		MessageBox(0, L"D3D11CreateDevice Failed.", 0, 0);
		return false;
	}

	if (featureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		MessageBox(0, L"Direct3D Feature Level 11 unsupported.", 0, 0);
		return false;
	}

	// Check 4X MSAA quality support for our back buffer format.
	// All Direct3D 11 capable devices support 4X MSAA for all render 
	// target formats, so we only need to check quality support.

	HR(m_pD3dDevice->CheckMultisampleQualityLevels(
		DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m4xMsaaQuality));
	assert(m4xMsaaQuality > 0);

	// DXGI_SWAP_CHAIN_DESC구조체를 채운다.
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));//구조체 초기화
	sd.BufferCount = 1;//백버퍼 개수
	sd.BufferDesc.Width = ClientWidth;//백버퍼 가로
	sd.BufferDesc.Height = ClientHeight;//백버퍼 세로
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//백버퍼 포맷 : RGBA8비트이며 값의 범위0.0~1.0
	sd.BufferDesc.RefreshRate.Numerator = 60;//화면 갱신율. 분자.
	sd.BufferDesc.RefreshRate.Denominator = 1;//화면 갱신율. 분모.(60/1)
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;//백버퍼의 용도
	sd.OutputWindow = g_hWnd;//버퍼를 출력할 윈도우
	sd.SampleDesc.Count = 1;//멀티 샘플링 수
	sd.SampleDesc.Quality = 0;//멀티 샘플링 퀄리티
	sd.Windowed = true;//윈도우모드
	sd.Flags = 0;
	// Use 4X MSAA? 
	if (mEnable4xMsaa)
	{
		sd.SampleDesc.Count = 4;
		sd.SampleDesc.Quality = m4xMsaaQuality - 1;
	}
	// No MSAA
	else
	{
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
	}


	// To correctly create the swap chain, we must use the IDXGIFactory that was
	// used to create the device.  If we tried to use a different IDXGIFactory instance
	// (by calling CreateDXGIFactory), we get an error: "IDXGIFactory::CreateSwapChain: 
	// This function is being called with a device from a different IDXGIFactory."

	IDXGIDevice* dxgiDevice = 0;
	HR(m_pD3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice));

	IDXGIAdapter* dxgiAdapter = 0;
	HR(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter));

	IDXGIFactory* dxgiFactory = 0;
	HR(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory));

	HR(dxgiFactory->CreateSwapChain(m_pD3dDevice, &sd, &m_pSwapChain));

	ReleaseCOM(dxgiDevice);
	ReleaseCOM(dxgiAdapter);
	ReleaseCOM(dxgiFactory);


	// The remaining steps that need to be carried out for d3d creation
	// also need to be executed every time the window is resized.  So
	// just call the OnResize method here to avoid code duplication.
	Onresize();
	return true;
}