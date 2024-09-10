bool D3D11Context::Init(HINSTANCE hInst, HWND wnd, std::string *error_message) {
	hWnd_ = wnd;
	LoadD3D11Error result = LoadD3D11();

	HRESULT hr = E_FAIL;
	std::vector<std::string> adapterNames;
	std::string chosenAdapterName;
	if (result == LoadD3D11Error::SUCCESS) {
		std::vector<IDXGIAdapter *> adapters;
		int chosenAdapter = 0;

		IDXGIFactory * pFactory = nullptr;
		ptr_CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pFactory);

		IDXGIAdapter *pAdapter;
		for (UINT i = 0; pFactory->EnumAdapters(i, &pAdapter) != DXGI_ERROR_NOT_FOUND; i++) {
			adapters.push_back(pAdapter);
			DXGI_ADAPTER_DESC desc;
			pAdapter->GetDesc(&desc);
			std::string str = ConvertWStringToUTF8(desc.Description);
			adapterNames.push_back(str);
			if (str == g_Config.sD3D11Device) {
				chosenAdapter = i;
			}
		}

		chosenAdapterName = adapterNames[chosenAdapter];
		hr = CreateTheDevice(adapters[chosenAdapter]);
		for (int i = 0; i < (int)adapters.size(); i++) {
			adapters[i]->Release();
		}
	}

	if (FAILED(hr)) {
		const char *defaultError = "Your GPU does not appear to support Direct3D 11.\n\nWould you like to try again using Direct3D 9 instead?";
		I18NCategory *err = GetI18NCategory("Error");

		std::wstring error;

		if (result == LoadD3D11Error::FAIL_NO_COMPILER) {
			error = ConvertUTF8ToWString(err->T("D3D11CompilerMissing", "D3DCompiler_47.dll not found. Please install. Or press Yes to try again using Direct3D9 instead."));
		} else if (result == LoadD3D11Error::FAIL_NO_D3D11) {
			error = ConvertUTF8ToWString(err->T("D3D11Missing", "Your operating system version does not include D3D11. Please run Windows Update.\n\nPress Yes to try again using Direct3D9 instead."));
		}

		error = ConvertUTF8ToWString(err->T("D3D11NotSupported", defaultError));
		std::wstring title = ConvertUTF8ToWString(err->T("D3D11InitializationError", "Direct3D 11 initialization error"));
		bool yes = IDYES == MessageBox(hWnd_, error.c_str(), title.c_str(), MB_ICONERROR | MB_YESNO);
		if (yes) {
			// Change the config to D3D9 and restart.
			g_Config.iGPUBackend = (int)GPUBackend::DIRECT3D9;
			g_Config.sFailedGPUBackends.clear();
			g_Config.Save("save_d3d9_fallback");

			W32Util::ExitAndRestart();
		}
		return false;
	}

	if (FAILED(device_->QueryInterface(__uuidof (ID3D11Device1), (void **)&device1_))) {
		device1_ = nullptr;
	}

	if (FAILED(context_->QueryInterface(__uuidof (ID3D11DeviceContext1), (void **)&context1_))) {
		context1_ = nullptr;
	}

#ifdef _DEBUG
	if (SUCCEEDED(device_->QueryInterface(__uuidof(ID3D11Debug), (void**)&d3dDebug_))) {
		if (SUCCEEDED(d3dDebug_->QueryInterface(__uuidof(ID3D11InfoQueue), (void**)&d3dInfoQueue_))) {
			d3dInfoQueue_->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
			d3dInfoQueue_->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
			d3dInfoQueue_->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_WARNING, true);
		}
	}
#endif

	draw_ = Draw::T3DCreateD3D11Context(device_, context_, device1_, context1_, featureLevel_, hWnd_, adapterNames);
	SetGPUBackend(GPUBackend::DIRECT3D11, chosenAdapterName);
	bool success = draw_->CreatePresets();  // If we can run D3D11, there's a compiler installed. I think.
	_assert_msg_(G3D, success, "Failed to compile preset shaders");

	int width;
	int height;
	GetRes(hWnd_, width, height);

	// Obtain DXGI factory from device (since we used nullptr for pAdapter above)
	IDXGIFactory1* dxgiFactory = nullptr;
	IDXGIDevice* dxgiDevice = nullptr;
	IDXGIAdapter* adapter = nullptr;
	hr = device_->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
	if (SUCCEEDED(hr)) {
		hr = dxgiDevice->GetAdapter(&adapter);
		if (SUCCEEDED(hr)) {
			hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory));
			DXGI_ADAPTER_DESC desc;
			adapter->GetDesc(&desc);
			adapter->Release();
		}
		dxgiDevice->Release();
	}

	// DirectX 11.0 systems
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWnd_;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	hr = dxgiFactory->CreateSwapChain(device_, &sd, &swapChain_);
	dxgiFactory->MakeWindowAssociation(hWnd_, DXGI_MWA_NO_ALT_ENTER);
	dxgiFactory->Release();

	GotBackbuffer();
	return true;
}