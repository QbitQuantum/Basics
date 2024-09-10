    WindowedGLContext (Component* const component_,
                       HGLRC contextToShareWith,
                       const OpenGLPixelFormat& pixelFormat)
        : renderContext (0),
          component (component_),
          dc (0)
    {
        initialiseGLExtensions();
        jassert (component != nullptr);
        createNativeWindow();

        PIXELFORMATDESCRIPTOR pfd;
        initialisePixelFormatDescriptor (pfd, pixelFormat);

        const int format = ChoosePixelFormat (dc, &pfd);

        if (format != 0)
            SetPixelFormat (dc, format, &pfd);

        renderContext = wglCreateContext (dc);

        if (renderContext != 0)
        {
            makeActive();
            initialiseGLExtensions();
            extensions.initialise();
            setPixelFormat (pixelFormat);

            if (contextToShareWith != 0)
                wglShareLists (contextToShareWith, renderContext);
        }
    }