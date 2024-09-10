PRBool
nsGLPbufferWGL::Init(nsCanvasRenderingContextGLPrivate *priv)
{
    // XXX lookup SYSTEM32 path!
    char *opengl32 = "C:\\WINDOWS\\SYSTEM32\\OPENGL32.DLL";

    if (!gWGLWrap.OpenLibrary(opengl32))
        return PR_FALSE;

    gWGLWrap.SetLookupFunc((LibrarySymbolLoader::PlatformLookupFunction) wglGetProcAddress);

    mPriv = priv;
    
    WNDCLASS wc;
    PIXELFORMATDESCRIPTOR pfd;

    if (!GetClassInfo(GetModuleHandle(NULL), "GLEW", &wc)) {
        ZeroMemory(&wc, sizeof(WNDCLASS));
        wc.hInstance = GetModuleHandle(NULL);
        wc.lpfnWndProc = DefWindowProc;
        wc.lpszClassName = "GLEW";

        if (!RegisterClass(&wc)) {
            LogMessage(NS_LITERAL_CSTRING("Canvas 3D: RegisterClass failed"));
            return PR_FALSE;
        }
    }

    // create window
    mGlewWindow = CreateWindow("GLEW", "GLEW", 0, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
                               CW_USEDEFAULT, NULL, NULL, GetModuleHandle(NULL), NULL);
    if (!mGlewWindow) {
        LogMessage(NS_LITERAL_CSTRING("Canvas 3D: CreateWindow failed"));
        return PR_FALSE;
    }

    // get the device context
    mGlewDC = GetDC(mGlewWindow);
    if (!mGlewDC) {
        LogMessage(NS_LITERAL_CSTRING("Canvas 3D: GetDC failed"));
        return PR_FALSE;
    }

    // find default pixel format
    ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
    int pixelformat = ChoosePixelFormat(mGlewDC, &pfd);

    // set the pixel format for the dc
    if (!SetPixelFormat(mGlewDC, pixelformat, &pfd)) {
        LogMessage(NS_LITERAL_CSTRING("Canvas 3D: SetPixelFormat failed"));
        return PR_FALSE;
    }

    // create rendering context
    mGlewWglContext = wglCreateContext(mGlewDC);
    if (!mGlewWglContext) {
        LogMessage(NS_LITERAL_CSTRING("Canvas 3D: wglCreateContext failed"));
        return PR_FALSE;
    }

    if (!wglMakeCurrent(mGlewDC, (HGLRC) mGlewWglContext)) {
        LogMessage(NS_LITERAL_CSTRING("Canvas 3D: wglMakeCurrent failed"));
        return PR_FALSE;
    }

    // grab all the wgl extension pieces that we couldn't grab before
    // we had a context
    if (!gWGLWrap.Init())
        return PR_FALSE;

    // XXX look up system32 dir
    if (!mGLWrap.OpenLibrary(opengl32)) {
        LogMessage(NS_LITERAL_CSTRING("Canvas 3D: Failed to open opengl32.dll (only looked in c:\\windows\\system32, fixme)"));
        return PR_FALSE;
    }

    mGLWrap.SetLookupFunc((LibrarySymbolLoader::PlatformLookupFunction) wglGetProcAddress);

    if (!mGLWrap.Init(GLES20Wrap::TRY_NATIVE_GL)) {
        LogMessage(NS_LITERAL_CSTRING("Canvas 3D: GLWrap init failed"));
        return PR_FALSE;
    }

    return PR_TRUE;
}