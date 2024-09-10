void XCompositeGLXClientBufferIntegration::initializeHardware(QtWayland::Display *)
{
    qDebug() << "Initializing GLX integration";
    QPlatformNativeInterface *nativeInterface = QGuiApplicationPrivate::platformIntegration()->nativeInterface();
    if (nativeInterface) {
        mDisplay = static_cast<Display *>(nativeInterface->nativeResourceForWindow("Display",m_compositor->window()));
        if (!mDisplay)
            qFatal("could not retireve Display from platform integration");
    } else {
        qFatal("Platform integration doesn't have native interface");
    }
    mScreen = XDefaultScreen(mDisplay);

    mHandler = new XCompositeHandler(m_compositor->handle(), mDisplay);

    QOpenGLContext *glContext = new QOpenGLContext();
    glContext->create();

    m_glxBindTexImageEXT = reinterpret_cast<PFNGLXBINDTEXIMAGEEXTPROC>(glContext->getProcAddress("glXBindTexImageEXT"));
    if (!m_glxBindTexImageEXT) {
        qDebug() << "Did not find glxBindTexImageExt, everything will FAIL!";
    }
    m_glxReleaseTexImageEXT = reinterpret_cast<PFNGLXRELEASETEXIMAGEEXTPROC>(glContext->getProcAddress("glXReleaseTexImageEXT"));
    if (!m_glxReleaseTexImageEXT) {
        qDebug() << "Did not find glxReleaseTexImageExt";
    }

    delete glContext;
}