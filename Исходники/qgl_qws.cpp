void qt_egl_add_platform_config(QEglProperties& props, QPaintDevice *device)
{
    // Find the QGLScreen for this paint device.
    QGLScreen *glScreen = glScreenForDevice(device);
    if (!glScreen) {
        qWarning("QGLContext::chooseContext(): The screen is not a QGLScreen");
        return;
    }
    int devType = device->devType();
    if (devType == QInternal::Image)
        props.setPixelFormat(static_cast<QImage *>(device)->format());
    else
        props.setPixelFormat(glScreen->pixelFormat());
}