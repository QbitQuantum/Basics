void DesktopDuplication::init()
{
	IDXGIFactory1* dxgiFactory = nullptr;
	CHECKED(hr, CreateDXGIFactory1(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory)));

	IDXGIAdapter1* dxgiAdapter = nullptr;
	CHECKED(hr, dxgiFactory->EnumAdapters1(adapter, &dxgiAdapter));
	dxgiFactory->Release();

	CHECKED(hr, D3D11CreateDevice(dxgiAdapter,
		D3D_DRIVER_TYPE_UNKNOWN,
		NULL,
		NULL,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&d3dDevice,
		NULL,
		&d3dContext));

	IDXGIOutput* dxgiOutput = nullptr;
	CHECKED(hr, dxgiAdapter->EnumOutputs(output, &dxgiOutput));
	dxgiAdapter->Release();

	IDXGIOutput1* dxgiOutput1 = nullptr;
	CHECKED(hr, dxgiOutput->QueryInterface(__uuidof(dxgiOutput1), reinterpret_cast<void**>(&dxgiOutput1)));
	dxgiOutput->Release();

	IDXGIDevice* dxgiDevice = nullptr;
	CHECKED(hr, d3dDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice)));

	CHECKED(hr, dxgiOutput1->DuplicateOutput(dxgiDevice, &outputDuplication));
	dxgiOutput1->Release();
	dxgiDevice->Release();
}