static cairo_status_t
_wgl_dummy_ctx (cairo_wgl_context_t *ctx)
{
    WNDCLASSEXA wincl;
    PIXELFORMATDESCRIPTOR pfd;
    int format;
    HDC dc;

    ZeroMemory (&wincl, sizeof (WNDCLASSEXA));
    wincl.cbSize = sizeof (WNDCLASSEXA);
    wincl.hInstance = GetModuleHandle (0);
    wincl.lpszClassName = "cairo_wgl_context_dummy";
    wincl.lpfnWndProc = DefWindowProcA;
    wincl.style = CS_OWNDC;

    RegisterClassExA (&wincl);

    ctx->dummy_wnd = CreateWindowA ("cairo_wgl_context_dummy", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    ctx->dummy_dc = GetDC (ctx->dummy_wnd);

    ZeroMemory (&pfd, sizeof (PIXELFORMATDESCRIPTOR));
    pfd.nSize = sizeof (PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
#ifndef WKC_CAIRO_CUSTOMIZE
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
#else
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;/* | PFD_DOUBLEBUFFER;*/
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 32;
    pfd.cStencilBits = 32;
#endif
    pfd.iLayerType = PFD_MAIN_PLANE;

    format = ChoosePixelFormat (ctx->dummy_dc, &pfd);
    SetPixelFormat (ctx->dummy_dc, format, &pfd);

    wglMakeCurrent(ctx->dummy_dc, ctx->rc);

    return CAIRO_STATUS_SUCCESS;
}