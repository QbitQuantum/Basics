HRESULT WINAPI D3DX10CreateDevice(IDXGIAdapter *adapter, D3D10_DRIVER_TYPE driver_type,
        HMODULE swrast, unsigned int flags, ID3D10Device **device)
{
    HRESULT hr;

    TRACE("adapter %p, driver_type %d, swrast %p, flags %#x, device %p.\n", adapter, driver_type,
            swrast, flags, device);

    if (SUCCEEDED(hr = D3D10CreateDevice1(adapter, driver_type, swrast, flags, D3D10_FEATURE_LEVEL_10_1,
            D3D10_SDK_VERSION, (ID3D10Device1 **)device)))
        return hr;

    if (SUCCEEDED(hr = D3D10CreateDevice1(adapter, driver_type, swrast, flags, D3D10_FEATURE_LEVEL_10_0,
            D3D10_SDK_VERSION, (ID3D10Device1 **)device)))
        return hr;

    return hr;
}