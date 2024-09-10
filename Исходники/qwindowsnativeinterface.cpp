void *QWindowsNativeInterface::nativeResourceForWindow(const QByteArray &resource, QWindow *window)
{
    if (!window || !window->handle()) {
        qWarning("%s: '%s' requested for null window or window without handle.", __FUNCTION__, resource.constData());
        return 0;
    }
    QWindowsWindow *bw = static_cast<QWindowsWindow *>(window->handle());
    int type = resourceType(resource);
    if (type == HandleType)
        return bw->handle();
    switch (window->surfaceType()) {
    case QWindow::RasterSurface:
    case QWindow::RasterGLSurface:
        if (type == GetDCType)
            return bw->getDC();
        if (type == ReleaseDCType) {
            bw->releaseDC();
            return 0;
        }
        break;
    case QWindow::OpenGLSurface:
        break;
    }
    qWarning("%s: Invalid key '%s' requested.", __FUNCTION__, resource.constData());
    return 0;
}