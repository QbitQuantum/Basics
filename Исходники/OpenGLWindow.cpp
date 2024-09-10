const char* SingleOpenGLWindowImplT::Open(const std::string& Title_, unsigned int Width_, unsigned int Height_, char BPP_, bool FullScreen_)
{
#ifdef _WIN32
    if (WindowIsOpen) return "OpenGLWindow is already open.";

    hInstance=GetModuleHandle(NULL);   // 'GetModuleHandle(NULL)' entspricht 'hInstance' von 'WinMain()'.
    hWindow  =NULL;
    hDC      =NULL;
    hRC      =NULL;

    Title      =Title_;
    Width      =Width_;
    Height     =Height_;
    BPP        =BPP_;
    FullScreen =FullScreen_;
    IsMinimized=false;

    for (unsigned int c=0; c<256; c++) KeyboardState[c]=false;


    // 1. Window-Klasse ausfüllen und registrieren
    // *******************************************

    WNDCLASSEX MainWindowClass;

    MainWindowClass.cbSize       =sizeof(WNDCLASSEX);                       // Größe dieser Struktur
    MainWindowClass.style        =CS_VREDRAW | CS_HREDRAW | CS_OWNDC;       // Fensterklassenstil
    MainWindowClass.lpfnWndProc  =WinProc;                                  // Zeiger auf Handler-Funktion
    MainWindowClass.cbClsExtra   =0;                                        // Zusätzlicher Platz für KlassenInfos
    MainWindowClass.cbWndExtra   =0;                                        // Zusätzlicher Platz für FensterInfos
    MainWindowClass.hInstance    =hInstance;                                // Unsere Programm-ID
    MainWindowClass.hIcon        =LoadIcon(NULL, IDI_APPLICATION);          // Icon
    MainWindowClass.hIconSm      =LoadIcon(NULL, IDI_APPLICATION);          // Kleines Icon für Task-Bar
    MainWindowClass.hCursor      =LoadCursor(NULL, IDC_ARROW);              // Cursor
    MainWindowClass.hbrBackground=NULL;                                     // Hintergrund-Brush
    MainWindowClass.lpszMenuName =NULL;                                     // Menü
    MainWindowClass.lpszClassName="CafuMain";                               // Name dieser Fensterklasse

    if (!RegisterClassEx(&MainWindowClass)) return "Unable to register the window class.";


    // 2. Display Settings ggf. anpassen
    // *********************************

    if (FullScreen)
    {
        DEVMODE dmScreenSettings;

        memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
        dmScreenSettings.dmSize      =sizeof(dmScreenSettings);
        dmScreenSettings.dmPelsWidth =Width;
        dmScreenSettings.dmPelsHeight=Height;
        dmScreenSettings.dmBitsPerPel=BPP;
        dmScreenSettings.dmFields    =DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

        // CDS_FULLSCREEN gets rid of start bar.
        if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
        {
            UnregisterClass("CafuMain", hInstance);
            return "Unable to change display settings.";
        }

        ShowCursor(false);
    }


    // 3. Window-Rectangle anpassen
    // ****************************

    unsigned int Style=FullScreen ? WS_POPUP : WS_OVERLAPPEDWINDOW;
    unsigned int ExStyle=WS_EX_APPWINDOW;

    RECT GLWindowRect;

    GLWindowRect.top   =0;
    GLWindowRect.left  =0;
    GLWindowRect.right =Width;
    GLWindowRect.bottom=Height;

    if (!AdjustWindowRectEx(&GLWindowRect, Style, false, ExStyle))
    {
        Close();
        return "Unable to adjust window rectangle.";
    }


    // 4. Window erzeugen
    // ******************

    hWindow=CreateWindowEx(ExStyle,                                    // Fensterstil (erweitert)
                           "CafuMain",                                 // Name der Fensterklasse
                           Title.c_str(),                              // Fenstertitel
                           Style | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,  // Fensterstil
                           0, // FullScreen ? 0 : CW_USEDEFAULT,       // X-Position
                           0, // FullScreen ? 0 : CW_USEDEFAULT,       // Y-Position
                           GLWindowRect.right-GLWindowRect.left,       // Breite
                           GLWindowRect.bottom-GLWindowRect.top,       // Höhe
                           NULL,                                       // Übergeordnetes Fenster
                           NULL,                                       // Menü
                           hInstance,                                  // Unsere Programm-ID
                           NULL);                                      // Zusätzliche Parameter

    if (!hWindow)
    {
        Close();
        return "Unable to create window.";
    }


    // 5. Device Context erfragen
    // **************************

    hDC=GetDC(hWindow);

    if (!hDC)
    {
        Close();
        return "Unable to obtain a GL device context.";
    }


    // 6. PixelFormat abfragen und setzen
    // **********************************

    PIXELFORMATDESCRIPTOR PFD;

    memset(&PFD, 0, sizeof(PFD));
    PFD.nSize       =sizeof(PFD);
    PFD.nVersion    =1;
    PFD.dwFlags     =PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    PFD.iPixelType  =PFD_TYPE_RGBA;
    PFD.cColorBits  =BPP;
    PFD.cDepthBits  =32;
    PFD.cStencilBits=8;
    PFD.iLayerType=PFD_MAIN_PLANE;

    int PixelFormat=ChoosePixelFormat(hDC, &PFD);

    if (!PixelFormat)
    {
        Close();
        return "Unable to choose a pixel format.";
    }

    if (!DescribePixelFormat(hDC, PixelFormat, sizeof(PFD), &PFD))
    {
        Close();
        return "Unable to verify pixel format.";
    }

    static char ErrorMsg[1024];
    const char* s1="Selected pixel format mismatches:\n";
    const char* s2="\n\nThis is probably a problem with your video card (or its driver).\n"
                   "Please make sure you have the latest drivers installed.\n"
                   "If it still doesn't work, please let me know.\n"
                   "(Email to [email protected], and please include the above message!)";

    if ((PFD.dwFlags & PFD_DRAW_TO_WINDOW)!=PFD_DRAW_TO_WINDOW) { Close(); sprintf(ErrorMsg, "%sPFD_DRAW_TO_WINDOW is not supported.                 %s", s1,                   s2); return ErrorMsg; }
    if ((PFD.dwFlags & PFD_SUPPORT_OPENGL)!=PFD_SUPPORT_OPENGL) { Close(); sprintf(ErrorMsg, "%sOpenGL is not supported.                             %s", s1,                   s2); return ErrorMsg; }
    if ((PFD.dwFlags & PFD_DOUBLEBUFFER  )!=PFD_DOUBLEBUFFER  ) { Close(); sprintf(ErrorMsg, "%sDouble-buffering is not supported.                   %s", s1,                   s2); return ErrorMsg; }
    if (PFD.iPixelType!=PFD_TYPE_RGBA                         ) { Close(); sprintf(ErrorMsg, "%sPixel type RGBA is not supported.                    %s", s1,                   s2); return ErrorMsg; }
 // if (PFD.cColorBits<BPP                                    ) { Close(); sprintf(ErrorMsg, "%sOnly %u color bits found (at least 15 are required). %s", s1, PFD.cColorBits  , s2); return ErrorMsg; }
    if (PFD.cDepthBits<16                                     ) { Close(); sprintf(ErrorMsg, "%sOnly %u depth bits found (at least 16 are required). %s", s1, PFD.cDepthBits  , s2); return ErrorMsg; }
    if (PFD.cStencilBits<8                                    ) { Close(); sprintf(ErrorMsg, "%sOnly %u stencil bits found (at least 8 are required).%s", s1, PFD.cStencilBits, s2); return ErrorMsg; }
    if (PFD.iLayerType!=PFD_MAIN_PLANE                        ) { Close(); sprintf(ErrorMsg, "%sLayer type PFD_MAIN_PLANE is not supported.          %s", s1,                   s2); return ErrorMsg; }

    if(!SetPixelFormat(hDC, PixelFormat, &PFD))
    {
        Close();
        return "Unable to set the pixel format.";
    }


    // 7. Rendering Context erzeugen und aktivieren
    // ********************************************

    hRC=wglCreateContext(hDC);

    if (!hRC)
    {
        Close();
        return "Unable to create a GL rendering context.";
    }

    if(!wglMakeCurrent(hDC, hRC))
    {
        Close();
        return "Unable to activate the GL rendering context.";
    }


    // 8. Fenster anzeigen und einrichten
    // **********************************

    ShowWindow(hWindow, SW_SHOW);                      // Show the window.
    SetForegroundWindow(hWindow);                      // Slightly higher priority.
    SetFocus(hWindow);                                 // Sets keyboard focus to the window.


    // 8.1. DirectInput initialisieren
    // *******************************

    HRESULT hResult=DirectInput.Initialize(hInstance, hWindow);

    if (hResult!=DI_OK)
    {
        static char ErrorMsg[80];

        Close();
        sprintf(ErrorMsg, "Unable to initialize DirectInput!\nhResult=%u", hResult);
        return ErrorMsg;
    }
#else
    PostQuitMsgFlag=false;
    DisplayPtr     =XOpenDisplay(NULL);

    if (!DisplayPtr)                                return "Cannot open display.";
    if (!glXQueryExtension(DisplayPtr, NULL, NULL)) return "No GLX extension.";

#ifdef DEBUG
    int ExtVersionMajor=0;
    int ExtVersionMinor=0;
    if (glXQueryVersion(DisplayPtr, &ExtVersionMajor, &ExtVersionMinor)) printf("GLX version: %i.%i\n", ExtVersionMajor, ExtVersionMinor);
                                                                    else printf("GLX version could not be determined.\n");
#endif

    Title      =Title_;
    Width      =FullScreen_ ? DisplayWidth (DisplayPtr, DefaultScreen(DisplayPtr)) : Width_;
    Height     =FullScreen_ ? DisplayHeight(DisplayPtr, DefaultScreen(DisplayPtr)) : Height_;
    BPP        =BPP_;
    FullScreen =FullScreen_;
    IsMinimized=false;

    for (unsigned int c=0; c<256; c++) KeyboardState[c]=false;


    int VisualInfo_Features[] =
    {
        GLX_RGBA,
        GLX_RED_SIZE, 8,
        GLX_GREEN_SIZE, 8,
        GLX_BLUE_SIZE, 8,
        GLX_ALPHA_SIZE, 8,
        GLX_DEPTH_SIZE, 16,
        GLX_STENCIL_SIZE, 8,
        GLX_DOUBLEBUFFER,
        None
    };


    XVisualInfo* VisualInfo=glXChooseVisual(DisplayPtr, DefaultScreen(DisplayPtr), VisualInfo_Features);
    if (!VisualInfo) return "Cannot find visual. (You can possibly fix this by setting your desktop bit depth to 32 BPP. Just a guess.)";

    RC=glXCreateContext(DisplayPtr, VisualInfo, None, True);
    if (!RC) return "Cannot create GLX context.";


    XSetWindowAttributes WinAttribs;

    WinAttribs.colormap         =XCreateColormap(DisplayPtr, RootWindow(DisplayPtr, VisualInfo->screen), VisualInfo->visual, AllocNone);
    WinAttribs.border_pixel     =0;
    WinAttribs.override_redirect=True;
    WinAttribs.event_mask       =EventMask;

    Win=XCreateWindow(DisplayPtr,
                      RootWindow(DisplayPtr, VisualInfo->screen),
                      0, 0, Width, Height,
                      FullScreen ? 0 : 4,
                      VisualInfo->depth,
                      InputOutput,
                      VisualInfo->visual,
                      FullScreen ? CWBorderPixel | CWColormap | CWEventMask | CWOverrideRedirect : CWColormap | CWEventMask,
                      &WinAttribs);

    if (!Win) return "Cannot open window.";


    XSizeHints SizeHints;

    SizeHints.flags =PSize | PMaxSize | PMinSize;
    SizeHints.width =SizeHints.max_width =SizeHints.min_width =Width;
    SizeHints.height=SizeHints.max_height=SizeHints.min_height=Height;

    XSetStandardProperties(DisplayPtr, Win, Title.c_str(), NULL, None, NULL, 0, &SizeHints);


    glXMakeCurrent(DisplayPtr, Win, RC);
    XMapRaised(DisplayPtr, Win);

    XEvent Event;

    do
    {
        XMaskEvent(DisplayPtr, StructureNotifyMask, &Event);
    } while ((Event.type!=MapNotify) || (Event.xmap.event!=Win));


    if (FullScreen) XSetInputFocus(DisplayPtr, Win, RevertToPointerRoot, CurrentTime);

    // Turn off auto-repeat.
    // XAutoRepeatOff(DisplayPtr);

    // Make the mouse cursor invisible.
    // This is necessary in order to have it not flickering it in mid-screen all the time.
    Pixmap CursorMask=XCreatePixmap(DisplayPtr, Win, 1, 1, 1);

    XGCValues xgc;
    xgc.function=GXclear;

    GC gc=XCreateGC(DisplayPtr, CursorMask, GCFunction, &xgc);

    XFillRectangle(DisplayPtr, CursorMask, gc, 0, 0, 1, 1);

    XColor DummyColor;
    DummyColor.pixel=0;
    DummyColor.red  =0;
    DummyColor.flags=4;

    Cursor cursor=XCreatePixmapCursor(DisplayPtr, CursorMask, CursorMask, &DummyColor, &DummyColor, 0, 0);

    XFreePixmap(DisplayPtr, CursorMask);
    XFreeGC(DisplayPtr, gc);
 // XDefineCursor(DisplayPtr, Win, XCreateFontCursor(DisplayPtr, XC_tcross));
    XDefineCursor(DisplayPtr, Win, cursor);
#endif

    Resize(Width, Height);                // Perspektivischen OpenGL Screen einrichten.


    // 9. OpenGL initialisieren
    // ************************

    /* if (atof((char const*)glGetString(GL_VERSION))<1.2)
    {
        Close();
        return "Need at least OpenGL version 1.2 to run. Please update your video board drivers.";
    } */

    // glDepthFunc(GL_LEQUAL);
    // glPolygonOffset(1.0, 1.0);

    // glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    // glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glShadeModel(GL_SMOOTH);                                        // Enables smooth shading.
    glClearColor(0.0, 0.0, 0.0, 0.0);                               // Black background.

    glClearDepth(1.0);                                              // Depth Buffer setup.
    glEnable(GL_DEPTH_TEST);                                        // Enables depth testing.

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);              // Really nice perspective calculations.

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); SwapBuffers();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); SwapBuffers();


    // 10. Geschafft: Keine Initialisierungsfehler
    // *******************************************

    WindowIsOpen=true;
    RenderingContextCounter++;
    return NULL;
}