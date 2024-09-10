QEglContext::~QEglContext()
{
    destroyContext();

    if (currentGLContext == this)
        currentGLContext = 0;
    if (currentVGContext == this)
        currentVGContext = 0;
    QEglContextTracker::deref();
}