void Direct3D11::create_device()
{
	D3D_FEATURE_LEVEL feature_levels[] = {
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};

	D3D_FEATURE_LEVEL feature_level = feature_levels[ 0 ];

#ifdef _DEBUG
    UINT d3d11_create_device_flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUG;
#else
    UINT d3d11_create_device_flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#endif

	DIRECT_X_FAIL_CHECK( D3D11CreateDevice( dxgi_adapter_.get(), D3D_DRIVER_TYPE_UNKNOWN, 0, d3d11_create_device_flags, feature_levels, ARRAYSIZE( feature_levels ), D3D11_SDK_VERSION, & device_, & feature_level, & immediate_context_ ) );
}