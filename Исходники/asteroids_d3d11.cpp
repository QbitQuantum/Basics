inline void DisableDXGIWindowChanges(IUnknown* device, HWND window)
{
    IDXGIDevice * pDXGIDevice;
    ThrowIfFailed(device->QueryInterface(IID_PPV_ARGS(&pDXGIDevice)));
    IDXGIAdapter * pDXGIAdapter;
    ThrowIfFailed(pDXGIDevice->GetParent(IID_PPV_ARGS(&pDXGIAdapter)));
    IDXGIFactory * pIDXGIFactory;
    ThrowIfFailed(pDXGIAdapter->GetParent(IID_PPV_ARGS(&pIDXGIFactory)));

    ThrowIfFailed(pIDXGIFactory->MakeWindowAssociation(window, DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER));

    pIDXGIFactory->Release();
    pDXGIAdapter->Release();
    pDXGIDevice->Release();
}