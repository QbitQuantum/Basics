djvWglContext::djvWglContext(djvCoreContext * context) throw (djvError) :
    djvOpenGlContext(context),
    _p(new djvWglContextPrivate)
{
#   if defined(DJV_WINDOWS)

    //DJV_DEBUG("djvWglContext::djvWglContext");

    // Create a dummy window and OpenGL context for glewInit.
    // According to the docs, glewInit can be called just once per-process?

    DJV_LOG(context->debugLog(), "djvWglContext", "Creating dummy window...");

    HINSTANCE hinstance = GetModuleHandle(0);

    if (! hinstance)
    {
        throw djvError(
            "djvWglContext",
            errorLabels()[ERROR_MODULE_HANDLE].arg(int(GetLastError())));
    }

    static const char name [] = "djv";
    WNDCLASS wc;
    if (! GetClassInfo(hinstance, name, &wc))
    {
        wc.style = CS_OWNDC;
        //wc.lpfnWndProc = (WNDPROC)MainWndProc;
        wc.lpfnWndProc = DefWindowProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = hinstance;
        wc.hIcon = LoadIcon(0, IDI_APPLICATION);
        wc.hCursor = LoadCursor(0, IDC_ARROW);
        wc.hbrBackground = 0;
        wc.lpszMenuName = 0;
        wc.lpszClassName = name;

        if (! RegisterClass(&wc))
        {
            throw djvError(
                "djvWglContext",
                errorLabels()[ERROR_REGISTER_CLASS].arg(int(GetLastError())));
        }
    }

    _p->id = CreateWindow(name, 0, 0, 0, 0, 0, 0, 0, 0, hinstance, 0);

    if (! _p->id)
    {
        throw djvError(
            "djvWglContext",
            errorLabels()[ERROR_CREATE_WINDOW].arg(int(GetLastError())));
    }

    _p->device = GetDC(_p->id);

    if (! _p->device)
    {
        throw djvError(
            "djvWglContext",
            errorLabels()[ERROR_GET_DC].arg(int(GetLastError())));
    }

    PIXELFORMATDESCRIPTOR pixelFormatInfo;

    const int pixelFormatCount = DescribePixelFormat(_p->device, 0, 0, 0);

    //DJV_DEBUG_PRINT("pixel format count = " << pixelFormatCount);

    DJV_LOG(context->debugLog(), "djvWglContext",
            QString("Pixel format count: %1").arg(pixelFormatCount));

    for (int i = 1; i < pixelFormatCount; ++i)
    {
        DescribePixelFormat(
            _p->device,
            i,
            sizeof(PIXELFORMATDESCRIPTOR),
            &pixelFormatInfo);

        //DJV_DEBUG_PRINT("  id " << i << ": " <<
        //    ((PFD_SUPPORT_OPENGL & pixelFormatInfo.dwFlags) ? "gl " : "") <<
        //    ((PFD_GENERIC_FORMAT & pixelFormatInfo.dwFlags) ? "" : "accel ") <<
        //    ((PFD_TYPE_RGBA == pixelFormatInfo.iPixelType) ? "rgba " : "") <<
        //    "depth = " << pixelFormatInfo.cColorBits << "/" <<
        //    pixelFormatInfo.cRedBits << "/" <<
        //    pixelFormatInfo.cGreenBits << "/" <<
        //    pixelFormatInfo.cBlueBits << "/" <<
        //    pixelFormatInfo.cAlphaBits << " ");

        QStringList tmp;
        if (PFD_SUPPORT_OPENGL & pixelFormatInfo.dwFlags)
            tmp += "gl";
        if (! (PFD_GENERIC_FORMAT & pixelFormatInfo.dwFlags))
            tmp += "accel";
        if (PFD_TYPE_RGBA == pixelFormatInfo.iPixelType)
            tmp += "rgba";

        DJV_LOG(context->debugLog(), "djvWglContext",
                QString("Pixel format %1: %2 %3/%4/%5/%6/%7").
                arg(i).
                arg(tmp.join(" ")).
                arg(pixelFormatInfo.cColorBits).
                arg(pixelFormatInfo.cRedBits).
                arg(pixelFormatInfo.cGreenBits).
                arg(pixelFormatInfo.cBlueBits).
                arg(pixelFormatInfo.cAlphaBits));
    }

    PIXELFORMATDESCRIPTOR pixelFormat =
    {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL,
        PFD_TYPE_RGBA,
        32,
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        0,
        0,
        0,
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };

    int pixelFormatId = ChoosePixelFormat(_p->device, &pixelFormat);

    //DJV_DEBUG_PRINT("pixel format = " << pixelFormatId);

    DJV_LOG(context->debugLog(), "djvWglContext",
            QString("Chosen pixel format: %1").arg(pixelFormatId));

    if (! pixelFormatId)
    {
        throw djvError(
            "djvWglContext",
            errorLabels()[ERROR_GET_PIXEL_FORMAT].arg(int(GetLastError())));
    }

    if (! SetPixelFormat(_p->device, pixelFormatId, &pixelFormat))
    {
        throw djvError(
            "djvWglContext",
            errorLabels()[ERROR_SET_PIXEL_FORMAT].arg(int(GetLastError())));
    }

    // Create OpengGL context.

    DJV_LOG(context->debugLog(), "djvWglContext", "Creating OpenGL context...");

    _p->context = wglCreateContext(_p->device);

    if (! _p->context)
    {
        throw djvError(
            "djvWglContext",
            errorLabels()[ERROR_CREATE_CONTEXT].arg(int(GetLastError())));
    }

    if (! wglMakeCurrent(_p->device, _p->context))
    {
        throw djvError(
            "djvWglContext",
            errorLabels()[ERROR_BIND_CONTEXT].arg(int(GetLastError())));
    }

    // Initialize GLEW.

    DJV_LOG(context->debugLog(), "djvWglContext", "Initializing GLEW...");

    GLenum err = glewInit();

    if (err != GLEW_OK)
    {
        throw djvError(
            "djvWglContext",
            errorLabels()[ERROR_INIT_GLEW].arg((char *)glewGetErrorString(err)));
    }

    setVendor(QString((const char *)glGetString(GL_VENDOR)));
    setRenderer(QString((const char *)glGetString(GL_RENDERER)));
    setVersion(QString((const char *)glGetString(GL_VERSION)));

    //DJV_DEBUG_PRINT("OpenGL vendor string = " << vendor());
    //DJV_DEBUG_PRINT("OpenGL renderer string = " << renderer());
    //DJV_DEBUG_PRINT("OpenGL version string = " << version());
    //DJV_DEBUG_PRINT("OpenGL extensions = " <<
    //    (const char *)glGetString(GL_EXTENSIONS));
    //DJV_DEBUG_PRINT("glu version = " <<
    //    (const char *)gluGetString(GLU_VERSION));
    //DJV_DEBUG_PRINT("glu extensions = " <<
    //    (const char *)gluGetString(GLU_EXTENSIONS));

    DJV_LOG(context->debugLog(), "djvWglContext",
            QString("GL vendor: \"%1\"").arg(vendor()));
    DJV_LOG(context->debugLog(), "djvWglContext",
            QString("GL renderer: \"%1\"").arg(renderer()));
    DJV_LOG(context->debugLog(), "djvWglContext",
            QString("GL version: \"%1\"").arg(version()));

#   endif // DJV_WINDOWS
}