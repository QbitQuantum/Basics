	RenderingSystem::RenderingSystem(Window* Window) : m_Running(true), m_Window(Window)
	{
		HRESULT hr = 0;

		DXGI_SWAP_CHAIN_DESC SwapChainDesc;
		ZeroMemory(&SwapChainDesc, sizeof(SwapChainDesc));

		SwapChainDesc.BufferCount = 1;

		//Set the width and Height of the back buffer
		SwapChainDesc.BufferDesc.Width = m_Window->getWidth();
		SwapChainDesc.BufferDesc.Height = m_Window->getHeight();

		//Set the surface to be 32 bit
		SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		//Set the refresh rate to be 60 frames per second
		SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

		//Set the output Window
		SwapChainDesc.OutputWindow = m_Window->getWindowHandle();

		//No multisampling at the moment
		SwapChainDesc.SampleDesc.Count = 1;
		SwapChainDesc.SampleDesc.Quality = 0;

		//Windowed mode
		SwapChainDesc.Windowed = TRUE;

		hr = D3D10CreateDeviceAndSwapChain(NULL, //Use the default Adapter
			D3D10_DRIVER_TYPE_HARDWARE, 
			NULL, //Not using DLL for rendering
			D3D10_CREATE_DEVICE_DEBUG, //Allow debug output
			D3D10_SDK_VERSION, //use the current SDK
			&SwapChainDesc,
			&m_SwapChain,
			&m_Device);
	}