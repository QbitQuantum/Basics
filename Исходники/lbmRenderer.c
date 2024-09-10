static void lbmSetupPixelFormat(HDC dc)
{
    PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),  /* size */
        1,                              /* version */
        PFD_SUPPORT_OPENGL |
        PFD_DRAW_TO_WINDOW |
        PFD_DOUBLEBUFFER,               /* support double-buffering */
        PFD_TYPE_RGBA,                  /* color type */
        16,                             /* prefered color depth */
        0, 0, 0, 0, 0, 0,               /* color bits (ignored) */
        0,                              /* no alpha buffer */
        0,                              /* alpha bits (ignored) */
        0,                              /* no accumulation buffer */
        0, 0, 0, 0,                     /* accum bits (ignored) */
        16,                             /* depth buffer */
        0,                              /* no stencil buffer */
        0,                              /* no auxiliary buffers */
        PFD_MAIN_PLANE,                 /* main layer */
        0,                              /* reserved */
        0, 0, 0,                        /* no layer, visible, damage masks */
    };
    int pixelFormat;

    pixelFormat = ChoosePixelFormat(dc, &pfd);
    if (pixelFormat == 0)
    {
        MessageBox(WindowFromDC(dc), "ChoosePixelFormat failed.", "Error", MB_ICONERROR | MB_OK);
        exit(1);
    }

    if (SetPixelFormat(dc, pixelFormat, &pfd) != TRUE)
    {
        MessageBox(WindowFromDC(dc), "SetPixelFormat failed.", "Error", MB_ICONERROR | MB_OK);
        exit(1);
    }
}