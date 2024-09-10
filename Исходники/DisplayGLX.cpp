egl::Error DisplayGLX::initialize(egl::Display *display)
{
    mEGLDisplay = display;
    Display *xDisplay = display->getNativeDisplayId();

    // ANGLE_platform_angle allows the creation of a default display
    // using EGL_DEFAULT_DISPLAY (= nullptr). In this case just open
    // the display specified by the DISPLAY environment variable.
    if (xDisplay == EGL_DEFAULT_DISPLAY)
    {
        mUsesNewXDisplay = true;
        xDisplay = XOpenDisplay(NULL);
        if (!xDisplay)
        {
            return egl::Error(EGL_NOT_INITIALIZED, "Could not open the default X display.");
        }
    }

    std::string glxInitError;
    if (!mGLX.initialize(xDisplay, DefaultScreen(xDisplay), &glxInitError))
    {
        return egl::Error(EGL_NOT_INITIALIZED, glxInitError.c_str());
    }

    // Check we have the needed extensions
    {
        if (mGLX.minorVersion == 3 && !mGLX.hasExtension("GLX_ARB_multisample"))
        {
            return egl::Error(EGL_NOT_INITIALIZED, "GLX doesn't support ARB_multisample.");
        }
        // Require ARB_create_context which has been supported since Mesa 9 unconditionnaly
        // and is present in Mesa 8 in an almost always on compile flag. Also assume proprietary
        // drivers have it.
        if (!mGLX.hasExtension("GLX_ARB_create_context"))
        {
            return egl::Error(EGL_NOT_INITIALIZED, "GLX doesn't support ARB_create_context.");
        }
    }

    // When glXMakeCurrent is called, the context and the surface must be
    // compatible which in glX-speak means that their config have the same
    // color buffer type, are both RGBA or ColorIndex, and their buffers have
    // the same depth, if they exist.
    // Since our whole EGL implementation is backed by only one GL context, this
    // context must be compatible with all the GLXFBConfig corresponding to the
    // EGLconfigs that we will be exposing.
    {
        int nConfigs;
        int attribList[] =
        {
            // We want RGBA8 and DEPTH24_STENCIL8
            GLX_RED_SIZE, 8,
            GLX_GREEN_SIZE, 8,
            GLX_BLUE_SIZE, 8,
            GLX_ALPHA_SIZE, 8,
            GLX_DEPTH_SIZE, 24,
            GLX_STENCIL_SIZE, 8,
            // We want RGBA rendering (vs COLOR_INDEX) and doublebuffer
            GLX_RENDER_TYPE, GLX_RGBA_BIT,
            // Double buffer is not strictly required as a non-doublebuffer
            // context can work with a doublebuffered surface, but it still
            // flickers and all applications want doublebuffer anyway.
            GLX_DOUBLEBUFFER, True,
            // All of these must be supported for full EGL support
            GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT | GLX_PBUFFER_BIT | GLX_PIXMAP_BIT,
            // This makes sure the config have an associated visual Id
            GLX_X_RENDERABLE, True,
            GLX_CONFIG_CAVEAT, GLX_NONE,
            None
        };
        glx::FBConfig* candidates = mGLX.chooseFBConfig(attribList, &nConfigs);
        if (nConfigs == 0)
        {
            XFree(candidates);
            return egl::Error(EGL_NOT_INITIALIZED, "Could not find a decent GLX FBConfig to create the context.");
        }
        mContextConfig = candidates[0];
        XFree(candidates);
    }

    mContext = initializeContext(mContextConfig, display->getAttributeMap());
    if (!mContext)
    {
        return egl::Error(EGL_NOT_INITIALIZED, "Could not create GL context.");
    }

    // FunctionsGL and DisplayGL need to make a few GL calls, for example to
    // query the version of the context so we need to make the context current.
    // glXMakeCurrent requires a GLXDrawable so we create a temporary Pbuffer
    // (of size 1, 1) for the duration of these calls.
    // Ideally we would want to unset the current context and destroy the pbuffer
    // before going back to the application but this is TODO
    // We could use a pbuffer of size (0, 0) but it fails on the Intel Mesa driver
    // as commented on https://bugs.freedesktop.org/show_bug.cgi?id=38869 so we
    // use (1, 1) instead.

    int dummyPbufferAttribs[] =
    {
        GLX_PBUFFER_WIDTH, 1,
        GLX_PBUFFER_HEIGHT, 1,
        None,
    };
    mDummyPbuffer = mGLX.createPbuffer(mContextConfig, dummyPbufferAttribs);
    if (!mDummyPbuffer)
    {
        return egl::Error(EGL_NOT_INITIALIZED, "Could not create the dummy pbuffer.");
    }

    if (!mGLX.makeCurrent(mDummyPbuffer, mContext))
    {
        return egl::Error(EGL_NOT_INITIALIZED, "Could not make the dummy pbuffer current.");
    }

    mFunctionsGL = new FunctionsGLGLX(mGLX.getProc);
    mFunctionsGL->initialize();

    syncXCommands();

    std::string rendererString =
        reinterpret_cast<const char*>(mFunctionsGL->getString(GL_RENDERER));
    mIsMesa = rendererString.find("Mesa") != std::string::npos;

    return DisplayGL::initialize(display);
}