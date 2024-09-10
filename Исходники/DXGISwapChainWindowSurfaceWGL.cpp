static IDXGIFactory *GetDXGIFactoryFromDevice(ID3D11Device *device)
{
    IDXGIDevice *dxgiDevice = nullptr;
    HRESULT result =
        device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void **>(&dxgiDevice));
    if (FAILED(result))
    {
        return nullptr;
    }

    IDXGIAdapter *dxgiAdapter = nullptr;
    result = dxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void **>(&dxgiAdapter));
    SafeRelease(dxgiDevice);
    if (FAILED(result))
    {
        return nullptr;
    }

    IDXGIFactory *dxgiFactory = nullptr;
    result =
        dxgiAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void **>(&dxgiFactory));
    SafeRelease(dxgiAdapter);
    if (FAILED(result))
    {
        return nullptr;
    }

    return dxgiFactory;
}