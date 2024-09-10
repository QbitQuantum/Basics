bool RenderContextWGL::Create(void* osWnd) {
    window = static_cast<HWND>(osWnd);

    int glmajor = 3;
    int glminor = 3;
    int colorBits = 32;
    int depthBits = 24;
    int stencilBits = 0;
    int samples = 0;

    
    InitGLEW();

    int attrs[] = {
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
        WGL_SAMPLE_BUFFERS_ARB, samples > 0 ? GL_TRUE : GL_FALSE,
        WGL_SAMPLES_ARB, samples,
        WGL_COLOR_BITS_ARB, colorBits,
        WGL_DEPTH_BITS_ARB, depthBits,
        WGL_STENCIL_BITS_ARB, stencilBits,
        WGL_ALPHA_BITS_ARB, colorBits == 32 ? 8 : 0,
        0
    };

    int pixelFormat;
    unsigned numFormats = 0;
    gdiDc = GetDC(window);

    int result = wglChoosePixelFormatARB(gdiDc, attrs, nullptr, 1, &pixelFormat, &numFormats);
    if (result == 0 || numFormats == 0) {
        Log::E("wglChoosePixelFormatARB failed");
    }
         
    // info
    PIXELFORMATDESCRIPTOR pfd;
    DescribePixelFormat(gdiDc, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
    Log::V() << "Pixel format:\tcColorBits " << (int)pfd.cColorBits << ", cDepthBits " << (int)pfd.cDepthBits
             << "\n\t\t\tcAlphaBits " << (int)pfd.cAlphaBits << ", cStencilBits " << (int)pfd.cStencilBits;

    if (!SetPixelFormat(gdiDc, pixelFormat, &pfd)) {
        Log::E("SetPixelFormat");
    }

    int contextAttrs[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, glmajor,   //  OpenGL 3.3 provides full compatibility with OpenGL ES 3.0.
        WGL_CONTEXT_MINOR_VERSION_ARB, glminor,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,  // WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB
     // WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,   // WGL_CONTEXT_DEBUG_BIT_ARB
     // WGL_CONTEXT_LAYER_PLANE_ARB, 0,
        0
    };

    wglContext = wglCreateContextAttribsARB(gdiDc, 0, contextAttrs);
    if (!wglContext) {
        Log::E("wglContext");
    }

    if (!wglMakeCurrent(gdiDc, wglContext)) {
        Log::E("wglMakeCurrent");
        wglDeleteContext(wglContext);
        ReleaseDC(window, gdiDc);
        wglContext = nullptr;
        return false;
    }

    RECT rect;
    GetClientRect(window, &rect);
    mWidth = rect.right - rect.left;
    mHeight = rect.bottom - rect.top;

    return true;
}