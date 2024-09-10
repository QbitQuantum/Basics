egl::Error DisplayAndroid::initialize(egl::Display *display)
{
    FunctionsEGLDL *egl = new FunctionsEGLDL();
    mEGL = egl;
    ANGLE_TRY(egl->initialize(display->getNativeDisplayId(), GetEGLPath()));

    gl::Version eglVersion(mEGL->majorVersion, mEGL->minorVersion);
    ASSERT(eglVersion >= gl::Version(1, 4));

    static_assert(EGL_OPENGL_ES3_BIT == EGL_OPENGL_ES3_BIT_KHR, "Extension define must match core");
    EGLint esBit = (eglVersion >= gl::Version(1, 5) || mEGL->hasExtension("EGL_KHR_create_context"))
                       ? EGL_OPENGL_ES3_BIT
                       : EGL_OPENGL_ES2_BIT;

    // clang-format off
    mConfigAttribList =
    {
        // Choose RGBA8888
        EGL_COLOR_BUFFER_TYPE, EGL_RGB_BUFFER,
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        // EGL1.5 spec Section 2.2 says that depth, multisample and stencil buffer depths
        // must match for contexts to be compatible.
        EGL_DEPTH_SIZE, 24,
        EGL_STENCIL_SIZE, 8,
        EGL_SAMPLE_BUFFERS, 0,
        // Android doesn't support pixmaps
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT | EGL_PBUFFER_BIT,
        EGL_CONFIG_CAVEAT, EGL_NONE,
        EGL_CONFORMANT, esBit,
        EGL_RENDERABLE_TYPE, esBit,
        EGL_NONE
    };
    // clang-format on
    EGLint numConfig;

    EGLBoolean success = mEGL->chooseConfig(mConfigAttribList.data(), &mConfig, 1, &numConfig);
    if (success == EGL_FALSE)
    {
        return egl::Error(mEGL->getError(), "eglChooseConfig failed");
    }

    ANGLE_TRY(initializeContext(display->getAttributeMap()));

    int dummyPbufferAttribs[] = {
        EGL_WIDTH, 1, EGL_HEIGHT, 1, EGL_NONE,
    };
    mDummyPbuffer = mEGL->createPbufferSurface(mConfig, dummyPbufferAttribs);
    if (mDummyPbuffer == EGL_NO_SURFACE)
    {
        return egl::Error(mEGL->getError(), "eglCreatePbufferSurface failed");
    }

    success = mEGL->makeCurrent(mDummyPbuffer, mContext);
    if (success == EGL_FALSE)
    {
        return egl::Error(mEGL->getError(), "eglMakeCurrent failed");
    }

    mFunctionsGL = mEGL->makeFunctionsGL();
    mFunctionsGL->initialize();

    return DisplayGL::initialize(display);
}