// Set pixel format and other properties based on a paint device.
void QEglProperties::setPaintDeviceFormat(QPaintDevice *dev)
{
    if (!dev)
        return;
    if (dev->devType() == QInternal::Image)
        setPixelFormat(static_cast<QImage *>(dev)->format());
    else
        setVisualFormat(qt_x11Info(dev));
}