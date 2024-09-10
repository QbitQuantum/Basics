// Create DX11 device
ID3D11Device* spoutDirectX::CreateDX11device()
{
	ID3D11Device* pd3dDevice = NULL;
	HRESULT hr = S_OK;
	UINT createDeviceFlags = 0;

	// GL/DX interop Spec
	// ID3D11Device can only be used on WDDM operating systems : Must be multithreaded
	// D3D11_CREATE_DEVICE_FLAG createDeviceFlags
	// malcolm - derivative reported possible NVIDIA memory leak bug unless D3D11_CREATE_DEVICE_SINGLETHREADED is set
	// but the spec requires multithreaded
	D3D_DRIVER_TYPE driverTypes[] =	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};

	UINT numDriverTypes = ARRAYSIZE( driverTypes );

	D3D_FEATURE_LEVEL featureLevels[] =	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};

	UINT numFeatureLevels = ARRAYSIZE( featureLevels );

	for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ ) {
		g_driverType = driverTypes[driverTypeIndex];

		// Createdevice only method, not the full swap chain
		hr = D3D11CreateDevice(	NULL,
								g_driverType,
								NULL,
								createDeviceFlags,
								featureLevels,
								numFeatureLevels,
								D3D11_SDK_VERSION, 
								&pd3dDevice,
								&g_featureLevel,
								&g_pImmediateContext);
		
		// Break as soon as something passes
		if(SUCCEEDED(hr))
			break;

	}
	
	// Quit if nothing worked
	if( FAILED(hr))
		return NULL;

	// All OK
	return pd3dDevice;

} // end CreateDX11device