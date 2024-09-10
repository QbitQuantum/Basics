GLboolean glewCreateContext (struct createParams* params)
{
    WNDCLASS wc;
    PIXELFORMATDESCRIPTOR pfd;
    /* register window class */
    ZeroMemory(&wc, sizeof(WNDCLASS));
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpfnWndProc = DefWindowProc;
    wc.lpszClassName = "GLEW";
    if (0 == RegisterClass(&wc)) return GL_TRUE;
    /* create window */
    wnd = CreateWindow("GLEW", "GLEW", 0, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                       CW_USEDEFAULT, NULL, NULL, GetModuleHandle(NULL), NULL);
    if (NULL == wnd) return GL_TRUE;
    /* get the device context */
    dc = GetDC(wnd);
    if (NULL == dc) return GL_TRUE;
    /* find pixel format */
    ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
    if (params->pixelformat == -1) /* find default */
    {
        pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
        pfd.nVersion = 1;
        pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
        params->pixelformat = ChoosePixelFormat(dc, &pfd);
        if (params->pixelformat == 0) return GL_TRUE;
    }
    /* set the pixel format for the dc */
    if (FALSE == SetPixelFormat(dc, params->pixelformat, &pfd)) return GL_TRUE;
    /* create rendering context */
    rc = wglCreateContext(dc);
    if (NULL == rc) return GL_TRUE;
    if (FALSE == wglMakeCurrent(dc, rc)) return GL_TRUE;
    if (params->major || params->profile || params->flags)
    {
        HGLRC oldRC = rc;
        int contextAttrs[20];
        int i;

        wglewInit();

        /* Intel HD 3000 has WGL_ARB_create_context, but not WGL_ARB_create_context_profile */
        if (!wglewGetExtension("WGL_ARB_create_context"))
            return GL_TRUE;

        i = 0;
        if (params->major)
        {
            contextAttrs[i++] = WGL_CONTEXT_MAJOR_VERSION_ARB;
            contextAttrs[i++] = params->major;
            contextAttrs[i++] = WGL_CONTEXT_MINOR_VERSION_ARB;
            contextAttrs[i++] = params->minor;
        }
        if (params->profile)
        {
            contextAttrs[i++] = WGL_CONTEXT_PROFILE_MASK_ARB;
            contextAttrs[i++] = params->profile;
        }
        if (params->flags)
        {
            contextAttrs[i++] = WGL_CONTEXT_FLAGS_ARB;
            contextAttrs[i++] = params->flags;
        }
        contextAttrs[i++] = 0;
        rc = wglCreateContextAttribsARB(dc, 0, contextAttrs);

        if (NULL == rc) return GL_TRUE;
        if (!wglMakeCurrent(dc, rc)) return GL_TRUE;

        wglDeleteContext(oldRC);
    }
    return GL_FALSE;
}