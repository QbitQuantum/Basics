agpu_device *_agpu_device::open(agpu_device_open_info* openInfo)
{
    // Create the device.
    std::unique_ptr<agpu_device> device(new agpu_device);
    bool failure = false;

    // Perform the main context creation in
    device->mainContextJobQueue.start();
    AsyncJob contextCreationJob([&] {
        std::unique_ptr<OpenGLContext> contextWrapper(new OpenGLContext());

        // Window for context creation.
        HINSTANCE hInstance = GetModuleHandle(nullptr);
        WNDCLASSW wc;
        memset(&wc, 0, sizeof(wc));
        wc.lpfnWndProc = dummyWindowProc;
        wc.hInstance = hInstance;
        wc.lpszClassName = L"agpuDummyOGLWindow";
        wc.style = CS_OWNDC;
        if (!RegisterClassW(&wc))
        {
            failure = true;
            return;
        }

        HWND dummyWindow = CreateWindowW(wc.lpszClassName, L"agpuDummyOGLWindow", WS_OVERLAPPEDWINDOW, 0, 0, 16, 16, 0, 0, hInstance, 0);

        // Need to create a dummy context first.
        PIXELFORMATDESCRIPTOR pixelFormatDescriptor =
        {
            sizeof(PIXELFORMATDESCRIPTOR),
            1,
            PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
            PFD_TYPE_RGBA,            //The kind of framebuffer. RGBA or palette.
            32,                        //Colordepth of the framebuffer.
            0, 0, 0, 0, 0, 0,
            0,
            0,
            0,
            0, 0, 0, 0,
            24,                        //Number of bits for the depthbuffer
            8,                        //Number of bits for the stencilbuffer
            0,                        //Number of Aux buffers in the framebuffer.
            PFD_MAIN_PLANE,
            0,
            0, 0, 0
        };

        // Set the pixel format.
        auto dummyDC = GetDC(dummyWindow);
        int dummyPixelFormat = ChoosePixelFormat(dummyDC, &pixelFormatDescriptor);
        auto pfRes = SetPixelFormat(dummyDC, dummyPixelFormat, &pixelFormatDescriptor);;
        if (pfRes == FALSE)
        {
            if (!printLastError())
                printError("Failed to set window pixel format.\n");

        }

        // Create the context.
        auto dummyContext = wglCreateContext(dummyDC);
        if (!dummyContext)
        {
            DestroyWindow(dummyWindow);
            failure = true;
            return;
        }

        // Use the context.
        if (!wglMakeCurrent(dummyDC, dummyContext))
        {
            wglDeleteContext(dummyContext);
            DestroyWindow(dummyWindow);
            failure = true;
            return;
        }

        // Create the context window.
        HWND contextWindow = CreateWindowW(wc.lpszClassName, L"agpuOGLWindow", WS_OVERLAPPEDWINDOW, 0, 0, 16, 16, 0, 0, hInstance, 0);
        auto contextDC = GetDC(contextWindow);

        // Choose a proper pixel format
        contextWrapper->wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
        if (contextWrapper->wglChoosePixelFormatARB)
        {
            int pixelFormat;
            UINT numFormats;
            int pixelAttributes[] = {
                WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
                WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
                WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
                WGL_RED_BITS_ARB, 8,
                WGL_GREEN_BITS_ARB, 8,
                WGL_BLUE_BITS_ARB, 8,
                WGL_ALPHA_BITS_ARB, 8,
                WGL_DEPTH_BITS_ARB, 0,
                0
            };

            contextWrapper->wglChoosePixelFormatARB(contextDC, &pixelAttributes[0], nullptr, 1, &pixelFormat, &numFormats);
            auto res = SetPixelFormat(contextDC, pixelFormat, &pixelFormatDescriptor);
            if (res == FALSE)
            {
                printError("Failed to set the pixel format.\n");
                failure = true;
                return;
            }
        }
        else
        {
            printError("Missing a required extension.\n");
            failure = true;
            return;
        }

        // Now create the actual context.
        contextWrapper->wglCreateContextAttribsARB = (wglCreateContextAttribsARBProc)wglGetProcAddress("wglCreateContextAttribsARB");
        if (contextWrapper->wglCreateContextAttribsARB)
        {
            int contextAttributes[] =
            {
                WGL_CONTEXT_MAJOR_VERSION_ARB, 0,
                WGL_CONTEXT_MINOR_VERSION_ARB, 0,
                //GLX_CONTEXT_FLAGS_ARB        , GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
                0
            };

            for (int versionIndex = 0; GLContextVersionPriorities[versionIndex] != OpenGLVersion::Invalid; ++versionIndex)
            {
                auto version = (int)GLContextVersionPriorities[versionIndex];

                // GLX_CONTEXT_MAJOR_VERSION_ARB
                contextAttributes[1] = version / 10;
                // GLX_CONTEXT_MINOR_VERSION_ARB
                contextAttributes[3] = version % 10;

                contextWrapper->context = contextWrapper->wglCreateContextAttribsARB(contextDC, NULL, contextAttributes);//glXCreateContextAttribsARB(display, framebufferConfig, 0, True, contextAttributes);

                // Check for success.
                if (contextWrapper->context)
                {
                    contextWrapper->version = OpenGLVersion(version);
                    break;
                }
            }
        }
        else
        {
            contextWrapper->context = wglCreateContext(contextDC);
        }

        // Destroy the dummy context
        wglMakeCurrent(dummyDC, NULL);
        wglDeleteContext(dummyContext);
        DestroyWindow(dummyWindow);

        // Set the current context.
        if (!contextWrapper->context || !wglMakeCurrent(contextDC, contextWrapper->context))
        {
            failure = true;
            return;
        }

        // Create the device and load the extensions.
        contextWrapper->window = contextWindow;
        contextWrapper->hDC = contextDC;
        contextWrapper->makeCurrent();
        device->mainContext = contextWrapper.release();
        device->mainContext->device = device.get();
        device->initializeObjects();
    });

    device->mainContextJobQueue.addJob(&contextCreationJob);
    contextCreationJob.wait();
    if (failure)
        return nullptr;

    return device.release();
}