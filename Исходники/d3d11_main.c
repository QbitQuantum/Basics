HRESULT WINAPI D3D11CreateDevice(IDXGIAdapter *adapter, D3D_DRIVER_TYPE driver_type, HMODULE swrast, UINT flags,
        const D3D_FEATURE_LEVEL *feature_levels, UINT levels, UINT sdk_version, ID3D11Device **device_out,
        D3D_FEATURE_LEVEL *obtained_feature_level, ID3D11DeviceContext **immediate_context)
{
    IDXGIFactory *factory;
    ID3D11Device *device;
    HRESULT hr;

    TRACE("adapter %p, driver_type %s, swrast %p, flags %#x, feature_levels %p, levels %u, sdk_version %u, "
            "device %p, obtained_feature_level %p, immediate_context %p.\n",
            adapter, debug_d3d_driver_type(driver_type), swrast, flags, feature_levels, levels, sdk_version,
            device_out, obtained_feature_level, immediate_context);

    if (device_out)
        *device_out = NULL;
    if (obtained_feature_level)
        *obtained_feature_level = 0;
    if (immediate_context)
        *immediate_context = NULL;

    if (adapter)
    {
        IDXGIAdapter_AddRef(adapter);
        hr = IDXGIAdapter_GetParent(adapter, &IID_IDXGIFactory, (void **)&factory);
        if (FAILED(hr))
        {
            WARN("Failed to get dxgi factory, returning %#x.\n", hr);
            return hr;
        }
    }
    else
    {
        hr = CreateDXGIFactory(&IID_IDXGIFactory, (void **)&factory);
        if (FAILED(hr))
        {
            WARN("Failed to create dxgi factory, returning %#x.\n", hr);
            return hr;
        }

        switch(driver_type)
        {
            case D3D_DRIVER_TYPE_HARDWARE:
            {
                hr = IDXGIFactory_EnumAdapters(factory, 0, &adapter);
                if (FAILED(hr))
                {
                    WARN("No adapters found, returning %#x.\n", hr);
                    IDXGIFactory_Release(factory);
                    return hr;
                }
                break;
            }

            case D3D_DRIVER_TYPE_NULL:
                FIXME("NULL device not implemented, falling back to refrast.\n");
                /* fall through, for now */
            case D3D_DRIVER_TYPE_REFERENCE:
            {
                HMODULE refrast = LoadLibraryA("d3d11ref.dll");
                if (!refrast)
                {
                    WARN("Failed to load refrast, returning E_FAIL.\n");
                    IDXGIFactory_Release(factory);
                    return E_FAIL;
                }
                hr = IDXGIFactory_CreateSoftwareAdapter(factory, refrast, &adapter);
                FreeLibrary(refrast);
                if (FAILED(hr))
                {
                    WARN("Failed to create a software adapter, returning %#x.\n", hr);
                    IDXGIFactory_Release(factory);
                    return hr;
                }
                break;
            }

            case D3D_DRIVER_TYPE_SOFTWARE:
            {
                if (!swrast)
                {
                    WARN("Software device requested, but NULL swrast passed, returning E_FAIL.\n");
                    IDXGIFactory_Release(factory);
                    return E_FAIL;
                }
                hr = IDXGIFactory_CreateSoftwareAdapter(factory, swrast, &adapter);
                if (FAILED(hr))
                {
                    WARN("Failed to create a software adapter, returning %#x.\n", hr);
                    IDXGIFactory_Release(factory);
                    return hr;
                }
                break;
            }

            default:
                FIXME("Unhandled driver type %#x.\n", driver_type);
                IDXGIFactory_Release(factory);
                return E_FAIL;
        }
    }

    hr = D3D11CoreCreateDevice(factory, adapter, flags, feature_levels, levels, &device);
    IDXGIAdapter_Release(adapter);
    IDXGIFactory_Release(factory);
    if (FAILED(hr))
    {
        WARN("Failed to create a device, returning %#x.\n", hr);
        return hr;
    }

    TRACE("Created ID3D11Device %p.\n", device);

    if (obtained_feature_level)
        *obtained_feature_level = ID3D11Device_GetFeatureLevel(device);

    if (immediate_context)
        ID3D11Device_GetImmediateContext(device, immediate_context);

    if (device_out)
        *device_out = device;
    else
        ID3D11Device_Release(device);

    return S_OK;
}