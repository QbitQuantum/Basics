HRESULT WINAPI D3D10CreateDeviceAndSwapChain1(IDXGIAdapter *adapter, D3D10_DRIVER_TYPE driver_type,
        HMODULE swrast, UINT flags, D3D10_FEATURE_LEVEL1 feature_level, UINT sdk_version,
        DXGI_SWAP_CHAIN_DESC *swapchain_desc, IDXGISwapChain **swapchain, ID3D10Device1 **device)
{
    IDXGIDevice *dxgi_device;
    IDXGIFactory *factory;
    HRESULT hr;

    TRACE("adapter %p, driver_type %s, swrast %p, flags %#x, "
            "feature_level %s, sdk_version %d, swapchain_desc %p, swapchain %p, device %p.\n",
            adapter, debug_d3d10_driver_type(driver_type), swrast, flags,
            debug_d3d10_feature_level(feature_level), sdk_version, swapchain_desc, swapchain, device);

    if (swapchain)
        *swapchain = NULL;

    if (!device)
        return E_INVALIDARG;

    if (FAILED(hr = D3D10CreateDevice1(adapter, driver_type, swrast, flags, feature_level, sdk_version, device)))
    {
        WARN("Failed to create a device, returning %#x.\n", hr);
        *device = NULL;
        return hr;
    }

    if (swapchain)
    {
        if (FAILED(hr = ID3D10Device1_QueryInterface(*device, &IID_IDXGIDevice, (void **)&dxgi_device)))
        {
            ERR("Failed to get a dxgi device from the d3d10 device, returning %#x.\n", hr);
            goto cleanup;
        }

        hr = IDXGIDevice_GetAdapter(dxgi_device, &adapter);
        IDXGIDevice_Release(dxgi_device);
        if (FAILED(hr))
        {
            ERR("Failed to get the device adapter, returning %#x.\n", hr);
            goto cleanup;
        }

        hr = IDXGIAdapter_GetParent(adapter, &IID_IDXGIFactory, (void **)&factory);
        IDXGIAdapter_Release(adapter);
        if (FAILED(hr))
        {
            ERR("Failed to get the adapter factory, returning %#x.\n", hr);
            goto cleanup;
        }

        hr = IDXGIFactory_CreateSwapChain(factory, (IUnknown *)*device, swapchain_desc, swapchain);
        IDXGIFactory_Release(factory);
        if (FAILED(hr))
        {
            WARN("Failed to create a swapchain, returning %#x.\n", hr);
            goto cleanup;
        }

        TRACE("Created IDXGISwapChain %p.\n", *swapchain);
    }

    return S_OK;

cleanup:
    ID3D10Device1_Release(*device);
    *device = NULL;
    return hr;
}