//--------------------------------------------------------------------------------------
// Initialize drawing API
//--------------------------------------------------------------------------------------
HRESULT InitBackend(HWND hWnd)
{
    if (!(g_hDC = GetDC(hWnd)))
    {
        printf("Error: Device fail.\n");
        return E_FAIL;
    }

    int format;
    static PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR), // Size Of This Pixel Format Descriptor
        1, // Version Number
        PFD_DRAW_TO_WINDOW | // Format Must Support Window
        PFD_SUPPORT_OPENGL | // Format Must Support OpenGL
        PFD_DOUBLEBUFFER, // Must Support Double Buffering
        PFD_TYPE_RGBA, // Request An RGBA Format
        32, // Select Our Color Depth
        0, 0, 0, 0, 0, 0, // Color Bits Ignored
        0, // No Alpha Buffer
        0, // Shift Bit Ignored
        0, // No Accumulation Buffer
        0, 0, 0, 0, // Accumulation Bits Ignored
        16, // 16Bit Z-Buffer (Depth Buffer)
        0, // No Stencil Buffer
        0, // No Auxiliary Buffer
        PFD_MAIN_PLANE, // Main Drawing Layer
        0, // Reserved
        0, 0, 0
    };

    if (!(format = ChoosePixelFormat(g_hDC, &pfd)))
    {
        printf("Error: PixelFormat fail.\n");
        return E_FAIL;
    }
    if (!SetPixelFormat(g_hDC, format, &pfd))
    {
        printf("Error: PixelFormat not set.\n");
        return E_FAIL;
    }
    if (!(g_hRC = wglCreateContext(g_hDC)))
    {
        printf("Error: Context not creted.\n");
        return E_FAIL;
    }
    if (!wglMakeCurrent(g_hDC, g_hRC))
    {
        printf("Error: Context not set.\n");
        return E_FAIL;
    }

    // initialize glew
    GLenum res = glewInit();
    if (res != GLEW_OK)
    {
        printf("Error: GLEW fail.\n");
        return E_FAIL;
    }

    return S_OK;
}