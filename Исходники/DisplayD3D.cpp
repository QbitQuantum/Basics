egl::Error DisplayD3D::initialize(egl::Display *display)
{
    ASSERT(mRenderer == nullptr && display != nullptr);
    mDisplay = display;
    egl::Error error = CreateRendererD3D(display, &mRenderer);
    if (error.isError())
    {
        return error;
    }

    ASSERT(mDevice == nullptr);
    mDevice = new DeviceD3D(mRenderer);

#if !defined(ANGLE_ENABLE_WINDOWS_STORE)
    // Work around compile error from not defining "UNICODE" while Chromium does
    const LPSTR idcArrow = MAKEINTRESOURCEA(32512);

    std::string className = FormatString("ANGLE DisplayD3D 0x%0.8p Child Window Class", mDisplay);

    WNDCLASSA childWindowClassDesc = { 0 };
    childWindowClassDesc.style = CS_OWNDC;
    childWindowClassDesc.lpfnWndProc = IntermediateWindowProc;
    childWindowClassDesc.cbClsExtra = 0;
    childWindowClassDesc.cbWndExtra = 0;
    childWindowClassDesc.hInstance = GetModuleHandle(nullptr);
    childWindowClassDesc.hIcon = nullptr;
    childWindowClassDesc.hCursor = LoadCursorA(nullptr, idcArrow);
    childWindowClassDesc.hbrBackground = 0;
    childWindowClassDesc.lpszMenuName = nullptr;
    childWindowClassDesc.lpszClassName = className.c_str();

    mChildWindowClass = RegisterClassA(&childWindowClassDesc);
    if (!mChildWindowClass)
    {
        return egl::Error(EGL_NOT_INITIALIZED, "Failed to register child window class.");
    }
#endif

    return egl::Error(EGL_SUCCESS);
}