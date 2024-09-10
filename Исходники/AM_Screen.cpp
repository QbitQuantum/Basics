bool Screen::createSCandDevice()
{
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = rndrWindow;
	swapChainDesc.SampleDesc.Count = settings.getNumSamples();
	swapChainDesc.SampleDesc.Quality = settings.getNumSamples()-1;
	swapChainDesc.Windowed = TRUE;
	HRESULT hr = D3D10CreateDeviceAndSwapChain(NULL,
		D3D10_DRIVER_TYPE_HARDWARE, NULL, D3D10_CREATE_DEVICE_PREVENT_INTERNAL_THREADING_OPTIMIZATIONS | D3D10_CREATE_DEVICE_SINGLETHREADED||D3D10_CREATE_DEVICE_DEBUG,
		D3D10_SDK_VERSION, &swapChainDesc,
		&swapChain, &d3ddev);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Error initializing Direct3D\n\n*This is usually caused by the configuration being unsupported by your graphics card, or your graphics card not supporting DirectX 10.\n\n*Try lowering and/or disabling some settings in the software config.\n\n*This may also have been caused by outdated graphics card drivers. Please make sure your graphics drivers are up to date.\n\n*If you are running a system with Nvidia Optimus, please make sure the software is running on the dedicated GPU.\n\n*Unfortunately, if your graphics card does not support DirectX 10, the only fix for this would be to use one that does.", "Fatal Error", MB_OK);
		return false;
	}
	return true;
}