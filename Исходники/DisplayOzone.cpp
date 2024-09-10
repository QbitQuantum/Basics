egl::Error DisplayOzone::initialize(egl::Display *display)
{
    int fd;
    char deviceName[30];
    drmModeResPtr resources = nullptr;

    for (int i = 0; i < 9; ++i)
    {
        snprintf(deviceName, sizeof(deviceName), "/dev/dri/card%d", i);
        fd = open(deviceName, O_RDWR | O_CLOEXEC);
        if (fd >= 0)
        {
            resources = drmModeGetResources(fd);
            if (resources)
            {
                if (resources->count_connectors > 0)
                {
                    break;
                }
                drmModeFreeResources(resources);
                resources = nullptr;
            }
            close(fd);
        }
    }
    if (!resources)
    {
        return egl::Error(EGL_NOT_INITIALIZED, "Could not open drm device.");
    }

    mGBM = gbm_create_device(fd);
    if (!mGBM)
    {
        close(fd);
        drmModeFreeResources(resources);
        return egl::Error(EGL_NOT_INITIALIZED, "Could not create gbm device.");
    }

    mConnector            = nullptr;
    bool monitorConnected = false;
    for (int i = 0; !mCRTC && i < resources->count_connectors; ++i)
    {
        drmModeFreeConnector(mConnector);
        mConnector = drmModeGetConnector(fd, resources->connectors[i]);
        if (!mConnector || mConnector->connection != DRM_MODE_CONNECTED)
        {
            continue;
        }
        monitorConnected = true;
        mMode = ChooseMode(mConnector);
        if (!mMode)
        {
            continue;
        }
        int n = ChooseCRTC(fd, mConnector);
        if (n < 0)
        {
            continue;
        }
        mCRTC = drmModeGetCrtc(fd, resources->crtcs[n]);
    }
    drmModeFreeResources(resources);

    if (mCRTC)
    {
        mWidth  = mMode->hdisplay;
        mHeight = mMode->vdisplay;
    }
    else if (!monitorConnected)
    {
        // Even though there is no monitor to show it, we still do
        // everything the same as if there were one, so we need an
        // arbitrary size for our buffers.
        mWidth  = 1280;
        mHeight = 1024;
    }
    else
    {
        return egl::Error(EGL_NOT_INITIALIZED, "Failed to choose mode/crtc.");
    }

    // ANGLE builds its executables with an RPATH so they pull in ANGLE's libGL and libEGL.
    // Here we need to open the native libEGL.  An absolute path would work, but then we
    // couldn't use LD_LIBRARY_PATH which is often useful during development.  Instead we take
    // advantage of the fact that the system lib is available under multiple names (for example
    // with a .1 suffix) while Angle only installs libEGL.so.
    FunctionsEGLDL *egl = new FunctionsEGLDL();
    mEGL = egl;
    ANGLE_TRY(egl->initialize(display->getNativeDisplayId(), "libEGL.so.1"));

    const char *necessaryExtensions[] = {
        "EGL_KHR_image_base", "EGL_EXT_image_dma_buf_import", "EGL_KHR_surfaceless_context",
    };
    for (auto &ext : necessaryExtensions)
    {
        if (!mEGL->hasExtension(ext))
        {
            return egl::Error(EGL_NOT_INITIALIZED, "need %s", ext);
        }
    }

    if (mEGL->hasExtension("EGL_MESA_configless_context"))
    {
        mConfig = EGL_NO_CONFIG_MESA;
    }
    else
    {
        // clang-format off
        const EGLint attrib[] =
        {
            // We want RGBA8 and DEPTH24_STENCIL8
            EGL_RED_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_BLUE_SIZE, 8,
            EGL_ALPHA_SIZE, 8,
            EGL_DEPTH_SIZE, 24,
            EGL_STENCIL_SIZE, 8,
            EGL_NONE,
        };
        // clang-format on
        EGLint numConfig;
        EGLConfig config[1];
        if (!mEGL->chooseConfig(attrib, config, 1, &numConfig) || numConfig < 1)
        {
            return egl::Error(EGL_NOT_INITIALIZED, "Could not get EGL config.");
        }
        mConfig = config[0];
    }

    ANGLE_TRY(initializeContext(display->getAttributeMap()));

    if (!mEGL->makeCurrent(EGL_NO_SURFACE, mContext))
    {
        return egl::Error(EGL_NOT_INITIALIZED, "Could not make context current.");
    }

    mFunctionsGL = mEGL->makeFunctionsGL();
    mFunctionsGL->initialize();

    return DisplayGL::initialize(display);
}