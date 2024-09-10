	// Constructor. Creates a Direct3D device.
	D3D() : _Device(NULL), _ImmediateContext(NULL)
	{
		IDXGIFactory* factory;
		if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory))) return;
		
		HRESULT hr = S_OK;

		UINT createDeviceFlags = 0;
#ifdef _DEBUG
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		D3D_DRIVER_TYPE driverTypes[] =
		{
			D3D_DRIVER_TYPE_UNKNOWN,
		};
		UINT numDriverTypes = sizeof(driverTypes) / sizeof(driverTypes[0]);

		D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };
		unsigned int numFeatureLevels = 1;
		D3D_FEATURE_LEVEL usedFeatureLevel = D3D_FEATURE_LEVEL_11_0;

		// iterate the display adapters and look for a DirectX 11 capable device.
		for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
		{
			D3D_DRIVER_TYPE driverType = driverTypes[driverTypeIndex];

			IDXGIAdapter* adapter;
			for (UINT i = 0;
				factory->EnumAdapters(i, &adapter) != DXGI_ERROR_NOT_FOUND;
				++i)
			{
				DXGI_ADAPTER_DESC desc;
				adapter->GetDesc(&desc);

				std::wstring adapterDesc(desc.Description);
				hr = D3D11CreateDevice(adapter, driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels, D3D11_SDK_VERSION, &_Device, &usedFeatureLevel, &_ImmediateContext);
				if (SUCCEEDED(hr))
				{
					wprintf(L"D3D is using: %s\n", adapterDesc.c_str());
					break;
				}
			}

			if (!_Device) {
				printf("Couldn't create DirectX device.\nMaybe DirectX 11 is not supported on your machine?\n");
				exit(-1);
			}

			if (adapter) adapter->Release();

			if (SUCCEEDED(hr))
				break;
		}
		factory->Release();
	}