SkWGLExtensions::SkWGLExtensions()
    : fGetExtensionsString(nullptr)
    , fChoosePixelFormat(nullptr)
    , fGetPixelFormatAttribfv(nullptr)
    , fGetPixelFormatAttribiv(nullptr)
    , fCreateContextAttribs(nullptr)
    , fSwapInterval(nullptr)
    , fCreatePbuffer(nullptr)
    , fGetPbufferDC(nullptr)
    , fReleasePbufferDC(nullptr)
    , fDestroyPbuffer(nullptr)
 {
    HDC prevDC = wglGetCurrentDC();
    HGLRC prevGLRC = wglGetCurrentContext();

    PIXELFORMATDESCRIPTOR dummyPFD;

    ZeroMemory(&dummyPFD, sizeof(dummyPFD));
    dummyPFD.nSize = sizeof(dummyPFD);
    dummyPFD.nVersion = 1;
    dummyPFD.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
    dummyPFD.iPixelType = PFD_TYPE_RGBA;
    dummyPFD.cColorBits  = 32;
    dummyPFD.cDepthBits  = 0;
    dummyPFD.cStencilBits = 8;
    dummyPFD.iLayerType = PFD_MAIN_PLANE;
    HWND dummyWND = create_dummy_window();
    if (dummyWND) {
        HDC dummyDC = GetDC(dummyWND);
        int dummyFormat = ChoosePixelFormat(dummyDC, &dummyPFD);
        SetPixelFormat(dummyDC, dummyFormat, &dummyPFD);
        HGLRC dummyGLRC = wglCreateContext(dummyDC);
        SkASSERT(dummyGLRC);
        wglMakeCurrent(dummyDC, dummyGLRC);

        GET_PROC(GetExtensionsString, ARB);
        GET_PROC(ChoosePixelFormat, ARB);
        GET_PROC(GetPixelFormatAttribiv, ARB);
        GET_PROC(GetPixelFormatAttribfv, ARB);
        GET_PROC(CreateContextAttribs, ARB);
        GET_PROC(SwapInterval, EXT);
        GET_PROC(CreatePbuffer, ARB);
        GET_PROC(GetPbufferDC, ARB);
        GET_PROC(ReleasePbufferDC, ARB);
        GET_PROC(DestroyPbuffer, ARB);

        wglMakeCurrent(dummyDC, nullptr);
        wglDeleteContext(dummyGLRC);
        destroy_dummy_window(dummyWND);
    }

    wglMakeCurrent(prevDC, prevGLRC);
}