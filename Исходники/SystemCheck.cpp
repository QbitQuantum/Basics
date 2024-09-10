    bool SystemCheck::CheckVRAMSize()
    {
        HRESULT hr;
        D3D_FEATURE_LEVEL FeatureLevel;

        CComPtr<IDXGIFactory1> DXGIFactory;

        hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&DXGIFactory);
        if(SUCCEEDED(hr))
        {
            CComPtr<IDXGIAdapter1> Adapter;

            hr = DXGIFactory->EnumAdapters1(0, &Adapter);
            if(SUCCEEDED(hr))
            {
                CComPtr<ID3D11Device> Device;
                CComPtr<ID3D11DeviceContext> DeviceContext;

                hr = D3D11CreateDevice(Adapter, D3D_DRIVER_TYPE_UNKNOWN, nullptr,
                    D3D11_CREATE_DEVICE_BGRA_SUPPORT, nullptr, 0, D3D11_SDK_VERSION,
                    &Device, &FeatureLevel, &DeviceContext);

                if(SUCCEEDED(hr))
                {
                    DXGI_ADAPTER_DESC adapterDesc;
                    Adapter->GetDesc(&adapterDesc);

                    std::wstring Description = adapterDesc.Description;
                    INT64 VideoRam = adapterDesc.DedicatedVideoMemory;
                    INT64 SystemRam = adapterDesc.DedicatedSystemMemory;
                    INT64 SharedRam = adapterDesc.SharedSystemMemory;

                    std::wcout << "***************** GRAPHICS ADAPTER DETAILS ***********************" << endl;;
                    std::wcout << "Adapter Description: " << Description << endl;
                    std::wcout << "Dedicated Video RAM: " << VideoRam << endl;
                    std::wcout << "Dedicated System RAM: " << SystemRam << endl;
                    std::wcout << "Shared System RAM: " << SharedRam << endl;
                    std::wcout << "PCI ID: " << Description << endl;
                    std::wcout << "Feature Level: " << FeatureLevel << endl;
                }
            }
        }    

        return true;
    }