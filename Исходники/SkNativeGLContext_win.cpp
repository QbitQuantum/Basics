const GrGLInterface* SkNativeGLContext::createGLContext() {
    HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(NULL);

    if (!gWC) {
        WNDCLASS wc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hbrBackground = NULL;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wc.hInstance = hInstance;
        wc.lpfnWndProc = (WNDPROC) DefWindowProc;
        wc.lpszClassName = TEXT("Griffin");
        wc.lpszMenuName = NULL;
        wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

        gWC = RegisterClass(&wc);
        if (!gWC) {
            SkDebugf("Could not register window class.\n");
            return NULL;
        }
    }

    if (!(fWindow = CreateWindow(TEXT("Griffin"),
                                 TEXT("The Invisible Man"),
                                 WS_OVERLAPPEDWINDOW,
                                 0, 0, 1, 1,
                                 NULL, NULL,
                                 hInstance, NULL))) {
        SkDebugf("Could not create window.\n");
        return NULL;
    }

    if (!(fDeviceContext = GetDC(fWindow))) {
        SkDebugf("Could not get device context.\n");
        this->destroyGLContext();
        return NULL;
    }
    
    PIXELFORMATDESCRIPTOR pfd;
    ZeroMemory(&pfd, sizeof(pfd));
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_SUPPORT_OPENGL;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 0;
    pfd.cStencilBits = 0;
    pfd.iLayerType = PFD_MAIN_PLANE;
    
    int pixelFormat = 0;
    if (!(pixelFormat = ChoosePixelFormat(fDeviceContext, &pfd))) {
        SkDebugf("No matching pixel format descriptor.\n");
        this->destroyGLContext();
        return NULL;
    }
    
    if (!SetPixelFormat(fDeviceContext, pixelFormat, &pfd)) {
        SkDebugf("Could not set the pixel format %d.\n", pixelFormat);
        this->destroyGLContext();
        return NULL;
    }
    
    if (!(fGlRenderContext = wglCreateContext(fDeviceContext))) {
        SkDebugf("Could not create rendering context.\n");
        this->destroyGLContext();
        return NULL;
    }

    if (!(wglMakeCurrent(fDeviceContext, fGlRenderContext))) {
        SkDebugf("Could not set the context.\n");
        this->destroyGLContext();
        return NULL;
    }
    const GrGLInterface* interface = GrGLCreateNativeInterface();
    if (NULL == interface) {
        SkDebugf("Could not create GL interface.\n");
        this->destroyGLContext();
        return NULL;
    }

    return interface;
}