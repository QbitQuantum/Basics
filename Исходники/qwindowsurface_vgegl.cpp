static QEglContext *createContext(QPaintDevice *device)
{
    QEglContext *context;

    // Create the context object and open the display.
    context = new QEglContext();
    context->setApi(QEgl::OpenVG);

    // Set the swap interval for the display.
    QByteArray interval = qgetenv("QT_VG_SWAP_INTERVAL");
    if (!interval.isEmpty())
        eglSwapInterval(QEgl::display(), interval.toInt());
    else
        eglSwapInterval(QEgl::display(), 1);

#ifdef EGL_RENDERABLE_TYPE
    // Has the user specified an explicit EGL configuration to use?
    QByteArray configId = qgetenv("QT_VG_EGL_CONFIG");
    if (!configId.isEmpty()) {
        EGLint cfgId = configId.toInt();
        EGLint properties[] = {
            EGL_CONFIG_ID, cfgId,
            EGL_NONE
        };
        EGLint matching = 0;
        EGLConfig cfg;
        if (eglChooseConfig
                    (QEgl::display(), properties, &cfg, 1, &matching) &&
                matching > 0) {
            // Check that the selected configuration actually supports OpenVG
            // and then create the context with it.
            EGLint id = 0;
            EGLint type = 0;
            eglGetConfigAttrib
                (QEgl::display(), cfg, EGL_CONFIG_ID, &id);
            eglGetConfigAttrib
                (QEgl::display(), cfg, EGL_RENDERABLE_TYPE, &type);
            if (cfgId == id && (type & EGL_OPENVG_BIT) != 0) {
                context->setConfig(cfg);
                if (!context->createContext()) {
                    delete context;
                    return 0;
                }
                return context;
            } else {
                qWarning("QT_VG_EGL_CONFIG: %d is not a valid OpenVG configuration", int(cfgId));
            }
        }
    }
#endif

    // Choose an appropriate configuration for rendering into the device.
    QEglProperties configProps;
    configProps.setPaintDeviceFormat(device);
    int redSize = configProps.value(EGL_RED_SIZE);
    if (redSize == EGL_DONT_CARE || redSize == 0)
        configProps.setPixelFormat(QImage::Format_ARGB32);  // XXX
#ifndef QVG_SCISSOR_CLIP
    // If we are using the mask to clip, then explicitly request a mask.
    configProps.setValue(EGL_ALPHA_MASK_SIZE, 1);
#endif
#ifdef EGL_VG_ALPHA_FORMAT_PRE_BIT
    configProps.setValue(EGL_SURFACE_TYPE, EGL_WINDOW_BIT |
                         EGL_VG_ALPHA_FORMAT_PRE_BIT);
    configProps.setRenderableType(QEgl::OpenVG);
    if (!context->chooseConfig(configProps)) {
        // Try again without the "pre" bit.
        configProps.setValue(EGL_SURFACE_TYPE, EGL_WINDOW_BIT);
        if (!context->chooseConfig(configProps)) {
            delete context;
            return 0;
        }
    }
#else
    configProps.setValue(EGL_SURFACE_TYPE, EGL_WINDOW_BIT);
    configProps.setRenderableType(QEgl::OpenVG);
    if (!context->chooseConfig(configProps)) {
        delete context;
        return 0;
    }
#endif

    // Construct a new EGL context for the selected configuration.
    if (!context->createContext()) {
        delete context;
        return 0;
    }

    return context;
}