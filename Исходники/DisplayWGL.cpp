egl::Error DisplayWGL::initializeD3DDevice()
{
    if (mD3D11Device != nullptr)
    {
        return egl::Error(EGL_SUCCESS);
    }

    mDxgiModule = LoadLibrary(TEXT("dxgi.dll"));
    if (!mDxgiModule)
    {
        return egl::Error(EGL_NOT_INITIALIZED, "Failed to load DXGI library.");
    }

    mD3d11Module = LoadLibrary(TEXT("d3d11.dll"));
    if (!mD3d11Module)
    {
        return egl::Error(EGL_NOT_INITIALIZED, "Failed to load d3d11 library.");
    }

    PFN_D3D11_CREATE_DEVICE d3d11CreateDevice = nullptr;
    d3d11CreateDevice = reinterpret_cast<PFN_D3D11_CREATE_DEVICE>(
                            GetProcAddress(mD3d11Module, "D3D11CreateDevice"));
    if (d3d11CreateDevice == nullptr)
    {
        return egl::Error(EGL_NOT_INITIALIZED, "Could not retrieve D3D11CreateDevice address.");
    }

    HRESULT result = d3d11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0,
                                       D3D11_SDK_VERSION, &mD3D11Device, nullptr, nullptr);
    if (FAILED(result))
    {
        return egl::Error(EGL_NOT_INITIALIZED, "Could not create D3D11 device, error: 0x%X",
                          result);
    }

    egl::Error error = registerD3DDevice(mD3D11Device, &mD3D11DeviceHandle);
    if (error.isError())
    {
        return error;
    }

    return egl::Error(EGL_SUCCESS);
}