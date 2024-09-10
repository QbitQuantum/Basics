HRESULT DeviceResources::Initialize()
{
	HRESULT hr;

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};

	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	this->_d3dDriverType = D3D_DRIVER_TYPE_HARDWARE;

	hr = D3D11CreateDevice(nullptr, this->_d3dDriverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels, D3D11_SDK_VERSION, &this->_d3dDevice, &this->_d3dFeatureLevel, &this->_d3dDeviceContext);

	if (FAILED(hr))
	{
		this->_d3dDriverType = D3D_DRIVER_TYPE_WARP;

		hr = D3D11CreateDevice(nullptr, this->_d3dDriverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels, D3D11_SDK_VERSION, &this->_d3dDevice, &this->_d3dFeatureLevel, &this->_d3dDeviceContext);
	}

	this->CheckMultisamplingSupport();

	if (SUCCEEDED(hr))
	{
		hr = this->LoadMainResources();
	}

	if (SUCCEEDED(hr))
	{
		hr = this->LoadResources();
	}

	if (FAILED(hr))
	{
		static bool messageShown = false;

		if (!messageShown)
		{
			MessageBox(nullptr, _com_error(hr).ErrorMessage(), __FUNCTION__, MB_ICONERROR);
		}

		messageShown = true;
	}

	return hr;
}