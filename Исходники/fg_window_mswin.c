GLboolean fgSetupPixelFormat( SFG_Window* window, GLboolean checkOnly,
                              unsigned char layer_type )
{
#if defined(_WIN32_WCE)
    return GL_TRUE;
#else
    PIXELFORMATDESCRIPTOR pfd;
    PIXELFORMATDESCRIPTOR* ppfd = &pfd;
    int pixelformat;
    HDC current_hDC;
    GLboolean success;

    if (checkOnly)
      current_hDC = CreateDC(TEXT("DISPLAY"), NULL ,NULL ,NULL);
    else
      current_hDC = window->Window.pContext.Device;

    fghFillPFD( ppfd, current_hDC, layer_type );
    pixelformat = ChoosePixelFormat( current_hDC, ppfd );

    /* windows hack for multismapling/sRGB */
    if ( ( fgState.DisplayMode & GLUT_MULTISAMPLE ) ||
         ( fgState.DisplayMode & GLUT_SRGB ) )
    {        
        HGLRC rc, rc_before=wglGetCurrentContext();
        HWND hWnd;
        HDC hDC, hDC_before=wglGetCurrentDC();
        WNDCLASS wndCls;

        /* create a dummy window */
        ZeroMemory(&wndCls, sizeof(wndCls));
        wndCls.lpfnWndProc = DefWindowProc;
        wndCls.hInstance = fgDisplay.pDisplay.Instance;
        wndCls.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
        wndCls.lpszClassName = _T("FREEGLUT_dummy");
        RegisterClass( &wndCls );

        hWnd=CreateWindow(_T("FREEGLUT_dummy"), _T(""), WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW , 0,0,0,0, 0, 0, fgDisplay.pDisplay.Instance, 0 );
        hDC=GetDC(hWnd);
        SetPixelFormat( hDC, pixelformat, ppfd );

        rc = wglCreateContext( hDC );
        wglMakeCurrent(hDC, rc);

        if ( fghIsExtensionSupported( hDC, "WGL_ARB_multisample" ) )
        {
            PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARBProc =
              (PFNWGLCHOOSEPIXELFORMATARBPROC) wglGetProcAddress("wglChoosePixelFormatARB");
            if ( wglChoosePixelFormatARBProc )
            {
                int attributes[100];
                int iPixelFormat;
                BOOL bValid;
                float fAttributes[] = { 0, 0 };
                UINT numFormats;
                fghFillPixelFormatAttributes( attributes, ppfd );
                bValid = wglChoosePixelFormatARBProc(hDC, attributes, fAttributes, 1, &iPixelFormat, &numFormats);

                if ( bValid && numFormats > 0 )
                {
                    pixelformat = iPixelFormat;
                }
            }
        }

        wglMakeCurrent( hDC_before, rc_before);
        wglDeleteContext(rc);
        ReleaseDC(hWnd, hDC);
        DestroyWindow(hWnd);
        UnregisterClass(_T("FREEGLUT_dummy"), fgDisplay.pDisplay.Instance);
    }

    success = ( pixelformat != 0 ) && ( checkOnly || SetPixelFormat( current_hDC, pixelformat, ppfd ) );

    if (checkOnly)
        DeleteDC(current_hDC);

    return success;
#endif /* defined(_WIN32_WCE) */
}