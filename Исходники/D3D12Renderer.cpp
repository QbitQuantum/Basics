//--------------------------------------------------------------------------
void D3D12Renderer::Init()
{
	m_spD3D12 = VE_NEW VeSharedLib(LIB_D3D12);
	if (!m_spD3D12->Load())
	{
		THROW("Failed to load " LIB_D3D12 ".");
	}
	m_spDXGI = VE_NEW VeSharedLib(LIB_DXGI);
	if (!m_spDXGI->Load())
	{
		THROW("Failed to load " LIB_DXGI ".");
	}
	m_spD3DCompiler = VE_NEW VeSharedLib(LIB_D3DCOMPLIER);
	if (!m_spD3DCompiler->Load())
	{
		THROW("Failed to load " LIB_D3DCOMPLIER ".");
	}

	D3D12GetDebugInterface = (decltype(D3D12GetDebugInterface))
		m_spD3D12->GetProc("D3D12GetDebugInterface");
	if (!D3D12GetDebugInterface)
	{
		THROW("Failed to fetch function D3D12GetDebugInterface.");
	}

	D3D12CreateDevice = (decltype(D3D12CreateDevice))
		m_spD3D12->GetProc("D3D12CreateDevice");
	if (!D3D12CreateDevice)
	{
		THROW("Failed to fetch function D3D12CreateDevice.");
	}

	D3D12SerializeRootSignature = (decltype(D3D12SerializeRootSignature))
		m_spD3D12->GetProc("D3D12SerializeRootSignature");
	if (!D3D12SerializeRootSignature)
	{
		THROW("Failed to fetch function D3D12SerializeRootSignature.");
	}

	CreateDXGIFactory1 = (decltype(CreateDXGIFactory1))
		m_spDXGI->GetProc("CreateDXGIFactory1");
	if (!CreateDXGIFactory1)
	{
		THROW("Failed to fetch function CreateDXGIFactory1.");
	}

	D3DCompile = (decltype(D3DCompile))
		m_spD3DCompiler->GetProc("D3DCompile");
	if (!D3DCompile)
	{
		THROW("Failed to fetch function D3DCompile.");
	}

#	ifdef VE_DEBUG
	{
		ID3D12Debug* pkDebugController(nullptr);
		if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&pkDebugController))))
		{
			pkDebugController->EnableDebugLayer();
		}
		VE_SAFE_RELEASE(pkDebugController);
	}
#	endif

	if (VE_FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&m_pkDXGIFactory))))
	{
		THROW("Failed to create DXGI factory.");
	}

	if (m_pkDXGIFactory->EnumAdapters1(0, &m_pkDefaultAdapter) == DXGI_ERROR_NOT_FOUND)
	{
		THROW("Failed to get main adapter.");
	}

	if (VE_FAILED(D3D12CreateDevice(m_pkDefaultAdapter,
		D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_pkDevice))))
	{
		THROW("Failed to create d3d12 device.");
	}

	m_kRTVHeap.Init(m_pkDevice);
	m_kDSVHeap.Init(m_pkDevice);
	m_kSRVHeap.Init(m_pkDevice);

	VeCoreLogI("D3D12Renderer created successfully.");
}