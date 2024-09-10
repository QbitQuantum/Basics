HWND
WGLLibrary::CreateDummyWindow(HDC *aWindowDC)
{
    WNDCLASSW wc;
    if (!GetClassInfoW(GetModuleHandle(NULL), L"GLContextWGLClass", &wc)) {
        ZeroMemory(&wc, sizeof(WNDCLASSW));
        wc.style = CS_OWNDC;
        wc.hInstance = GetModuleHandle(NULL);
        wc.lpfnWndProc = DefWindowProc;
        wc.lpszClassName = L"GLContextWGLClass";
        if (!RegisterClassW(&wc)) {
            NS_WARNING("Failed to register GLContextWGLClass?!");
            // er. failed to register our class?
            return NULL;
        }
    }

    HWND win = CreateWindowW(L"GLContextWGLClass", L"GLContextWGL", 0,
                             0, 0, 16, 16,
                             NULL, NULL, GetModuleHandle(NULL), NULL);
    NS_ENSURE_TRUE(win, NULL);

    HDC dc = GetDC(win);
    NS_ENSURE_TRUE(dc, NULL);

    if (mWindowPixelFormat == 0) {
        PIXELFORMATDESCRIPTOR pfd;
        ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
        pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
        pfd.nVersion = 1;
        pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
        if (mUseDoubleBufferedWindows)
            pfd.dwFlags |= PFD_DOUBLEBUFFER;
        pfd.iPixelType = PFD_TYPE_RGBA;
        pfd.cColorBits = 24;
        pfd.cRedBits = 8;
        pfd.cGreenBits = 8;
        pfd.cBlueBits = 8;
        pfd.cAlphaBits = 8;
        pfd.cDepthBits = 0;
        pfd.iLayerType = PFD_MAIN_PLANE;

        mWindowPixelFormat = ChoosePixelFormat(dc, &pfd);
    }

    if (!mWindowPixelFormat ||
        !SetPixelFormat(dc, mWindowPixelFormat, NULL))
    {
        NS_WARNING("SetPixelFormat failed!");
        DestroyWindow(win);
        return NULL;
    }

    if (aWindowDC) {
        *aWindowDC = dc;
    }

    return win;
}