static qboolean VID_CreateWindow( int width, int height, qboolean fullscreen )
{
    RECT			r;
    int				stylebits;
    int				x, y, w, h, exstyle;

    /* Register the frame class */
    if (!s_classRegistered)
    {
        WNDCLASS wc;

        memset( &wc, 0, sizeof( wc ) );
        wc.style         = 0;
        wc.lpfnWndProc   = (WNDPROC)glw_state.wndproc;
        wc.cbClsExtra    = 0;
        wc.cbWndExtra    = 0;
        wc.hInstance     = glw_state.hInstance;
        wc.hIcon         = LoadIcon(glw_state.hInstance, MAKEINTRESOURCE(IDI_ICON1));
        wc.hCursor       = LoadCursor (NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
        wc.lpszMenuName  = 0;
        wc.lpszClassName = WINDOW_CLASS_NAME;

        if (!RegisterClass(&wc)) {
            PrintWinError("VID_CreateWindow: RegisterClass", true);
            return false;
        }

        s_classRegistered = true;
    }

    if (fullscreen) {
        exstyle = WS_EX_TOPMOST;
        stylebits = WS_POPUP|WS_VISIBLE;

        w = width;
        h = height;
        x = 0;
        y = 0;
    }
    else {
        exstyle = 0;
        stylebits = WINDOW_STYLE;

        r.left = 0;
        r.top = 0;
        r.right  = width;
        r.bottom = height;

        AdjustWindowRect (&r, stylebits, FALSE);

        w = r.right - r.left;
        h = r.bottom - r.top;
        x = vid_xpos->integer;
        y = vid_ypos->integer;
    }

    glw_state.hWnd = CreateWindowEx (
                         exstyle,
                         WINDOW_CLASS_NAME,
                         APPLICATION,
                         stylebits,
                         x, y, w, h,
                         NULL,
                         NULL,
                         glw_state.hInstance,
                         NULL);

    if (!glw_state.hWnd) {
        PrintWinError("VID_CreateWindow: CreateWindowEx", true);
        return false;
    }

    ShowWindow( glw_state.hWnd, SW_SHOW );
    UpdateWindow( glw_state.hWnd );

    // init all the gl stuff for the window
    if (!GLimp_InitGL())
    {
        Com_Printf ( "VID_CreateWindow() - GLimp_InitGL failed\n");

        if (glw_state.hGLRC) {
            qwglDeleteContext( glw_state.hGLRC );
            glw_state.hGLRC = NULL;
        }
        if (glw_state.hDC) {
            ReleaseDC( glw_state.hWnd, glw_state.hDC );
            glw_state.hDC = NULL;
        }

        ShowWindow( glw_state.hWnd, SW_HIDE );
        DestroyWindow( glw_state.hWnd );
        glw_state.hWnd = NULL;
        return false;
    }

    SetForegroundWindow( glw_state.hWnd );
    SetFocus( glw_state.hWnd );

    vid_scaled_width = (int)ceilf((float)width / gl_scale->value);
    vid_scaled_height = (int)ceilf((float)height / gl_scale->value);

    //round to powers of 8/2 to avoid blackbars
    width = (vid_scaled_width+7)&~7;
    height = (vid_scaled_height+1)&~1;

    // let the sound and input subsystems know about the new window
    VID_NewWindow( width, height );
    //VID_NewWindow( width / gl_scale->value, height / gl_scale->value);

    return true;
}