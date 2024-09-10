// Destroy the application window. Attempt to remove the rendering context and
// the device context as well.
void gs_display_dispose(long display)
{
    HWND hwnd = LongToHandle(display);
    HDC shell = GetDC(hwnd);
    HGLRC context = wglGetCurrentContext();
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(context);
    ReleaseDC(hwnd, shell);
    DestroyWindow(hwnd);
}