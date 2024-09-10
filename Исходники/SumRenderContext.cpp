//*************************************************************************************************
// Create the device
//*************************************************************************************************
SBOOL RenderContext::createDevice()
{
	// Create the device and device context
	UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
	//createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	HRESULT hr = S_OK;

	// Set the desired feature level
	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL targetLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};
	SUINT numFeatureLevels = 1;

	// Create a device factory so that we can find a DX11 compatible device
	IDXGIFactory* factory = 0;
	IDXGIAdapter* adapter = 0;
	hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&factory));
	if(FAILED(hr))
	{
		MessageBox(0, "Failed to create IDXGIFactory.", 0, 0);
		return false;
	}

	// Get selected device if it is part of the config
	Configuration* config = ConfigurationManager::getSingletonPtr()->getConfiguration("Engine");
	String configAdapter = config->retrieveValue("adapter");

	// Iterate through adapters to find a compatible one
	DXGI_ADAPTER_DESC adapterDesc;
	for(SINT i = 0; factory->EnumAdapters(i, &adapter) != DXGI_ERROR_NOT_FOUND; ++i)
	{
		// Get the adapter description
		adapter->GetDesc(&adapterDesc);

		// See whether this adapter matches the one we selected
		if(configAdapter == adapterDesc.Description)
		{
			// Use this adapter
			break;
		}
		
	}

	if(adapter)
	{
		// Create the device using the specified adapter
		_d3dDriverType = D3D_DRIVER_TYPE_UNKNOWN;
		hr = D3D11CreateDevice(
			adapter,	// Selected adapter
			_d3dDriverType,
			0,
			createDeviceFlags,	// Support debug mode
			targetLevels,		// Target feature levels
			numFeatureLevels,	// Number of supported feature levels
			D3D11_SDK_VERSION,
			&_d3dDevice,
			&featureLevel,
			&_d3dImmediateContext
			);
	}
	else
	{
		_d3dDriverType = D3D_DRIVER_TYPE_HARDWARE;
		hr = D3D11CreateDevice(
			0,
			_d3dDriverType,
			0,
			createDeviceFlags,
			targetLevels,
			numFeatureLevels,
			D3D11_SDK_VERSION,
			&_d3dDevice,
			&featureLevel,
			&_d3dImmediateContext
			);
	}
	if(FAILED(hr))
	{
		MessageBox(0, "D3DCreateDevice Failed", 0, 0);
		return false;
	}

	// Check for DX11 support
	if(featureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		MessageBox(0, "DirectX 11 is not supported on this device", 0, 0);
		return false;
	}

	// Creation of device succeeded
	return true;
}