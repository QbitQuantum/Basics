static HWND
toglCreateTestWindow(HWND parent)
{
    static char ClassName[] = "ToglTestWindow";
    WNDCLASS wc;
    HINSTANCE instance = GetModuleHandle(NULL);
    HWND    wnd;
    HDC     dc;
    PIXELFORMATDESCRIPTOR pfd;
    int     pixelFormat;

    wc.style = CS_OWNDC;
    wc.lpfnWndProc = DefWindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = instance;
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = NULL;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = ClassName;
    if (!RegisterClass(&wc)) {
        DWORD   err = GetLastError();

        if (err != ERROR_CLASS_ALREADY_EXISTS) {
            fprintf(stderr, "Unable to register Togl Test Window class\n");
            return NULL;
        }
    }

    wnd = CreateWindow(ClassName, "test OpenGL capabilities",
            WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
            0, 0, 1, 1, parent, NULL, instance, NULL);
    if (wnd == NULL) {
        fprintf(stderr, "Unable to create temporary OpenGL window\n");
        return NULL;
    }
    dc = GetDC(wnd);

    memset(&pfd, 0, sizeof pfd);
    pfd.nSize = sizeof pfd;
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 3;
    pfd.iLayerType = PFD_MAIN_PLANE;
    pixelFormat = ChoosePixelFormat(dc, &pfd);
    if (pixelFormat == 0) {
        fprintf(stderr, "Unable to choose simple pixel format\n");
        ReleaseDC(wnd, dc);
        return NULL;
    }
    if (!SetPixelFormat(dc, pixelFormat, &pfd)) {
        fprintf(stderr, "Unable to set simple pixel format\n");
        ReleaseDC(wnd, dc);
        return NULL;
    }

    ShowWindow(wnd, SW_HIDE);   // make sure it's hidden
    ReleaseDC(wnd, dc);
    return wnd;
}