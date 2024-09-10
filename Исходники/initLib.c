/*
 * ::createGlInitContext
 */
BOOL createGlInitContext(GlInitContext *outCtx) {
    HINSTANCE hInst = GetModuleHandle(NULL);
    GLuint pixelFormat = 0;
    PIXELFORMATDESCRIPTOR pfd = { sizeof(PIXELFORMATDESCRIPTOR), 1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, 
        PFD_TYPE_RGBA, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0,
        PFD_MAIN_PLANE, 0, 0, 0, 0 };
    WNDCLASSEXA wndClass;
    
    if (outCtx == NULL) {
        return FALSE;
    }

    outCtx->hWnd = NULL;
    outCtx->hDC = NULL;
    outCtx->hRC = NULL;

    /* Register window class, if not yet available. */
    if (!GetClassInfoExA(hInst, INITCTX_WNDCLASS_NAME, &wndClass)) {
        ZeroMemory(&wndClass, sizeof(WNDCLASSEX));
        wndClass.cbSize = sizeof(WNDCLASSEX);
        wndClass.style = CS_CLASSDC;
        wndClass.lpfnWndProc = DefWindowProc;
        wndClass.hInstance = hInst;
        wndClass.lpszClassName = INITCTX_WNDCLASS_NAME;

        if (!RegisterClassExA(&wndClass)) {
            dbgPrint(DBGLVL_ERROR, "Registering window class for GL detours initialisation "
                "failed: %u\n", GetLastError());
            return FALSE;
        }
    }

    /* Create window. */
    if ((outCtx->hWnd = CreateWindowExA(WS_EX_APPWINDOW, 
            INITCTX_WNDCLASS_NAME, "", WS_POPUP, 0, 0, 1, 1, NULL, NULL, hInst,
            NULL)) == NULL) {
        dbgPrint(DBGLVL_ERROR, "Creating window for GL detours initialisation failed:\n",
            GetLastError());
        releaseGlInitContext(outCtx);
        return FALSE;
    }

    /* Create OpenGL context. */
    outCtx->hDC = GetDC(outCtx->hWnd);

    if ((pixelFormat = ChoosePixelFormat(outCtx->hDC, &pfd)) == 0) {
        dbgPrint(DBGLVL_ERROR, "ChoosePixelFormat failed: %u\n", GetLastError());
        releaseGlInitContext(outCtx);
        return FALSE;
    }
    if (!SetPixelFormat(outCtx->hDC, pixelFormat, &pfd)) {
        dbgPrint(DBGLVL_ERROR, "SetPixelFormat failed: %u\n", GetLastError());
        releaseGlInitContext(outCtx);
        return FALSE;
    }

    if ((outCtx->hRC = wglCreateContext(outCtx->hDC)) == NULL) {
        dbgPrint(DBGLVL_ERROR, "wglCreateContext failed: %u\n", GetLastError());
        releaseGlInitContext(outCtx);
        return FALSE;
    }
    if (!wglMakeCurrent(outCtx->hDC, outCtx->hRC)) {
        dbgPrint(DBGLVL_ERROR, "wglMakeCurrent failed: %u\n", GetLastError());
        releaseGlInitContext(outCtx);
        return FALSE;
    }

    return TRUE;
}