/**
 *  Erstellt das Fenster mit entsprechenden Werten.
 *
 *  @param[in] width      Breite des Fensters
 *  @param[in] height     Höhe des Fensters
 *  @param[in] fullscreen Vollbildmodus ja oder nein
 *
 *  @return @p true bei Erfolg, @p false bei Fehler
 *
 *  @bug Hardwarecursor ist bei Fenstermodus sichtbar,
 *       Cursor deaktivieren ist fehlerhaft
 *
 *  @author FloSoft
 */
bool VideoWinAPI::CreateScreen(unsigned short width, unsigned short height, const bool fullscreen)
{
    char title[512];

    if(!initialized)
        return false;

    LPWSTR wTitle;
    AnsiToUtf8(wTitle, GetWindowTitle());

    WNDCLASSW  wc;
    wc.style            = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc      = WindowProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hInstance        = GetModuleHandle(NULL);
    wc.hIcon            = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_SYMBOL));
    wc.hCursor          = NULL;
    wc.hbrBackground    = NULL;
    wc.lpszMenuName     = NULL;
    wc.lpszClassName    = wTitle;

    // Fensterklasse registrieren
    if (!RegisterClassW(&wc))
        return false;

    DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
    DWORD dwStyle   = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX;

    if(fullscreen)
    {
        dwExStyle   = WS_EX_APPWINDOW;
        dwStyle     = WS_POPUP;

        EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &dm_prev);
    }
    else
    {
        // Bei Fensteranwendung die Breiten und Hoehen der Fensterrahmen, Titelleiste draufaddieren
        width += 2 * GetSystemMetrics(SM_CXFIXEDFRAME);
        height += 2 * GetSystemMetrics(SM_CXFIXEDFRAME) + GetSystemMetrics(SM_CYCAPTION);
    }

    // Fenster erstellen
    screen = CreateWindowExW(dwExStyle, wTitle, wTitle, dwStyle, CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL, GetModuleHandle(NULL), NULL);

    delete[] wTitle;

    if(screen == NULL)
        return false;

    SetClipboardViewer(screen);

    sprintf(title, "%s - v%s-%s", GetWindowTitle(), GetWindowVersion(), GetWindowRevision());

    AnsiToUtf8(wTitle, title);

    SetWindowTextW(screen, wTitle);
    SetWindowTextW(GetConsoleWindow(), wTitle);

    delete[] wTitle;

    // Pixelformat zuweisen
    GLuint PixelFormat;
    static PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        8, // 8 Bit
        8, // red
        0,
        8, // green
        0,
        8, // blue
        0,
        8, // alpha
        0,
        0,
        0,
        0,
        0,
        0,
        32, // 32 Bit
        0,
        0,
        PFD_MAIN_PLANE,
        0,
        0,
        0,
        0
    };

    screen_dc = GetDC(screen);
    if(screen_dc == NULL)
        return false;

    // Pixelformat auswaehlen
    PixelFormat = ChoosePixelFormat(screen_dc, &pfd);
    if(PixelFormat == 0)
        return false;

    // Pixelformat zuweisen
    if(!SetPixelFormat(screen_dc, PixelFormat, &pfd))
        return false;

    // Renderingkontext erstellen
    screen_rc = wglCreateContext(screen_dc);
    if(screen_rc == NULL)
        return false;

    // Renderingkontext aktivieren
    if(!wglMakeCurrent(screen_dc, screen_rc))
        return false;

    // Mauscursor ausblenden
    ShowCursor(FALSE);

    // Bei Fullscreen Aufloesung umstellen
    if(fullscreen)
    {
        // Aktuelle Framerate holen und die spaeter dann benutzen
        DEVMODE prev;
        EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &prev);

        DEVMODE dm;
        memset(&dm, 0, sizeof(dm));
        dm.dmSize = sizeof(dm);
        dm.dmFields = DM_DISPLAYFREQUENCY | DM_PELSWIDTH | DM_PELSHEIGHT;
        dm.dmDisplayFrequency = prev.dmDisplayFrequency;
        dm.dmPelsWidth = width;
        dm.dmPelsHeight = height;

        ChangeDisplaySettings(&dm, CDS_FULLSCREEN);
    }

    this->screenWidth  = width;
    this->screenHeight = height;
    this->fullscreen = fullscreen;

    // Das Fenster anzeigen
    ShowWindow(screen, SW_SHOW);
    // Das Fenster in den Vordergrund rcken
    SetForegroundWindow(screen);
    // Dem Fenster den Eingabefokus geben
    SetFocus(screen);

    return true;
}