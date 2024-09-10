IUnknown* DX11Engine::createNativeDevice() const {
    ID3D11Device* pDeivce = nullptr;
    unsigned int flag = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
    flag |= D3D11_CREATE_DEVICE_DEBUG;
#endif
    D3D_FEATURE_LEVEL levels[] = { D3D_FEATURE_LEVEL_11_0 };
    D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
                      flag, levels, _countof(levels), D3D11_SDK_VERSION, &pDeivce, nullptr, nullptr);
        
    return pDeivce;
}