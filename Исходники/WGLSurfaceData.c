/**
 * This function initializes a native window surface and caches the window
 * bounds in the given OGLSDOps.  Returns JNI_TRUE if the operation was
 * successful; JNI_FALSE otherwise.
 */
jboolean
OGLSD_InitOGLWindow(JNIEnv *env, OGLSDOps *oglsdo)
{
    PIXELFORMATDESCRIPTOR pfd;
    WGLSDOps *wglsdo;
    WGLGraphicsConfigInfo *wglInfo;
    HWND window;
    RECT wbounds;
    HDC hdc;

    J2dTraceLn(J2D_TRACE_INFO, "OGLSD_InitOGLWindow");

    if (oglsdo == NULL) {
        J2dRlsTraceLn(J2D_TRACE_ERROR,
                      "OGLSD_InitOGLWindow: ops are null");
        return JNI_FALSE;
    }

    wglsdo = (WGLSDOps *)oglsdo->privOps;
    if (wglsdo == NULL) {
        J2dRlsTraceLn(J2D_TRACE_ERROR,
                      "OGLSD_InitOGLWindow: wgl ops are null");
        return JNI_FALSE;
    }

    wglInfo = wglsdo->configInfo;
    if (wglInfo == NULL) {
        J2dRlsTraceLn(J2D_TRACE_ERROR,
                      "OGLSD_InitOGLWindow: graphics config info is null");
        return JNI_FALSE;
    }

    window = wglsdo->window;
    if (!IsWindow(window)) {
        J2dRlsTraceLn(J2D_TRACE_ERROR,
                      "OGLSD_InitOGLWindow: disposed component");
        return JNI_FALSE;
    }

    GetWindowRect(window, &wbounds);

    hdc = GetDC(window);
    if (hdc == 0) {
        J2dRlsTraceLn(J2D_TRACE_ERROR,
                      "OGLSD_InitOGLWindow: invalid hdc");
        return JNI_FALSE;
    }

    if (!SetPixelFormat(hdc, wglInfo->pixfmt, &pfd)) {
        J2dRlsTraceLn(J2D_TRACE_ERROR,
                      "OGLSD_InitOGLWindow: error setting pixel format");
        ReleaseDC(window, hdc);
        return JNI_FALSE;
    }

    ReleaseDC(window, hdc);

    oglsdo->drawableType = OGLSD_WINDOW;
    oglsdo->isOpaque = JNI_TRUE;
    oglsdo->width = wbounds.right - wbounds.left;
    oglsdo->height = wbounds.bottom - wbounds.top;
    wglsdo->pbufferDC = 0;

    J2dTraceLn2(J2D_TRACE_VERBOSE, "  created window: w=%d h=%d",
                oglsdo->width, oglsdo->height);

    return JNI_TRUE;
}