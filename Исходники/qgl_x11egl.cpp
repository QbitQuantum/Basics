void qt_egl_add_platform_config(QEglProperties& props, QPaintDevice *device)
{
    if (device->devType() == QInternal::Image)
        props.setPixelFormat(static_cast<QImage *>(device)->format());
}