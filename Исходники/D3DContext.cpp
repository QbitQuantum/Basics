bool D3DContext::CreateDeviceAndSwapChain(Description description)
{
    unsigned int deviceFlags = 0;
#ifdef DEBUG_MODE
    deviceFlags |= D3D10_CREATE_DEVICE_DEBUG;
#endif

    // Create the swap chain description
    description.BackBuffer.Width = (description.BackBuffer.Width == 0) ? mTargetWindow->GetClientWidth() : description.BackBuffer.Width;
    description.BackBuffer.Height = (description.BackBuffer.Height == 0) ? mTargetWindow->GetClientHeight() : description.BackBuffer.Height;

    DXGI_SWAP_CHAIN_DESC scDescription;
    ZeroMemory(&scDescription, sizeof(scDescription));
    scDescription.BufferCount = 1;
    scDescription.BufferDesc.Width = description.BackBuffer.Width;
    scDescription.BufferDesc.Height = description.BackBuffer.Height;
    scDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scDescription.BufferDesc.RefreshRate.Numerator = 60;
    scDescription.BufferDesc.RefreshRate.Denominator = 1;
    scDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scDescription.OutputWindow = mTargetWindow->GetHandle();
    scDescription.SampleDesc.Count = 1;
    scDescription.SampleDesc.Quality = 0;
    scDescription.Windowed = !description.Fullscreen;

    // Create the device and the swap chain
    // Try different drivers for Direct3D, hardware first, reference only if that fails.
    D3D10_DRIVER_TYPE driverTypes[] = { D3D10_DRIVER_TYPE_HARDWARE, D3D10_DRIVER_TYPE_REFERENCE };
    unsigned int driverTypeCount = sizeof(driverTypes) / sizeof(driverTypes[0]);

    HRESULT result = S_OK;
    for (unsigned int i = 0; i < driverTypeCount; ++i)
    {
        result = D3D10CreateDeviceAndSwapChain(NULL,
                                               driverTypes[i],
                                               NULL,
                                               deviceFlags,
                                               D3D10_SDK_VERSION,
                                               &scDescription,
                                               &mSwapChain,
                                               &mDevice);

        if (SUCCEEDED(result))
            break;
    }

    if (FAILED(result))
        return false;

    mBackBufferSize.Width = description.BackBuffer.Width;
    mBackBufferSize.Height = description.BackBuffer.Height;

    return true;
}