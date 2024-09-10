void DebugAnnotator11::initializeDevice()
{
    if (!mInitialized)
    {
#if !defined(ANGLE_ENABLE_WINDOWS_STORE)
        mD3d11Module = LoadLibrary(TEXT("d3d11.dll"));
        ASSERT(mD3d11Module);

        PFN_D3D11_CREATE_DEVICE D3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE)GetProcAddress(mD3d11Module, "D3D11CreateDevice");
        ASSERT(D3D11CreateDevice != nullptr);
#endif // !ANGLE_ENABLE_WINDOWS_STORE

        ID3D11Device *device = nullptr;
        ID3D11DeviceContext *context = nullptr;

        HRESULT hr = E_FAIL;

        // Create a D3D_DRIVER_TYPE_NULL device, which is much cheaper than other types of device.
        hr = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_NULL, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &device, nullptr, &context);
        ASSERT(SUCCEEDED(hr));
        if (SUCCEEDED(hr))
        {
            mUserDefinedAnnotation = d3d11::DynamicCastComObject<ID3DUserDefinedAnnotation>(context);
            ASSERT(mUserDefinedAnnotation != nullptr);
            mInitialized = true;
        }

        SafeRelease(device);
        SafeRelease(context);
    }
}