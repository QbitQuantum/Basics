egl::Error WindowSurfaceWGL::initialize()
{
    mDeviceContext = GetDC(mWindow);
    if (!mDeviceContext)
    {
        return egl::Error(EGL_BAD_NATIVE_WINDOW, "Failed to get the device context from the native window, "
                                                 "error: 0x%X.", GetLastError());
    }

    // Require that the pixel format for this window has not been set yet or is equal to the Display's pixel format.
    int windowPixelFormat = GetPixelFormat(mDeviceContext);
    if (windowPixelFormat == 0)
    {
        PIXELFORMATDESCRIPTOR pixelFormatDescriptor = { 0 };
        if (!DescribePixelFormat(mDeviceContext, mPixelFormat, sizeof(pixelFormatDescriptor), &pixelFormatDescriptor))
        {
            return egl::Error(EGL_BAD_NATIVE_WINDOW, "Failed to DescribePixelFormat, error: 0x%X.", GetLastError());
        }

        if (!SetPixelFormat(mDeviceContext, mPixelFormat, &pixelFormatDescriptor))
        {
            return egl::Error(EGL_NOT_INITIALIZED, "Failed to set the pixel format on the device context, "
                                                   "error: 0x%X.", GetLastError());
        }
    }
    else if (windowPixelFormat != mPixelFormat)
    {
        return egl::Error(EGL_NOT_INITIALIZED, "Pixel format of the NativeWindow and NativeDisplayType must match.");
    }

    // Check for the swap behavior of this pixel format
    switch (
        wgl::QueryWGLFormatAttrib(mDeviceContext, mPixelFormat, WGL_SWAP_METHOD_ARB, mFunctionsWGL))
    {
        case WGL_SWAP_COPY_ARB:
            mSwapBehavior = EGL_BUFFER_PRESERVED;
            break;

        case WGL_SWAP_EXCHANGE_ARB:
        case WGL_SWAP_UNDEFINED_ARB:
        default:
            mSwapBehavior = EGL_BUFFER_DESTROYED;
            break;
    }

    return egl::Error(EGL_SUCCESS);
}