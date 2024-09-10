bool GL_Init(HWND window, std::string *error_message) {
    *error_message = "ok";
    hWnd = window;
    GLuint PixelFormat;

    // TODO: Change to use WGL_ARB_pixel_format instead
    static const PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),							// Size Of This Pixel Format Descriptor
        1,														// Version Number
        PFD_DRAW_TO_WINDOW |									// Format Must Support Window
        PFD_SUPPORT_OPENGL |									// Format Must Support OpenGL
        PFD_DOUBLEBUFFER,										// Must Support Double Buffering
        PFD_TYPE_RGBA,											// Request An RGBA Format
        24,														// Select Our Color Depth
        0, 0, 0, 0, 0, 0,										// Color Bits Ignored
        8,														// No Alpha Buffer
        0,														// Shift Bit Ignored
        0,														// No Accumulation Buffer
        0, 0, 0, 0,										// Accumulation Bits Ignored
        16,														// At least a 16Bit Z-Buffer (Depth Buffer)
        8,														// 8-bit Stencil Buffer
        0,														// No Auxiliary Buffer
        PFD_MAIN_PLANE,								// Main Drawing Layer
        0,														// Reserved
        0, 0, 0												// Layer Masks Ignored
    };

    hDC = GetDC(hWnd);

    if (!hDC) {
        *error_message = "Failed to get a device context.";
        return false;											// Return FALSE
    }

    if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))	{
        *error_message = "Can't find a suitable PixelFormat.";
        return false;
    }

    if (!SetPixelFormat(hDC, PixelFormat, &pfd)) {
        *error_message = "Can't set the PixelFormat.";
        return false;
    }

    if (!(hRC = wglCreateContext(hDC)))	{
        *error_message = "Can't create a GL rendering context.";
        return false;
    }

    if (!wglMakeCurrent(hDC, hRC)) {
        *error_message = "Can't activate the GL rendering context.";
        return false;
    }

    // Check for really old OpenGL drivers and refuse to run really early in some cases.

    // TODO: Also either tell the user to give up or point the user to the right websites. Here's some collected
    // information about a system that will not work:

    // GL_VERSION                        GL_VENDOR        GL_RENDERER
    // "1.4.0 - Build 8.14.10.2364"      "intel"          intel Pineview Platform
    I18NCategory *err = GetI18NCategory("Error");

    std::string glVersion = (const char *)glGetString(GL_VERSION);
    std::string glRenderer = (const char *)glGetString(GL_RENDERER);
    const std::string openGL_1 = "1.";

    if (glRenderer == "GDI Generic" || glVersion.substr(0, openGL_1.size()) == openGL_1) {
        //The error may come from 16-bit colour mode
        //Check Colour depth
        HDC dc = GetDC(NULL);
        u32 colour_depth = GetDeviceCaps(dc, BITSPIXEL);
        ReleaseDC(NULL, dc);
        if (colour_depth != 32) {
            MessageBox(0, L"Please switch your display to 32-bit colour mode", L"OpenGL Error", MB_OK);
            ExitProcess(1);
        }
        const char *defaultError = "Insufficient OpenGL driver support detected!\n\n"
                                   "Your GPU reports that it does not support OpenGL 2.0. Would you like to try using DirectX 9 instead?\n\n"
                                   "DirectX is currently compatible with less games, but on your GPU it may be the only choice.\n\n"
                                   "Visit the forums at http://forums.ppsspp.org for more information.\n\n";

        std::wstring versionDetected = ConvertUTF8ToWString(glVersion + "\n\n");
        std::wstring error = ConvertUTF8ToWString(err->T("InsufficientOpenGLDriver", defaultError));
        std::wstring title = ConvertUTF8ToWString(err->T("OpenGLDriverError", "OpenGL driver error"));
        std::wstring combined = versionDetected + error;

        bool yes = IDYES == MessageBox(hWnd, combined.c_str(), title.c_str(), MB_ICONERROR | MB_YESNO);

        if (yes) {
            // Change the config to D3D and restart.
            g_Config.iGPUBackend = GPU_BACKEND_DIRECT3D9;
            g_Config.Save();

            W32Util::ExitAndRestart();
        }

        // Avoid further error messages. Let's just bail, it's safe, and we can't continue.
        ExitProcess(1);
    }

    if (GLEW_OK != glewInit()) {
        *error_message = "Failed to initialize GLEW.";
        return false;
    }

    CheckGLExtensions();

    int contextFlags = g_Config.bGfxDebugOutput ? WGL_CONTEXT_DEBUG_BIT_ARB : 0;

    // Alright, now for the modernity. First try a 4.4, then 4.3, context, if that fails try 3.3.
    // I can't seem to find a way that lets you simply request the newest version available.
    const int attribs44[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
        WGL_CONTEXT_MINOR_VERSION_ARB, 4,
        WGL_CONTEXT_FLAGS_ARB, contextFlags,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
        0
    };
    const int attribs43[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
        WGL_CONTEXT_MINOR_VERSION_ARB, 3,
        WGL_CONTEXT_FLAGS_ARB, contextFlags,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
        0
    };
    const int attribs33[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
        WGL_CONTEXT_MINOR_VERSION_ARB, 3,
        WGL_CONTEXT_FLAGS_ARB, contextFlags,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
        0
    };

    HGLRC	m_hrc;
    if(wglewIsSupported("WGL_ARB_create_context") == 1) {
        m_hrc = wglCreateContextAttribsARB(hDC, 0, attribs44);
        if (!m_hrc)
            m_hrc = wglCreateContextAttribsARB(hDC, 0, attribs43);
        if (!m_hrc)
            m_hrc = wglCreateContextAttribsARB(hDC, 0, attribs33);
        if (!m_hrc) {
            // Fall back
            m_hrc = hRC;
        } else {
            // Switch to the new ARB context.
            wglMakeCurrent(NULL, NULL);
            wglDeleteContext(hRC);
            wglMakeCurrent(hDC, m_hrc);
        }
    } else {
        // We can't make a GL 3.x context. Use an old style context (GL 2.1 and before)
        m_hrc = hRC;
    }

    if (GLEW_OK != glewInit()) {
        *error_message = "Failed to re-initialize GLEW.";
        return false;
    }

    if (!m_hrc) {
        *error_message = "No m_hrc";
        return false;
    }

    hRC = m_hrc;

    GL_SwapInterval(0);

    // TODO: Also support GL_KHR_debug which might be more widely supported?
    if (g_Config.bGfxDebugOutput && glewIsSupported("GL_ARB_debug_output")) {
        glGetError();
        glDebugMessageCallbackARB((GLDEBUGPROCARB)&DebugCallbackARB, 0); // print debug output to stderr
        if (glGetError()) {
            ERROR_LOG(G3D, "Failed to register a debug log callback");
        }
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
        if (glGetError()) {
            ERROR_LOG(G3D, "Failed to enable synchronous debug output");
        }

        // For extra verbosity uncomment this (MEDIUM and HIGH are on by default):
        // glDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_LOW_ARB, 0, nullptr, GL_TRUE);
    }

    pauseRequested = false;
    resumeRequested = false;

    // These are auto-reset events.
    pauseEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    resumeEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

    return true;												// Success
}